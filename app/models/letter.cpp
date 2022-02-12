#include "letter.h"

Letter::Letter()
{
    mValue = "";
    mInTheRightPlace = false;
    mInTheWord = false;
}

Letter::Letter(const QString &v, const bool &isInTheRightPlace, const bool &isInTheWord)

{
    mValue = v;
    mInTheRightPlace = isInTheRightPlace;
    mInTheWord = isInTheWord;
}

const QString Letter::value() const
{
    return mValue;
}

void Letter::setValue(const QString &newValue)
{
    mValue = newValue;
}

bool Letter::inTheRightPlace() const
{
    return mInTheRightPlace;
}

void Letter::setInTheRightPlace(bool newInTheRightPlace)
{
    mInTheRightPlace = newInTheRightPlace;
}

bool Letter::inTheWord() const
{
    return mInTheWord;
}

void Letter::setInTheWord(bool newInTheWord)
{
    mInTheWord = newInTheWord;
}

