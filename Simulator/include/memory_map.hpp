#pragma once
constexpr char SLAVE_ADDRESS = 0b01011101;

constexpr char MASK_MODE_CONTROL_AVE_NUM = 0b11100000;
constexpr char MASK_MODE_CONTROL_DR_EN   = 0b00010000;
constexpr char MASK_MODE_CONTROL_FULL_EN = 0b00001000;
constexpr char MASK_MODE_CONTROL_WTM_EN  = 0b00000100;
constexpr char MASK_MODE_CONTROL_MODE    = 0b00000011;

constexpr char MODE_CONTROL_MODE_STANDBY   = 0b00000000;
constexpr char MODE_CONTROL_MODE_CONTINOUS = 0b00000010;
constexpr char MODE_CONTROL_MODE_ONE_SHOT  = 0b00000001;
constexpr char MODE_CONTROL_AVE_NUM_8_TIMES  = 0b01100000;
constexpr char MODE_CONTROL_AVE_NUM_16_TIMES = 0b10000000;
constexpr char MODE_CONTROL_AVE_NUM_32_TIMES = 0b10100000;
constexpr char MODE_CONTROL_AVE_NUM_64_TIMES = 0b11000000;


constexpr char MASK_STATUS_RD_FULL = 0b00000100;
constexpr char MASK_STATUS_RD_WTM  = 0b00000010;
constexpr char MASK_STATUS_RD_DRDY = 0b00000001;

enum class MemoryAddresses : char
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


