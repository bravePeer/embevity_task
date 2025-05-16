#pragma once
#include <iostream>
#include <math.h>
#include "client.hpp"
#include "../../Simulator/include/memory_map.hpp"

void readSensorReg(Client* c, MemoryAddresses addr)
{
    char buffer[1];
    buffer[0] = static_cast<char>(addr);
    int len = 1;
    c->writeReg(SLAVE_ADDRESS, buffer, 1); // Set read reg
    c->readReg(SLAVE_ADDRESS, buffer, &len);

    std::cout<<"Reg val = ";
    printCharArray(buffer, len);
    std::cout << std::endl;
}

/// @brief Sets register responsible for power up device
/// @param c pointer to client
/// @param val if 1 device is power up else is power down
void setPowerDown(Client* c, char val)
{
    char buffer[2];
    buffer[0] = static_cast<char>(MemoryAddresses::PowerDown);
    buffer[1] = val;
    c->writeReg(SLAVE_ADDRESS, buffer, 2);
}

void setReset(Client* c, char val)
{
    char buffer[2];
    buffer[0] = static_cast<char>(MemoryAddresses::Reset);
    buffer[1] = val;
    c->writeReg(SLAVE_ADDRESS, buffer, 2);
}

/// @brief 
/// @param c 
/// @param pressure Pa
/// @param temperature *C
void readPressureTemperature(Client* c, int* pressure, float* temperature)
{
    char buffer[5];
    int len = 5;
    buffer[0] = static_cast<char>(MemoryAddresses::PressureMSB);
    c->writeReg(SLAVE_ADDRESS, buffer, 1);
    c->readReg(SLAVE_ADDRESS, buffer, &len);

    int tmpPress = buffer[0] & 0xff;
    tmpPress <<= 8;
    tmpPress |=  buffer[1] & 0xff;
    tmpPress <<= 6;
    tmpPress |=  buffer[2] & 0x3f;
    

    float tmpPressF = (static_cast<float>(tmpPress) / 2048.f) * 100.f;
    *pressure = static_cast<int>(std::round(tmpPressF));

    unsigned int tmpTemp = buffer[3] & 0xff;
    tmpTemp <<= 8;
    tmpTemp |= buffer[4] & 0xff;
    
    *temperature = static_cast<float>(tmpTemp) / 32.f;
}

