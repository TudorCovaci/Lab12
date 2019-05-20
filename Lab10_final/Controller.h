#pragma once
#include "MovieRepo.h"
#include "Validator.h"
#include "MovieRepoIterator.h"
class Controller
{
private:
    MovieRepo* repo_;
    Validator* validator_;
	std::string pathOfFile_;
    MovieRepoIterator* iterator_;

public:
    
    /*Constructor
    Input:
        - repo, movieRepo-object reference
        - validator, validator-object reference
    Output:
        - a new controller-object is created
    */
	Controller(MovieRepo* repo, Validator* validator) { validator_ = validator;  repo_ = repo; iterator_ = new MovieRepoIterator(repo); }
	Controller(MovieRepo* repo) { repo_ = repo, validator_ = new Validator; }
    
    bool AddMovieToRepo(std::string title, std::string genre, std::string yearOfRelease, std::string numberOfLikes, std::string link);
    bool RemoveMovie(std::string title);
    bool UpdateMovie(std::string title, std::string newGenre, std::string newYearOfRelease, std::string newNumberOfLikes, std::string newLink);
	int SizeOfRepo() { return repo_->getSize(); }
    MovieRepo* getRepo();
    void next();
    Movie& getCurrent();

	void setFilePath(std::string pathOfFile);
	void writeToFile();
	void readFromFile();
};
