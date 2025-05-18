//My implementation made for other project

#pragma once
#include <stdint.h>

template <typename T>
struct RingBuffer
{
    RingBuffer(int size)
    {
        bufferSize = size + 1;
        bufferData = new T[bufferSize];
    }
    ~RingBuffer()
    {
        delete[] bufferData;
    }
    uint32_t beginIndex = 0;
    uint32_t endIndex = 0;
    int32_t bufferSize;
    T* bufferData;

    int getData(T& data, int32_t index)
    {
        if(((beginIndex + index) % bufferSize) == endIndex || index >= bufferSize)
            return -1;
        
        data = bufferData[(endIndex + index) % bufferSize];
        return 0;
    }

    int pushData(T& data)
    {
        if((beginIndex + 1) % bufferSize == endIndex)
            return -1; // Full buffer

        bufferData[beginIndex] = data;
        beginIndex = (beginIndex + 1) % bufferSize;

        return 0;
    }

    int popData(T& data)
    {
        if(beginIndex == endIndex)
            return -1; // Empty buffer
        
        data = bufferData[endIndex];
        endIndex = (endIndex + 1) % bufferSize;

        return 0;
    }

    int getDataCount()
    {
        if((beginIndex + 1) % bufferSize == endIndex)
            return bufferSize - 1; // Full buffer
        
        if(beginIndex >= endIndex)
            return beginIndex - endIndex;

        return bufferSize - endIndex + beginIndex;
    }
};

