#include "Movie.h"
#include <string>
#include <sstream>
#include <vector>
Movie::Movie(std::string title, std::string genre, std::string trailerLink, int yearOfRelease, int numberOfLikes)
{
    title_ = title;
    genre_ = genre;
    trailerLink_ = trailerLink;
    yearOfRelease_ = yearOfRelease;
    numberOfLikes_ = numberOfLikes;
}
std::string Movie::getTitle()
{
    return title_;
}
std::string Movie::getGenre()
{
    return genre_;
}
std::string Movie::getTrailerLink()
{
    return trailerLink_;
}
bool Movie::operator!=(Movie & firstMovie)
{
    return !(genre_ == firstMovie.getGenre() &&
        title_ == firstMovie.getTitle() &&
        numberOfLikes_ == firstMovie.getNumberOfLikes() &&
        yearOfRelease_ == firstMovie.getYearOfRelease() &&
        trailerLink_ == firstMovie.getTrailerLink());
}
int Movie::getYearOfRelease()
{
    return yearOfRelease_;
}
int Movie::getNumberOfLikes()
{
    return numberOfLikes_;
}
std::ostream& operator<<(std::ostream& os, Movie& movie)
{
    os << movie.getTitle() << ","
        << movie.getGenre() << ","
        << movie.getYearOfRelease() << ","
        << movie.getNumberOfLikes() << ","
        << movie.getTrailerLink() << "\n";
    return os;
}
std::vector<std::string> tokenize(std::string line)
{
	std::vector<std::string> result;
	std::stringstream ss(line);
	std::string token;
	while (std::getline(ss, token, ','))
		result.push_back(token);
	return result;
}
bool Movie::operator==(Movie& MovieToCompare)
{
    if (title_ == MovieToCompare.getTitle() &&
        genre_ == MovieToCompare.getGenre() &&
        trailerLink_ == MovieToCompare.getTrailerLink() &&
        yearOfRelease_ == MovieToCompare.getYearOfRelease() &&
        numberOfLikes_ == MovieToCompare.getNumberOfLikes())
        return true;
    return false;
}
std::istream& operator>>(std::istream& inputStream, Movie& Movie)
{
	std::string line;
	std::getline(inputStream, line);
	std::vector<std::string> tokens = tokenize(line);
	if (tokens.size() != 5)
	{
		return inputStream;
	}
	
	Movie.title_ = tokens[0];
	Movie.genre_ = tokens[1];
	Movie.yearOfRelease_ = std::stoi(tokens[2]);
	Movie.numberOfLikes_ = std::stoi(tokens[3]);
	Movie.trailerLink_ = tokens[4];
	return inputStream;
}
std::string Movie::toString()
{
	std::string newString = "";
	char* yearOfReleaseString = new char[100];
	char* numberOfLikesString = new char[100];
	itoa(yearOfRelease_, yearOfReleaseString, 10);
	itoa(numberOfLikes_, numberOfLikesString, 10);
	newString += title_ + ",";
	newString += genre_ + ",";
	newString += yearOfReleaseString;
	newString += ",";
	newString += numberOfLikesString;
	newString += "," + trailerLink_;
	return newString;
}