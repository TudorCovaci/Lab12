#include "MovieRepoIterator.h"

bool MovieRepoIterator::valid()
{
    return currentPosition < repo_->getSize();
}
Movie& MovieRepoIterator::getCurrent()
{
    return repo_->getElements()[currentPosition];
}
void MovieRepoIterator::next()
{
    currentPosition++;
}
void MovieRepoIterator::first()
{
    currentPosition = 0;
}

