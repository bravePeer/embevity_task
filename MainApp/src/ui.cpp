#include "ui.hpp"
#include <sstream>

UI::Command UI::processInput()
{
    std::string str;
    std::cout << ">";
    std::getline(std::cin, str);

    std::vector<std::string> input = split(str, ' ');

    if(input.empty())
        return Command::None;

    if(input[0] == "reset")
        return Command::Reset;

    if(input[0] == "exit")
        return Command::Exit;

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
    std::cout << "HELP" << std::endl;
}
