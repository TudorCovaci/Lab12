#include "AdminInterface.h"
int AdminInterface::commandHash(std::string command)
{
    if (command == "add")
        return ADD;
    if (command == "delete")
        return DELETE;
    if (command == "update")
        return UPDATE;
    if (command == "list")
        return LIST;
    if (command == "exit")
        return EXIT;
    if (command == "mode")
        return MODEB;

}
int AdminInterface::mainLoop()
{
    CommandLine commandLine;
    while (true)
    {
        try
        {
            std::cin >> commandLine;
            int command = commandHash(commandLine.getCommand());
            switch (command)
            {
            case ADD:
            {
                if (commandLine.getParameters().size() != 5)
                    throw InterfaceException("Invalid parameters!");
                std::string title = commandLine.getParameters()[0];
                std::string genre = commandLine.getParameters()[1];
                int yearOfRelease = stoi(commandLine.getParameters()[2]);
                int numberOfLikes = stoi(commandLine.getParameters()[3]);
                std::string link = commandLine.getParameters()[4];
                controller_.AddMovieToRepo(title, genre, yearOfRelease, numberOfLikes, link);
                break;
            }
            case DELETE:
            {
                if (commandLine.getParameters().size() != 1)
                    throw InterfaceException("Invalid parameters!");
                std::string title = commandLine.getParameters()[0];
                controller_.RemoveMovie(title);
                break;
            }
            case UPDATE:
            {
                if (commandLine.getParameters().size() != 5)
                    throw InterfaceException("Invalid parameters!");
                std::string title = commandLine.getParameters()[0];
                std::string newGenre = commandLine.getParameters()[1];
                int newYearOfRelease = stoi(commandLine.getParameters()[2]);
                int newNumberOfLikes = stoi(commandLine.getParameters()[3]);
                std::string newLink = commandLine.getParameters()[4];
                controller_.UpdateMovie(title, newGenre, newYearOfRelease, newNumberOfLikes, newLink);
                break;
            }
            case LIST:
            {
                if (commandLine.getParameters().size() != 0)
                    throw InterfaceException("Invalid parameters!");
                std::cout << (*controller_.getRepo());
                break;
            }
            case EXIT:
                if (commandLine.getParameters().size() != 0)
                    throw InterfaceException("Invalid parameters!");
                return 0;
            case MODEB:
                if (commandLine.getParameters().size() != 1)
                    throw InterfaceException("Invalid parameters!");
                return -1;
            default:
                return 0;

            }
        }
        catch (InterfaceException& ex)
        {
            std::cout << ex.what();
            
        }
    }
}