#pragma once
#include <vector>
#include <string>
#include <iostream>
class InterfaceException : public std::exception
{
private:
    std::string message_;
public:
    InterfaceException(const std::string& message) : message_(message) {}
    virtual const char* what() const noexcept override
    {
        return message_.c_str();
    }
    ~InterfaceException() {}
};

class CommandLine
{
private:
    std::string command_;
    std::vector<std::string>parameters_;
    
public:
    std::string getCommand();
    bool validate(std::string commandString);
    std::vector<std::string> getParameters();
    friend std::istream& operator>>(std::istream& inStream, CommandLine& commandLine);
};
class Interface
{
private:
   
    virtual int commandHash(std::string command) = 0;
public:
    
    virtual int mainLoop() = 0;

};