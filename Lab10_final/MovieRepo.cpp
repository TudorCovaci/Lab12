#include "MovieRepo.h"
#include <fstream>
void MovieRepo::addMovie(const Movie& MovieToAdd)
{
	elements_.push_back(MovieToAdd);
	
}
int MovieRepo::getSize()
{
    return elements_.size();

}

int MovieRepo::findMovieByTitle(std::string Title)
{	
	int index = 0;
	
	for (Movie& element : elements_)
	{
		if (element.getTitle() == Title)
			return index;
		index += 1;
	}
    return -1;
}

void MovieRepo::removeMovie(int Position)
{
    elements_.erase(elements_.begin() + Position);
}
void MovieRepo::updateMovie(std::string Title,const Movie& UpdatedMovie)
{
    int foundPosition = findMovieByTitle(Title);
    removeMovie(foundPosition);
    addMovie(UpdatedMovie);
}
std::ostream& operator<<(std::ostream& outStream, MovieRepo& repo)
{
    std::vector<Movie>::iterator repoIterator = repo.elements_.begin();
    for (int i = 0;i < repo.getSize();i++)
    {
        outStream << repo.elements_[i];
    }
    return outStream;
}
std::vector<Movie> MovieRepo::filterMovies(std::string genre, int numberOfLikes)
{
	std::vector<Movie> filteredVector;
	for (auto movie : elements_)
		if (movie.getGenre() == genre && movie.getNumberOfLikes() >= numberOfLikes)
			filteredVector.push_back(movie);
	return filteredVector;
}
void MovieRepo::writeToFile(std::string path)
{
	std::fstream saveFile_(path, std::ios::out);

	for (auto movie : elements_)
	{
		//saveFile_ << " ";
		saveFile_ << movie;
	}
	saveFile_.close();
}
void MovieRepo::readFromFile(std::string path)
{
	std::ifstream saveFile_(path, std::ios::in);
	if (!saveFile_.is_open())
	{
		std::fstream createdFile(path,std::ios::out);
		createdFile.close();
		
		return;
	}
	int size = 0;

	Movie newMovie;
	while (saveFile_ >> newMovie)
	{
		addMovie(newMovie);
	}
	saveFile_.close();
}