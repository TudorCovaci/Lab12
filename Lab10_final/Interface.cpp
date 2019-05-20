#include "Interface.h"
#include <sstream>
std::vector<std::string> tokenize1(std::string line)
{
    
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> result;
    std::getline(ss, token, ' ');
    result.push_back(token);
    while (std::getline(ss, token, ','))
        result.push_back(token);
    for (int index = 2;index < result.size();index++)
    {
        result[index].erase(result[index].begin());
    }
    return result;
}

std::string CommandLine::getCommand()
{
    return command_;
}

std::vector<std::string> CommandLine::getParameters()
{
    return parameters_;
}
bool CommandLine::validate(std::string CommandString)
{
    return false;
}
std::istream& operator>>(std::istream & inStream, CommandLine & commandLine)
{
    std::string line;
    std::getline(inStream, line);
    std::vector<std::string> result = tokenize1(line);
    commandLine.command_ = result[0];
    result.erase(result.begin());
    commandLine.parameters_ = result;
    return inStream;
}
