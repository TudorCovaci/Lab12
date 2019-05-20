#include "UserInterface.h"
#include <fstream>
UserInterface::UserInterface(Controller& controller) : controller_(controller)
{
}
void UserInterface::writeMyListCSV()
{
	std::ofstream csvFile(myListPath_);
	csvFile << myList_;
	csvFile.close();
}
void UserInterface::writeMyListHTML()
{
	std::ofstream htmlFile(myListPath_);
	htmlFile << "<!DOCTYPE html><html><head><title>My Movie List</title></head><body><table border='1'>";
	htmlFile << "<tr><td>Title</td><td>Genre</td><td>Year of release</td><td>Number of likes</td><td>Link</td></tr>";
	for (int i = 0; i < myList_.getSize(); i++) {
		Movie currentMovie = myList_.getElements()[i];
		htmlFile << "<tr><td>" << currentMovie.getTitle() << "</td><td>" << currentMovie.getGenre() << "</td>"
			<< "<td>" << currentMovie.getYearOfRelease() << "</td>"
			<< "<td>" << currentMovie.getNumberOfLikes() <<"</td>"
			<< "<td><a href = \"" << currentMovie <<"\">Trailer Link</a></td></tr>";
	}
	htmlFile << "</table></body></html>";
	htmlFile.close();

}
void UserInterface::readMyListCSV()
{
	std::ifstream csvFile(myListPath_);
	if (!csvFile.is_open())
	{
		std::ofstream createdFile(myListPath_);
		createdFile.close();
	}
	Movie currentMovie;
	while (csvFile >> currentMovie)
	{
		myList_.addMovie(currentMovie);

	}
	
	csvFile.close();
}
void UserInterface::openMyListCSV()
{
	std::string command = "notepad.exe \"" + myListPath_ + "\"";
	system(command.c_str());
}
void UserInterface::openMyListHTML()
{
	std::string command = "C:\\Users\\Tudor\\AppData\\Local\\Programs\\Opera\\launcher.exe \"" + myListPath_ + "\"";
	system(command.c_str());
}
void UserInterface::readMyList()
{
	readMyListCSV();

}
void UserInterface::writeMyList()
{
	if(myListPath_.substr(myListPath_.find_first_of('.')+1) == "csv" || myListPath_.substr(myListPath_.find_first_of('.') + 1) == "txt")
		writeMyListCSV();
	else writeMyListHTML();
}
void UserInterface::openMyList()
{
	if (myListPath_.substr(myListPath_.find_first_of('.') + 1) == "html")
		openMyListHTML();
	else openMyListCSV();
}
int UserInterface::commandHash(std::string command)
{
    if (command == "next")
        return NEXT;
    if (command == "save")
        return SAVE;
    if (command == "list")
        return LIST;
    if (command == "mylist")
        return MYLIST;
    if (command == "exit")
        return EXIT;
    if (command == "mode")
        return MODEA;
}
int UserInterface::mainLoop()
{
    CommandLine commandLine;
    
    Movie currentMovie;
    while (true)
    {
        try
        {
            std::cin >> commandLine;
            int command = commandHash(commandLine.getCommand());
            switch (command)
            {
                case NEXT:
                {
                    if (commandLine.getParameters().size() > 1)
                        throw InterfaceException("Invalid parameters!");
                    if (commandLine.getParameters().size() == 0)
                    {
                        
                        currentMovie = controller_.getCurrent();
                        controller_.next();
                        std::cout << currentMovie;
                        break;

                    }
                    else
                    {
                        int nextContor = 0;
                        std::string genre = commandLine.getParameters()[0];
                        Movie lastMovie = controller_.getCurrent();
						Movie auxMovie;
                        controller_.next();
                        while (controller_.getCurrent() != lastMovie)
                        {
                            auxMovie = controller_.getCurrent();
                            if (auxMovie.getGenre() == genre)
							{
								currentMovie = auxMovie;
                                std::cout << currentMovie;
                                break;
                            }
                            controller_.next();
                        }
                        if (controller_.getCurrent() == lastMovie)
                        {
							if(lastMovie.getGenre() == genre)
							{	
								std::cout << lastMovie;
								currentMovie = controller_.getCurrent();
							}
                        }
                        break;
                    }

                    


                    
                }
                case SAVE:
                {
                    if (commandLine.getParameters().size() != 1)
                        throw InterfaceException("Invalid parameters!");
					Movie movieToAdd = controller_.getRepo()->getElements()[controller_.getRepo()->findMovieByTitle(commandLine.getParameters()[0])];
                    myList_.addMovie(movieToAdd);
					writeMyList();
                    break;
                }
                case LIST:
                {
                    if (commandLine.getParameters().size() > 2)
                        throw InterfaceException("Invalid parameters!");
                    if (commandLine.getParameters().size() == 0)
                    {
                        std::cout << (*controller_.getRepo());
                        break;
                    }
                    else
                    {
                        std::string genre = commandLine.getParameters()[0];
                        int numberOfLikes = stoi(commandLine.getParameters()[1]);
                        int nextCounter = 0;
                        while (nextCounter < controller_.SizeOfRepo())
                        {
                            Movie currentMovie = controller_.getCurrent();
                            if (currentMovie.getGenre() == genre && currentMovie.getNumberOfLikes() >= numberOfLikes)                         
                            {
                                std::cout << currentMovie;
                            }
                            controller_.next();
                            nextCounter++;
                        }
                        break;
                    }
                }
                case MYLIST:
                {
                    if (commandLine.getParameters().size() != 0)
                        throw InterfaceException("Invalid parameters!");
					openMyList();
                    break;
                }
                case EXIT:
                {
                    if (commandLine.getParameters().size() != 0)
                        throw InterfaceException("Invalid parameters!");
                    return 0;
                }
                case MODEA:
                {
                    if (commandLine.getParameters().size() != 1)
                        throw InterfaceException("Invalid parameters!");
                    return -2;
                }
                default:
                {
                    return 0;
                }
            }
        }
        catch (InterfaceException& ex)
        {
            std::cout << ex.what();
            
        }
    }
}