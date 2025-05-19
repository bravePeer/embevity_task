#pragma once
#include <iostream>
#include <string>
#include <vector>

class UI
{
public:

    enum class Command : int
    {
        None,
        Exit,
        Reset,
        SetSensivity,
        SetMeasurementsCount,
        Run,
        Init,
        Help
    };

    Command processInput();
    
    int getValueToSet();

    void printHelp();
    void printValueChanged(const std::string& valueName, int actualValue);
    void printResults(int floorChange, int pressure, float temperature);

    void printError(const std::string& error);
    void printInfo(const std::string& info);

private:
    std::vector<std::string> split(const std::string &s, char delim);

    int valueToSet = 0;
};