//
#include "Movie.h"
#include "MovieRepo.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <exception>
#include "Tests.h"
#include "Interface.h"

void testMovie()
{
    
    Movie emptyMovie;
    assert(emptyMovie.getTitle() == "");
    Movie testMovie("film", "horror", "link", 2000, 30000);
    assert(testMovie.getGenre() == "horror");
    assert(testMovie.getTitle() == "film");
    assert(testMovie.getTrailerLink() == "link");
    assert(testMovie.getYearOfRelease() == 2000);
    assert(testMovie.getNumberOfLikes() == 30000);
    assert(!(emptyMovie == testMovie));
    Movie secondTestMovie("film", "horror", "link", 2000, 30000);
    assert(testMovie == secondTestMovie);
    Movie thirdTestMovie("film1", "comedy", "link1", 1000, 30);
    assert(testMovie != thirdTestMovie);

}
void testRepo()
{
    Movie firstTestMovie("film", "horror", "link", 2000, 30000);
    Movie secondTestMovie("film1", "horror1", "link1", 22220, 33330);
    Movie thirdTestMovie("film2", "horror2", "link2", 1111, 1111);
    MovieRepo testRepo;
    testRepo.addMovie(firstTestMovie);
    assert(testRepo.getSize() == 1);
    assert(testRepo.findMovieByTitle("film") == 0);
    testRepo.addMovie(secondTestMovie);
    assert(testRepo.getSize() == 2);
    assert(testRepo.findMovieByTitle("film1") == 1);
    testRepo.removeMovie(0);
    assert(testRepo.getSize() == 1);
    assert(testRepo.findMovieByTitle("film") == -1);
    testRepo.addMovie(firstTestMovie);
    testRepo.updateMovie(secondTestMovie.getTitle(), thirdTestMovie);
    assert(testRepo.getSize() == 2);
    assert(testRepo.findMovieByTitle("film2") == 1);
    assert(testRepo.getElements().size() == 2);
    std::cout << testRepo;

}
void testController()
{

    auto testRepo = new MovieRepo();
    Validator* testValidator = new Validator();
    Controller testController(testRepo, testValidator);
    testController.setFilePath("C:\\Users\\Tudor\\Desktop\\test.txt");
    testController.readFromFile();
    testController.AddMovieToRepo("film", "horror", 30000, 2000, "link");
    assert(testController.SizeOfRepo() == 1);
    testController.AddMovieToRepo("film1", "horror1", 3330, 22220, "link1");

    assert(testController.SizeOfRepo() == 2);
    testController.RemoveMovie("film");
    assert(testController.SizeOfRepo() == 1);
    
    assert(testController.getCurrent().getTitle() == "film1");

    testController.UpdateMovie("film1", "Genre2", 2005, 10000, "Link2");
    assert(testController.getCurrent().getTitle() == "film1");
    assert(testController.getCurrent().getGenre() == "Genre2");
    assert(testController.getCurrent().getYearOfRelease() == 2005);
    assert(testController.getCurrent().getNumberOfLikes() == 10000);
    assert(testController.getCurrent().getTrailerLink() == "Link2");
    testController.AddMovieToRepo("film", "horror", 2000, 30000, "link");
    testController.next();
    assert(testController.getCurrent().getTitle() == "film");
    assert(testController.getCurrent().getGenre() == "horror");
    assert(testController.getCurrent().getYearOfRelease() == 2000);
    assert(testController.getCurrent().getNumberOfLikes() == 30000);
    assert(testController.getCurrent().getTrailerLink() == "link");
    try 

    {
        testController.AddMovieToRepo("film", "horror", 2000, 30000, "link");
        assert(false);
    }
    catch(InterfaceException& ex)
    {
        assert(true);
    }
    testController.next();
    testController.next();
    try
    {
        testController.AddMovieToRepo("", "", 1, 1, "");
        assert(false);        

    }
    catch(InterfaceException& ex)
    {
        assert(true);
    }
    try
    {
        
        testController.AddMovieToRepo("a", "b", -1, -1, "c");
        assert(false);

    }
    catch (InterfaceException& ex)
    {
        assert(true);
    }
    try
    {
        testController.RemoveMovie("testmovie");
        assert(false);
    }
    catch (InterfaceException& ex)
    {
        assert(true);
    }
    assert(testController.getRepo()->getSize() == testRepo->getSize());
    testController.writeToFile();
    testController.readFromFile();
    testController.writeToFile();
    testController.readFromFile();
    testController.setFilePath("");
    testController.readFromFile();

}
//void testAdminUI()
//{
//    MovieRepo repo;
//    Validator validator(repo);
//    Controller controller(repo, validator);
//    AdminInterface ui(controller);
//    ui.mainLoop();
//}
//void testUI()
//{
//    MovieRepo repo;
//    Validator validator(repo);
//    Controller controller(repo, validator);
//    controller.AddMovieToRepo("film", "horror", 30000, 2000, "link");
//    controller.AddMovieToRepo("film1", "comedy", 3330, 22220, "link1");
//    UserInterface ui(controller);
//    ui.mainLoop();
//}
//void testApp()
//{
//    MovieRepo repo;
//    Validator validator(repo);
//    Controller controller(repo, validator);
//    AdminInterface adminUI(controller);
//    UserInterface ui(controller);
//    CommandLine commandLine;
//    std::cin >> commandLine;
//    int response;
//    if (commandLine.getParameters()[0] == "A")
//        response = -2;
//    else
//        response = -1;
//    while (true)
//    {
//
//            if (response == -2)
//                response = adminUI.mainLoop();
//            else if (response == -1)
//                response = ui.mainLoop();
//            else
//            {
//                return;
//            }
//
//    }
//}
void testAll()
{
    testMovie();
    testRepo();    
    testController();
    //testAdminUI();
    //testUI();
    //testApp();
}