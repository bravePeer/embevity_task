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
    if(ringBuffer)
        delete ringBuffer;
    ringBuffer = new RingBuffer<int>(measurementsCount);

    setPowerDown(client, 1);
    setReset(client, 1);
    
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
    int pressure = calculatePressureMean();
    
    std::cout << "Pressure: "<< pressure << " Last pressure: "<< lastPossibleCorrectPressureVal << " Counts: " << correctCounts << " Possible change: " << possibleChange << std::endl;

    int floorChanged = 0;

    if(possibleChange)
    {
        if(abs(lastPressureVal - pressure) < sensivityChange)
        {
            correctCounts++;
        }
        else
        {
            possibleChange = false;
            correctCounts = 0;
        }
    }

    if(abs(lastPossibleCorrectPressureVal - pressure) > sensivityChange)
    {
        possibleChange = true;
    }

    if(correctCounts == measurementsCount)
    {
        if(lastPressureVal - pressure < sensivityChange)
            floorChanged = -1;
        else
            floorChanged = 1;

        possibleChange = false;
        correctCounts = 0;
        lastPossibleCorrectPressureVal = pressure;
    }

    lastPressureVal = pressure;
    return floorChanged;
}

int PositionDetector::readNextPressureVal()
{
    int pressure = 0;
    float temperature = 0.0f;
    readPressureTemperature(client, &pressure, &temperature);

    return pressure;
}

void PositionDetector::updatePressure()
{
    int pressure = readNextPressureVal();
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