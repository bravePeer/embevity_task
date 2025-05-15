#include "BM1390GLV_ZTR.hpp"

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
        memory.reset = val & 0x01;
        break;
    case MemoryAddresses::ModeControl:
        memory.modeControl = val;
        break;
    case MemoryAddresses::IIRFifoControl:
        memory.modeControl = val & 0b11000011;
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
        return memory.status;
    case MemoryAddresses::PressureMSB:
        return memory.pressureMSB;
    case MemoryAddresses::PressureLSB:
        return memory.pressureLSB;
    case MemoryAddresses::PressureXL:
        return memory.pressureXL;
    case MemoryAddresses::TemperatureMSB:
        return memory.temperatureMSB;
    case MemoryAddresses::TemperatureLSB:
        return memory.temperatureLSB;
    }
    return 0;
}
