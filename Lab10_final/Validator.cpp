#include "Validator.h"
#include <exception>
bool Validator::validate(Movie& movieToValidate)
{
    if (movieToValidate.getGenre() == "" || movieToValidate.getTitle() == "" || movieToValidate.getTrailerLink() == "")
        throw std::exception("Invalid genre/title/trailer link!\n");
    if (movieToValidate.getNumberOfLikes() < 0 || movieToValidate.getYearOfRelease() < 0)
        throw std::exception("Invalid number of likes / year of release!\n");
    return true;
}
