//#include "AdminInterface.h"
//#include "UserInterface.h"
//
//int main()
//{
//    
//    MovieRepo* repo = new MovieRepo();
//    Validator validator;
//    Controller controller(repo, validator);
//    AdminInterface adminUI(controller);
//    UserInterface ui(controller);
//    CommandLine commandLine;
//    std::cin >> commandLine;
//    int response = -3;
//    if (commandLine.getCommand() == "fileLocation")
//    {
//        if (commandLine.getParameters().size() != 1)
//            return -1;
//        controller.setFilePath(commandLine.getParameters()[0]);
//        controller.readFromFile();
//    }
//	std::cin >> commandLine;
//	if (commandLine.getCommand() == "myListLocation")
//	{
//		if (commandLine.getParameters().size() != 1)
//			return -1;
//		ui.setMyListPath(commandLine.getParameters()[0]);
//		ui.readMyList();
//	}
//    
//    while (response == -3)
//    {
//        if (commandLine.getCommand() == "exit")
//            return 0;
//        if (commandLine.getCommand()=="mode")
//        {
//            if(commandLine.getParameters().size() == 1)
//                if (commandLine.getParameters()[0] == "A")
//                    response = -2;
//                else if (commandLine.getParameters()[0] == "B")
//                    response = -1;
//        }
//        if (response == -3)
//            std::cin >> commandLine;
//    }
//    
//    while (true)
//    {
//
//        if (response == -2)
//            response = adminUI.mainLoop();
//        else if (response == -1)
//            response = ui.mainLoop();
//        else if(response == 0)
//        {
//            controller.writeToFile();
//			ui.writeMyList();
//            return 0;
//        }
//
//    }
//	
//}
