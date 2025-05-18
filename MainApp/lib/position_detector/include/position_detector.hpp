#include <iostream>
#include "client.hpp"
#include "ring_buffer.hpp"

class PositionDetector
{
public:
    PositionDetector(Client* c);
    ~PositionDetector();

    void reset();
    
    /// @brief Set before init()
    /// @param val 
    void setSensivityChange(int val);
    
    /// @brief Set before init()
    /// @param val 
    void setMeasurementCount(int val);
    
    void init();
    
    void updatePressure();
    int calculatePressureMean();

    int update();
    int readNextPressureVal();

private:
    Client* client;

    int sensivityChange = 10; // Pa
    const int minSensivityChange = 1;
    const int maxSensivityChange = 10000; // Pa

    int measurementsCount = 3;
    const int minMeasurementsCount = 1;
    const int maxMeasurementsCount = 1000; 

    bool initialized = false;
    int lastPressureVal = 0;
    int lastPossibleCorrectPressureVal = 0;

    int correctCounts = 0;
    bool possibleChange = false;

    RingBuffer<int>* ringBuffer;
};