#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(const QString &path, QObject *parent = nullptr);
    QString getWord(const int &length = 0);
    bool wordExist(const QString &word);
private:

    QSqlDatabase mDB;

signals:

};

#endif // DBMANAGER_H
