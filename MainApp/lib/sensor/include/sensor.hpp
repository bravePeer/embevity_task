#pragma once
#include <iostream>
#include <math.h>
#include "client.hpp"
#include "../../Simulator/include/memory_map.hpp"

/// @brief Read register value from sensor if error occure throw exception
/// @param c Pointer to client to connect to simulator
/// @param addr Address of register
/// @return Register Value
char readSensorReg(Client* c, MemoryAddresses addr);

/// @brief Sets register responsible for power up device if error occure throw exception
/// @param c Pointer to client to connect to simulator
/// @param val If 1 device is power up else if 0 is power down
void setPowerDown(Client* c, char val);

/// @brief Sets register responsible for reset device if error occure throw exception
/// @param c Pointer to client to connect to simulator
/// @param val If 1 device is ready to work else if 0 is in reset mode
void setReset(Client* c, char val);

/// @brief Reads pressure and temperature from sensor if error occure throw exception
/// @param c Pointer to client to connect to simulator
/// @param pressure Pointer where to store pressure in Pa
/// @param temperature Pointer where to store temperature in *C
void readPressureTemperature(Client* c, int* pressure, float* temperature);
