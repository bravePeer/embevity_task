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
        Run
    };

    Command processInput();
    
    int getValueToSet();

    void printHelp();
    void printValueChanged();
    void printReset();
    void printResult();


private:
    std::vector<std::string> split(const std::string &s, char delim);

    int valueToSet = 0;
};