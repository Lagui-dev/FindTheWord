#ifndef LETTER_H
#define LETTER_H

#include <QObject>
#include <QDebug>

class Letter
{

public:
    explicit Letter();
    explicit Letter(const QString &v, const bool &isInTheRightPlace, const bool &isInTheWord);

    const QString value() const;
    void setValue(const QString &newValue);

    bool inTheRightPlace() const;
    void setInTheRightPlace(bool newInTheRightPlace);

    bool inTheWord() const;
    void setInTheWord(bool newInTheWord);

private:
    QString mValue;
    bool mInTheRightPlace;
    bool mInTheWord;
signals:

};

#endif // LETTER_H
