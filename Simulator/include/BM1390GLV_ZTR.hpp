#pragma once
#include <iostream>
#include <fstream>
#include "memory_map.hpp"

class BM1390GLV_ZTR
{
public:
    ~BM1390GLV_ZTR();

    void processI2C(char* data, int* dataLen, int* shouldAnswer);

    void writeReg(MemoryAddresses addr, char val);
    char readReg(MemoryAddresses addr);

    /// @brief Open log file and load first data
    /// @param path path to file
    void initLoadPressTempFromFile(const char* path);

    void updatePressTempFromFile();

    void restart();

private:
    struct Memory
    {
        const char manufacturerId = '\xe0';
        const char partId = '\x34';
        char powerDown = 0;
        char reset = 0;
        char modeControl = 0;
        char iirFifoControl = 0;
        char fifoData = 0;
        char status = 0;
        char pressureMSB = 0;
        char pressureLSB = 0;
        char pressureXL = 0;
        char temperatureMSB = 0;
        char temperatureLSB = 0;
    };
    Memory memory;
    char registerAddr = 0;

    bool updateNeeded = false;
    bool fileInitialized = false;
    std::fstream logFile;
};