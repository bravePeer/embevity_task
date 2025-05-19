#include "position_detector.hpp"
#include "sensor.hpp"

PositionDetector::PositionDetector(Client* c)
{
    client = c;
    ringBuffer = new RingBuffer<int>(measurementsCount);
}

PositionDetector::~PositionDetector()
{
    delete ringBuffer;
}

void PositionDetector::init()
{
    if(initialized)
        return;
    
    if(ringBuffer)
        delete ringBuffer;
    ringBuffer = new RingBuffer<int>(measurementsCount);

    setPowerDown(client, 1);
    setReset(client, 1);
    setControlMode(client, MODE_CONTROL_AVE_NUM_8_TIMES | MODE_CONTROL_MODE_CONTINOUS);

    initialized = true;
}

void PositionDetector::deinit()
{
    setControlMode(client, MODE_CONTROL_AVE_NUM_8_TIMES | MODE_CONTROL_MODE_STANDBY);
    setReset(client, 0);
    setPowerDown(client, 0);

    initialized = false;
    lastPressureVal = 0;
    lastPossibleCorrectPressureVal = 0;
    correctCounts = 0;
    possibleChange = false;
}

void PositionDetector::setSensivityChange(int val)
{
    if(val < minSensivityChange || val > maxSensivityChange)
        throw "Error wrong walue";

    sensivityChange = val;
}

void PositionDetector::setMeasurementCount(int val)
{
    if(val < minMeasurementsCount || val > maxMeasurementsCount)
        throw "Error wrong walue";

    measurementsCount = val;
}

int PositionDetector::update()
{
    updatePressure();
    int meanPressure = calculatePressureMean();
    
    // std::cout << "Pressure: "<< meanPressure << " Last pressure: "<< lastPossibleCorrectPressureVal << " Counts: " << correctCounts << " Possible change: " << possibleChange << std::endl;

    int floorChanged = 0;

    if(possibleChange)
    {
        if(abs(lastPressureVal - meanPressure) < sensivityChange)
        {
            correctCounts++;
        }
        else
        {
            possibleChange = false;
            correctCounts = 0;
        }
    }

    if(abs(lastPossibleCorrectPressureVal - meanPressure) > sensivityChange)
    {
        possibleChange = true;
    }

    if(correctCounts == measurementsCount)
    {
        if(lastPossibleCorrectPressureVal - meanPressure < sensivityChange)
            floorChanged = -1;
        else
            floorChanged = 1;

        possibleChange = false;
        correctCounts = 0;
        lastPossibleCorrectPressureVal = meanPressure;
    }

    lastPressureVal = meanPressure;
    return floorChanged;
}

void PositionDetector::updatePressureTemperature()
{
    readPressureTemperature(client, &pressure, &temperature);
}

void PositionDetector::updatePressure()
{
    updatePressureTemperature();
    if(ringBuffer->pushData(pressure) == -1)
    {
        int oldestPressure;
        ringBuffer->popData(oldestPressure);
        ringBuffer->pushData(pressure);
    }
}

int PositionDetector::calculatePressureMean()
{
    long int mean = 0;
    int dataCount = ringBuffer->getDataCount();
    for (int i = 0; i < dataCount; i++)
    {
        int tmp;
        ringBuffer->getData(tmp, i);
        mean = mean + tmp;
    }
    
    if(dataCount == 0)
        throw "ERROR";

    return static_cast<int>(mean / dataCount);
}

bool PositionDetector::isInitialized()
{
    return initialized;
}

int PositionDetector::getPressure()
{
    return lastPressureVal;
}

float PositionDetector::getTemperature()
{
    return temperature;
}
