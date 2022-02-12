#ifndef LETTERMODEL_H
#define LETTERMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>
#include <QDebug>

#include "letter.h"

class LetterModel : public QAbstractListModel
{
    Q_OBJECT
public:

    Q_INVOKABLE void addLetter(const QString &letterValue);
    Q_INVOKABLE void setLetter(const Letter *letter, const int &index);
    Q_INVOKABLE void setWord(const QString &wordValue);
    Q_INVOKABLE void clearLetters();
    Q_INVOKABLE QString word();
    Q_INVOKABLE QString wordAt(const int &begin, const int &end);
    Q_INVOKABLE QString getValue(const int &index);
    Q_INVOKABLE Letter *getObject(const int &index);


    enum LetterRoles {
        Value = Qt::UserRole + 1,
        InTheRightPlace,
        InTheWord
    };
    explicit LetterModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Letter*> mLetters;
};

#endif // LETTERMODEL_H
