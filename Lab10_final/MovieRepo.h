#pragma once

#include "Movie.h"
#include <vector>
class MovieRepo
{
private:
	std::vector<Movie> elements_;
public:

    /*Default constructor*/
    MovieRepo() {}

    /*Adds a new movie to the repository
    Input:
        - movieToAdd - constant movie-object reference, the movie 
                       that needs to be added
    Output:
        -
    */
	virtual void addMovie(const Movie& movieToAdd);
    /*Finds the first movie in the repo that has a given title.
    Input:
        - title - string, the title that is searched in the repo
    Output:
        - integer != -1, represents the movie's position in the repo
        - -1, if the movie does not exist

    */
    virtual int findMovieByTitle(std::string Title);

    /*Removes the movie that is on the given position from the repo.
    Input:
        - position, integer
    Output:
        -
    */
    virtual void removeMovie(int Position);

    /*Size getter
    Input:
        -
    Output:
        - integer, represents the current size of the repo
    */
    int getSize();

    /*Updates the movie with the given title
    Input:
        - title, string
        - updatedMovie, movie-type object reference
    Output:
        - 
    */
    virtual void updateMovie(std::string Title,const  Movie& UpdatedMovie);
    
    /*Returns an array containing the elements
    Input:
        -
    Output:
        - STL vector of movie objects   
    */
    std::vector<Movie>& getElements() { return elements_; }

	std::vector<Movie>filterMovies(std::string genre, int numberOfLikes);
    /*Stream-insertion operator
    Input:
        - outStream, output stream
        - repo, movieRepo-object
    Output:
        - updated output stream
    */
    friend std::ostream& operator<<(std::ostream& outStream, MovieRepo& repo);
	void writeToFile(std::string path);
	void readFromFile(std::string path);
   
};