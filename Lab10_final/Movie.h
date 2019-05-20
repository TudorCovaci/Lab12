#pragma once
#include <iostream>
class Movie {
private:
    std::string title_;
    std::string genre_;
    std::string trailerLink_;
    int yearOfRelease_;
    int numberOfLikes_;
public:
    /*Default constructor*/
    Movie() { title_ = ""; genre_ = ""; trailerLink_ = ""; yearOfRelease_ = 0; numberOfLikes_ = 0; }

    /*Default destructor*/
    ~Movie() {}

    /*Constructor: constructs a new movie object
    Input:
        - title: non-empty string
        - genre: non-empty string
        - trailerLink: non-empty string
        - yearOfRelease: positive integer
        - numberOfLikes: positive integer
    Output: A new movie object is created.*/
    Movie(std::string title, std::string genre, std::string trailerLink, int yearOfRelease, int numberOfLikes);
    
    /*Title attribute getter
    Input:
        -
    Output:
        - returns the object's "title" attribute
    */
    std::string getTitle();
    
    /*Genre attribute getter
    Input:
        -
    Output:
        - returns the object's "genre" attribute
    */
    std::string getGenre();

    /*Trailer link attribute getter
    Input:
        -
    Output:
        - returns the object's "trailerLink" attribute
    */
    std::string getTrailerLink();

    /*Equality operator for 2 movie-type objects.
    Input:
        - movieToCompare - Movie-type object, the movie that needs to be compared with the current object
    Output:
        - true, if the movies are equal
        - false, otherwise
    */
    bool operator==(Movie& movieToCompare);

    /*Stream-extraction operator
    Input:
        - inputStream, input stream
    Ouput:
        - Movie - movie-type object, the attributes are extracted from the stream
                  and are assigned to this parameter
    */
	friend std::istream& operator>>(std::istream& inputStream, Movie& Movie);
	
    /*Stream-insertion operator
    Input:
        - Movie - movie-type object, represents the object which has the attributes
                  that need to be inserted into the stream
        - outStream - output stream
    Output:
        the function returns an output stream which contains the movie object's attributes inserted into it. */
    friend std::ostream& operator<<(std::ostream& outStream, Movie& movie);

    /*
    Inequality operator for 2 movie-type objects;
    Input:
        - movieToCompareTo - movie-type object
    Output:
        - true, if the objects are different
        - false, otherwise
    */
    bool operator!=(Movie& movieToCompareTo);

    /*Year of release attribute getter
    Input:
        -
    Output:
        - returns the object's "yearOfRelease" attribute
    */
    int getYearOfRelease();

    /*Number of likes attribute getter
    Input:
        -
    Output:
        - returns the object's "numberOfLikes" attribute
    */
    int getNumberOfLikes();
	std::string toString();
};