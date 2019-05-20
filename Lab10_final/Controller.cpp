#include "Controller.h"
#include <fstream>
#include <string>


bool Controller::AddMovieToRepo(std::string title, std::string genre, std::string yearOfRelease, std::string numberOfLikes, std::string link)
{
	int yearOfReleaseInt;
	int numberOfLikesInt;
	try {
		
		yearOfReleaseInt = std::stoi(yearOfRelease);
		numberOfLikesInt = std::stoi(numberOfLikes);
	}
	catch (std::exception & ex)
	{
		throw std::exception("Invalid data!\n");
	}
	
    Movie newMovie(title, genre, link, yearOfReleaseInt, numberOfLikesInt);
    if (validator_->validate(newMovie) == true)
        if (repo_->findMovieByTitle(newMovie.getTitle()) != -1)
            throw std::exception("Movie already exists!\n");
        else
        {
            repo_->addMovie(newMovie);
			writeToFile();
            return true;
        }
}
bool Controller::RemoveMovie(std::string title)
{
    int position = repo_->findMovieByTitle(title);
    if (position == -1)
        throw std::exception("The movie was not found!\n");
    repo_->removeMovie(position);
	writeToFile();
    return true;
}

bool Controller::UpdateMovie(std::string title, std::string newGenre, std::string newYearOfRelease, std::string newNumberOfLikes, std::string newLink)
{
	int yearOfReleaseInt;
	int numberOfLikesInt;
	try {
		yearOfReleaseInt = std::stoi(newYearOfRelease);
		numberOfLikesInt = std::stoi(newNumberOfLikes);
	}
	catch (std::exception & ex)
	{
		throw std::exception("Invalid parameters!");
	}
	
    Movie updatedMovie(title, newGenre, newLink, yearOfReleaseInt, numberOfLikesInt);
    validator_->validate(updatedMovie);
    repo_->updateMovie(title, updatedMovie);
	writeToFile();

    return true;
}


void Controller::next()
{
    iterator_->next();
    if (!iterator_->valid())
    {
        iterator_->first();
    }
    
}
Movie& Controller::getCurrent()
{
    if (iterator_->valid())
        return iterator_->getCurrent();
}
MovieRepo* Controller::getRepo()
{
    return repo_;
}
void Controller::writeToFile()
{
	repo_->writeToFile(pathOfFile_);
}
void Controller::setFilePath(std::string pathOfFile)
{
	pathOfFile_ = pathOfFile;
}
void Controller::readFromFile()
{
	repo_->readFromFile(pathOfFile_);
}