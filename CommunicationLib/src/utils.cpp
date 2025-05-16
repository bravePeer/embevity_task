#include "utils.hpp"

void printCharArray(const char* data, int len)
{
    std::cout << std::setfill('0') << std::hex;
    for (int i = 0; i < len; i++)
    {
        std::cout <<  std::setw(2) << ((int)data[i] & 0xff) << " ";
    }
    std::cout << std::setfill(' ') << std::dec;
}