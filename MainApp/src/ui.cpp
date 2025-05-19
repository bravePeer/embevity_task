#include "ui.hpp"
#include <sstream>

UI::Command UI::processInput()
{
    std::string str;
    std::cout << "\n>";
    std::getline(std::cin, str);

    std::vector<std::string> input = split(str, ' ');

    if(input.empty())
        return Command::None;

    if(input[0] == "reset")
        return Command::Reset;

    if(input[0] == "exit")
        return Command::Exit;

    if(input[0] == "init")
        return Command::Init;
    
    if(input[0] == "help")
        return Command::Help;

    if(input[0] == "set")
    {
        if(input.size() != 3)
            return Command::None;

        valueToSet = atoi(input[2].c_str());
        if(input[1] == "sensivity")
            return Command::SetSensivity;
        else if(input[1] == "count")
            return Command::SetMeasurementsCount;
        else
            return Command::None;
    }

    if(input[0] == "run")
    {
        if(input.size() != 2)
            return Command::None;

        valueToSet = atoi(input[1].c_str());
        return Command::Run;
    }

    return Command::None;
}

std::vector<std::string> UI::split(const std::string &str, char delim) 
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim)) 
    {
        result.push_back(item);
    }

    return result;
}

int UI::getValueToSet()
{
    return valueToSet;
}

void UI::printHelp()
{
    std::cout << "HELP\n\n" ;
    std::cout << "init -> initializes detector\n";
    std::cout << "reset -> resets detector\n";
    std::cout << "run <numberOfCycles> -> run for the designated number of cycles \n";
    std::cout << "exit -> exit the program\n";
    std::cout << "set <count/sensivity> <value> -> set parameter (count or sensivity) to value. To take effect run this command before init\n";
    std::cout << "help -> this information\n";
    std::cout << std::endl;
}

void UI::printValueChanged(const std::string& valueName, int actualValue)
{
    std::cout << "Value of " << valueName << " set to: " << actualValue << std::endl;
}

void UI::printResults(int floorChange, int pressure, float temperature)
{
    std::cout << "\33[2K\rFloor change: " << floorChange << ", Pressure: " << pressure <<" Pa, Temperature: "<< temperature << " *C" << std::flush;

    if(floorChange > 0)
        std::cout << "\nFloor up" << std::endl;
    else if(floorChange < 0)
        std::cout << "\nFloor down" << std::endl;
}

void UI::printError(const std::string& error)
{
    std::cout << "ERROR: " << error << std::endl;
}

void UI::printInfo(const std::string& info)
{
    std::cout << "INFO: " << info << std::endl;
}
