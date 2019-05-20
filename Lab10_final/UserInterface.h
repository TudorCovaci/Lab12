#pragma once
#include "Interface.h"
#include "Controller.h"
#define NEXT 1
#define SAVE 2
#define LIST 3
#define MYLIST 4
#define EXIT 0
#define MODEA -2

class UserInterface : public Interface
{
private:
    MovieRepo myList_;
    Controller& controller_;
    int commandHash(std::string command);
	std::string myListPath_;
	void writeMyListCSV();
	void readMyListCSV();
	void writeMyListHTML();
	void readMyListHTML();
	void openMyListCSV();
	void openMyListHTML();
public:
    UserInterface(Controller& controller);
    int mainLoop();
	void setMyListPath(std::string path) { myListPath_ = path; }
	void openMyList();
	void readMyList();
	void writeMyList();
};