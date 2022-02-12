#include "lettermodel.h"

LetterModel::LetterModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void LetterModel::addLetter(const QString &letterValue)
{
    Letter *letter = new Letter(letterValue, false, false);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mLetters.append(letter);
    endInsertRows();
}

void LetterModel::setLetter(const Letter *letter, const int &index)
{
    mLetters.at(index)->setValue(letter->value());
    mLetters.at(index)->setInTheWord(letter->inTheWord());
    mLetters.at(index)->setInTheRightPlace(letter->inTheRightPlace());
    QModelIndex topLeft = createIndex(index, 0);
    QModelIndex bottomRight = createIndex( index ,0);
    emit dataChanged( topLeft, bottomRight );
}

void LetterModel::setWord(const QString &wordValue)
{
    mLetters.clear();
    for (int pos = 0; pos < wordValue.count(); pos++) {
        addLetter(wordValue.at(pos));
    }
}

void LetterModel::clearLetters()
{
    beginResetModel();
    qDeleteAll(mLetters);
    mLetters.clear();
    endResetModel();
}

QString LetterModel::word()
{
    return wordAt(0, mLetters.length()-1);
}

QString LetterModel::wordAt(const int &begin, const int &end)
{
    QString theWord = "";
    if ((begin >=0) && (end < mLetters.count())) {
        for (int pos = begin; pos <= end; pos++) {
            theWord = theWord + mLetters.at(pos)->value();
        }
    }
    return theWord;
}

QString LetterModel::getValue(const int &index)
{
    const Letter *letter = mLetters.at(index);
    return letter->value();
}

Letter *LetterModel::getObject(const int &index)
{
    return mLetters.at(index);
}

int LetterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mLetters.count();
}

QVariant LetterModel::data(const QModelIndex &index, const int role) const
{
    if (index.row() < 0 || index.row() >= mLetters.count())
        return QVariant();

    const Letter *letter = mLetters.at(index.row());

    switch (role) {
    case LetterRoles::Value :
        return letter->value();
        break;
    case LetterRoles::InTheRightPlace:
        return letter->inTheRightPlace();
        break;
    case LetterRoles::InTheWord:
        return letter->inTheWord();
        break;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LetterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LetterRoles::Value] = "value";
    roles[LetterRoles::InTheRightPlace] = "inTheRightPlace";
    roles[LetterRoles::InTheWord] = "inTheWord";
    return roles;
}
