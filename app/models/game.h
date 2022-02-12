#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGuiApplication>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include "lettermodel.h"
#include "letter.h"

#include "dbmanager.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void keyPressed(const QString letterValue);
    Q_INVOKABLE void restart();
    Q_PROPERTY(LetterModel *lettersModel READ lettersModel CONSTANT);
    Q_PROPERTY(QString wordToFindString READ wordToFindString CONSTANT)

    enum GameStatus {
        //wordNotFound,
        notAllLettersHaveBeenEntered,
        //youWin,
        cancel
    };

    explicit Game(QObject *parent = nullptr);

    const QString &wordToFindString() const;

private:
    LetterModel *mLettersPlayed;
    LetterModel mLettersOfWordToFind;
    QString mWordToFindString;

    int mCurrentPosition;
    int mMaxOfRows;
    int mCurrentRow;
    int mLengthOfWord;
    bool youLOST;
    bool youWIN;

    DbManager *mDictionary;

    QTimer mChrono;
    QTime  mChronoHMS;
    QTime  mBestChrono;

    LetterModel *lettersModel() const;

    bool areYouWIN();
    QString removeAccents(QString s);

private slots:
    void chronoAdd1sec();

signals:
    void wordNotFound();
    void youWin();
    void youtLost();
    void restartGame();
    void chronoUpdated(QString chronoHMS);
};

#endif // GAME_H
