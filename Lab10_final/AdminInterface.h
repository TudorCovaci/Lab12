#pragma once
#include "Interface.h"
#include "Controller.h"
#define ADD 1
#define DELETE 2
#define UPDATE 3
#define LIST 4
#define EXIT 0
#define MODEB -1
class AdminInterface : public Interface
{
private:
    Controller& controller_;
    int commandHash(std::string command);
    
public:
    AdminInterface(Controller& controller) : controller_(controller) {}
    int mainLoop();
    
    
};