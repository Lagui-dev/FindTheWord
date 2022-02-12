#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
{
    mDictionary = new DbManager(QCoreApplication::applicationDirPath() + "/data/data.db");

    youLOST = true;
    youWIN  = false;
    mLettersPlayed = new LetterModel;
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");

    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter("F");
    mLettersPlayed->addLetter("I");
    mLettersPlayed->addLetter("N");
    mLettersPlayed->addLetter("D");
    mLettersPlayed->addLetter(" ");

    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter("T");
    mLettersPlayed->addLetter("H");
    mLettersPlayed->addLetter("E");
    mLettersPlayed->addLetter(" ");

    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter("W");
    mLettersPlayed->addLetter("O");
    mLettersPlayed->addLetter("R");
    mLettersPlayed->addLetter("D");
    mLettersPlayed->addLetter(" ");

    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");
    mLettersPlayed->addLetter(" ");

    connect(&mChrono, &QTimer::timeout, this, &Game::chronoAdd1sec);
    mChronoHMS = QTime(0,0,0,0);
    mChrono.setInterval(1000);
    mBestChrono = QTime(23,59,59);

}

void Game::keyPressed(const QString letterValue)
{
    if (youLOST || youWIN) {
        return;
    }

    if (!mChrono.isActive()) {
        mChrono.start();
    }

    if (letterValue == "BACK") {
        if ((mCurrentPosition  + mCurrentRow * mLengthOfWord) >= mCurrentRow * mLengthOfWord) {
            Letter *letter = mLettersPlayed->getObject(mCurrentPosition+mCurrentRow*mLengthOfWord);
            letter->setValue("");
            letter->setInTheRightPlace(false);
            letter->setInTheWord(false);

            mLettersPlayed->setLetter(letter, mCurrentPosition+mCurrentRow*mLengthOfWord);
            mCurrentPosition--;
        }
    } else {
        if (letterValue == "ENTER") {
            if (mCurrentPosition + 1 == mLengthOfWord) {
                areYouWIN();
            }
            // TODO Else Warning

        } else {
            if (mCurrentPosition < mLengthOfWord - 1) {
                mCurrentPosition++;
                Letter *letter = mLettersPlayed->getObject(mCurrentPosition + mCurrentRow * mLengthOfWord);
                letter->setValue(letterValue);
                letter->setInTheRightPlace(false);
                letter->setInTheWord(false);
                mLettersPlayed->setLetter(letter, mCurrentPosition + mCurrentRow * mLengthOfWord);
            }
        }
    }
}

void Game::restart()
{
    mWordToFindString = removeAccents(mDictionary->getWord(6)).toUpper();

    mLettersOfWordToFind.setWord(mWordToFindString);
    mLettersPlayed->clearLetters();
    emit restartGame();
    mLengthOfWord = 6;
    mMaxOfRows = 5;
    mCurrentRow = 0;
    mCurrentPosition = -1;
    youLOST = false;
    youWIN  = false;
    for (int pos = 1; pos <= mLengthOfWord ; pos++ ) {
        mLettersPlayed->addLetter("");
    }
    mChrono.stop();
    mChronoHMS = QTime(0,0,0,0);

}

const QString &Game::wordToFindString() const
{
    return mWordToFindString;
}

LetterModel *Game::lettersModel() const
{
    return mLettersPlayed;
}

bool Game::areYouWIN()
{
    if (!mDictionary->wordExist(mLettersPlayed->wordAt(mCurrentRow * mLengthOfWord,(mCurrentRow + 1) * mLengthOfWord - 1))) {
        emit wordNotFound();
        return false;
    }
    int countInTheRightPlace = 0;
    // Compare Letters
    for (int posPlayed = 0 ; posPlayed < mLengthOfWord ; posPlayed++) {
        Letter *letterPlayed = mLettersPlayed->getObject(posPlayed + mCurrentRow * mLengthOfWord);
        letterPlayed->setInTheWord(false);
        letterPlayed->setInTheRightPlace(false);
        //mLettersPlayed->setLetter(letterPlayed, posPlayed + mCurrentRow * mLengthOfWord);
        for (int posWord = 0 ; posWord < mLengthOfWord; posWord++) {
            Letter *letterToFind = mLettersOfWordToFind.getObject(posWord);
            if (letterPlayed->value() == letterToFind->value()) {
                if (posPlayed == posWord) {
                    letterPlayed->setInTheRightPlace(true);
                    countInTheRightPlace++;
                    break;
                } else {
                    letterPlayed->setInTheWord(true);
                }
            }
        }
        mLettersPlayed->setLetter(letterPlayed, posPlayed + mCurrentRow * mLengthOfWord);

    }
    if (countInTheRightPlace == mLengthOfWord) {
        mChrono.stop();
        emit youWin();
        return true;
    } else {
        if (mCurrentRow < mMaxOfRows) {
            mCurrentPosition = -1;
            mCurrentRow++;
            for (int pos = 1; pos <= mLengthOfWord ; pos++ ) {
                mLettersPlayed->addLetter("");
            }
        } else {
            youLOST = true;
            mChrono.stop();
            emit youtLost();
        }
        return false;
    }

}

QString Game::removeAccents(QString s)
{
    QString diacriticLetters_;
    QStringList noDiacriticLetters_;

    if (diacriticLetters_.isEmpty()) {
        diacriticLetters_ = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ");
        noDiacriticLetters_ << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y";
    }

    QString output = "";
    for (int i = 0; i < s.length(); i++) {
        QChar c = s[i];
        int dIndex = diacriticLetters_.indexOf(c);
        if (dIndex < 0) {
            output.append(c);
        } else {
            QString replacement = noDiacriticLetters_[dIndex];
            output.append(replacement);
        }
    }

    return output;
}

void Game::chronoAdd1sec()
{
    mChronoHMS = mChronoHMS.addSecs(1);
    emit chronoUpdated(mChronoHMS.toString("hh:mm:ss"));
}
