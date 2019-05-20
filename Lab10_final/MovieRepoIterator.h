#include "MovieRepo.h"
class MovieRepoIterator
{
private:
    MovieRepo* repo_;
    int currentPosition;
public:
	MovieRepoIterator(MovieRepo* repo) { repo_ = repo; }
    bool valid();
    Movie& getCurrent();
    void next();
    void first();
};