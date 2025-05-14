unsigned char slaveAddress = 0b01011101;

enum MemoryAddresses
{
    ManufacturerId = 0x0F,
    PartId = 0x10,
    PowerDown = 0x12,
    Reset = 0x13,
    ModeControl = 0x14,
    IIRFifoControl = 0x15,
    FifoData = 0x18,
    Status = 0x19,
    PressureMSB = 0x1A,
    PressureLSB = 0x1B,
    PressureXL = 0x1C,
    TemperatureMSB = 0x1D,
    TemperatureLSB = 0x1E
};

struct MemoryMap
{
    
};

