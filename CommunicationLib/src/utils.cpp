#include "utils.hpp"

void printCharArray(const char* data, int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << ((int)data[i] & 0xff) << " ";
        // std::cout << std::setfill('0') << std::setw(2) << std::hex << ((int)data[i] & 0xff) << " ";
    }
}