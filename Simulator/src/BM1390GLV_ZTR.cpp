#include "BM1390GLV_ZTR.hpp"

BM1390GLV_ZTR::~BM1390GLV_ZTR()
{
    if(logFile.is_open())
        logFile.close();
}

void BM1390GLV_ZTR::processI2C(char* data, int* dataLen, int* shouldAnswer)
{
    if(((data[0] >> 1) & 0b01111111) != SLAVE_ADDRESS)
        throw std::runtime_error("Wrong device address");

    if(*dataLen < 2)
        throw std::runtime_error("Too short packet");

    if(data[0] & 1) // Read from device
    {
        (*dataLen)--;
        for (int i = 0; i < *dataLen; i++)
            data[i] = readReg(static_cast<MemoryAddresses>(registerAddr + i));
        
        *shouldAnswer = 1;
    }
    else // Write to device
    {
        registerAddr = data[1];
        for (int i = 0; i < *dataLen - 2; i++)
            writeReg(static_cast<MemoryAddresses>(registerAddr + i), data[i + 2]);

        *shouldAnswer = 0;
    }
}

void BM1390GLV_ZTR::writeReg(MemoryAddresses addr, char val)
{
    switch (addr)
    {
    case MemoryAddresses::PowerDown:
        memory.powerDown = val & 0x01;
        break;
    case MemoryAddresses::Reset:
        if(memory.powerDown & 0x01)
            memory.reset = val & 0x01;
        break;
    case MemoryAddresses::ModeControl:
        if((memory.reset & 0x01) == 0)
            return;
        
        if((memory.modeControl & MASK_MODE_CONTROL_MODE) == 0x03) // Prohibited
            return;

        // Prohibited changing beetween modes
        if(memory.modeControl & MASK_MODE_CONTROL_MODE
            && val & MASK_MODE_CONTROL_MODE)
            return;

        // Check prohibited AVE_NUM
        if((val & MASK_MODE_CONTROL_AVE_NUM) < MODE_CONTROL_AVE_NUM_8_TIMES 
            && (val & MASK_MODE_CONTROL_AVE_NUM) > MODE_CONTROL_AVE_NUM_32_TIMES)
            return;

        updateNeeded = true;
        memory.modeControl = val;
        break;
    case MemoryAddresses::IIRFifoControl:
        memory.modeControl = val & 0b11000011;
        break;
    case MemoryAddresses::ManufacturerId:
    case MemoryAddresses::PartId:
    case MemoryAddresses::FifoData:
    case MemoryAddresses::Status:
    case MemoryAddresses::PressureLSB:
    case MemoryAddresses::PressureMSB:
    case MemoryAddresses::PressureXL:
    case MemoryAddresses::TemperatureMSB:
    case MemoryAddresses::TemperatureLSB:
        break;
    }
}

char BM1390GLV_ZTR::readReg(MemoryAddresses addr)
{
    switch (addr)
    {
    case MemoryAddresses::ManufacturerId:
        return memory.manufacturerId;
    case MemoryAddresses::PartId:
        return memory.partId;
    case MemoryAddresses::PowerDown:
        return memory.powerDown;
    case MemoryAddresses::Reset:
        return memory.reset;
    case MemoryAddresses::ModeControl:
        return memory.modeControl;
    case MemoryAddresses::IIRFifoControl:
        return memory.iirFifoControl;
    case MemoryAddresses::FifoData:
        return memory.fifoData;
    case MemoryAddresses::Status:
    {
        char tmp = memory.status;
        if(memory.status & MASK_STATUS_RD_DRDY)
            memory.status &= ~MASK_STATUS_RD_DRDY;
        return tmp;
    }
    case MemoryAddresses::PressureMSB:
        updateNeeded = true;
        return memory.pressureMSB;
    case MemoryAddresses::PressureLSB:
        updateNeeded = true;
        return memory.pressureLSB;
    case MemoryAddresses::PressureXL:
        updateNeeded = true;
        return memory.pressureXL;
    case MemoryAddresses::TemperatureMSB:
        updateNeeded = true;
        return memory.temperatureMSB;
    case MemoryAddresses::TemperatureLSB:
        updateNeeded = true;
        return memory.temperatureLSB;
    }
    return 0;
}

void BM1390GLV_ZTR::initLoadPressTempFromFile(const char* path)
{
    if(logFile.is_open())
        logFile.close();
    logFile.open(path, std::ios_base::in);

    updatePressTempFromFile();
}

void BM1390GLV_ZTR::updatePressTempFromFile()
{
    if(!updateNeeded)
        return;

    if((memory.modeControl & MASK_MODE_CONTROL_MODE) == MODE_CONTROL_MODE_STANDBY)
        return;

    if((memory.modeControl & MASK_MODE_CONTROL_MODE) == MODE_CONTROL_MODE_ONE_SHOT) // One shot mode
    {
        memory.modeControl &= ~MASK_MODE_CONTROL_MODE;
    }

    if(logFile.eof())
    {
        std::cout << "File ended" << std::endl;
        memory.pressureMSB = 0;
        memory.pressureLSB = 0;
        memory.pressureXL = 0;

        memory.temperatureLSB = 0;
        memory.temperatureMSB = 0;
        return;
    }
    
    std::string tmp;
    for (int i = 0; i < 21; i++)
        logFile >> tmp;

    int pressure = atoi(tmp.c_str());
    logFile >> tmp;
    logFile >> tmp;
    double temperature = atof(tmp.c_str());

    for (int i = 0; i < 8; i++) // new line
        logFile >> tmp;    

    pressure = (pressure * 2048) / 100;
    memory.pressureMSB = static_cast<char>(pressure >> 14);
    memory.pressureLSB = static_cast<char>(pressure >> 6);
    memory.pressureXL = static_cast<char>(pressure & 0x3f);

    temperature = temperature * 32;
    int temperatureInt = static_cast<int>(temperature);
    memory.temperatureLSB = static_cast<char>(temperatureInt);
    memory.temperatureMSB = static_cast<char>(temperatureInt >> 8);
    //std::cout<<pressure << " "<< temperature<<std::endl;
    memory.status |= MASK_STATUS_RD_DRDY;
}

void BM1390GLV_ZTR::restart()
{
    memory.powerDown = 0;
    memory.reset = 0;
    memory.modeControl = 0;
    memory.iirFifoControl = 0;
    memory.fifoData = 0;
    memory.status = 0;
    memory.pressureMSB = 0;
    memory.pressureLSB = 0;
    memory.pressureXL = 0;
    memory.temperatureMSB = 0;
    memory.temperatureLSB = 0;

    updateNeeded = false;
}
