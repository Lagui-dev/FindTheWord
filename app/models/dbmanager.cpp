#include "dbmanager.h"

DbManager::DbManager(const QString &path, QObject *parent)
    : QObject{parent}
{
    mDB = QSqlDatabase::addDatabase("QSQLITE");
    mDB.setDatabaseName(path);
    if (!mDB.open()) {
        qDebug() << "Dictionary not found";
    } else {
        qDebug() << "Connected";
    }
}

QString DbManager::getWord(const int &length)
{
    QSqlQuery query(mDB);
    query.prepare("SELECT UPPER(lemma) AS word FROM FR WHERE FR.length = :length AND frequency > 1 ORDER BY RANDOM() LIMIT 1;");
    query.bindValue(":length", length);
    if (query.exec()) {
        if (query.next()) {
            return query.value("word").toString();
        }
    }
    return "";
}

bool DbManager::wordExist(const QString &word)
{
    QSqlQuery query(mDB);
    query.prepare("SELECT UPPER(lemma) AS word FROM FR WHERE word = :word;");
    query.bindValue(":word", word);
    if (query.exec()) {
        if (query.next()) {
            if (query.value("word").toString().length() != NULL) {
                return true;
            }
        }
    }
    return false;
}
