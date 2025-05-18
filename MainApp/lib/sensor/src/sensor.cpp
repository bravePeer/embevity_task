#include "sensor.hpp"

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