#include "dbmanager.h"
#include <QDebug>

dbManager::dbManager(QString path, QObject *parent) :
    QObject(parent)
{
    qDebug() << "Here";
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path);
    if (!dbase.open())
    {
        qDebug() << "Not open";
    }
    QSqlQuery q;
    if(!q.exec(QString("CREATE TABLE IF NOT EXISTS groups ("
                       "gid INTEGER PRIMARY KEY NOT NULL,"
                       "name TEXT,"
                       "photoUrl TEXT,"
                       "photo BLOB,"
                       "lastRecordDate INTEGER"
                       ");"))){
        qDebug() << "Can`t create groups";
    }
    if(!q.exec(QString("CREATE TABLE IF NOT EXISTS posts ("
                       "pid INTEGER NOT NULL,"
                       "gid INTEGER NOT NULL,"
                       "date INTEGER,"
                       "text TEXT,"
                       "aid INTEGER,"
                       "PRIMARY KEY (pid, gid),"
                       "FOREIGN KEY(gid) REFERENCES groups(gid)"
                       ");"))){
        qDebug() << "Can`t create posts";
    }
    if(!q.exec(QString("PRAGMA foreign_keys = ON;"))){
        qDebug() << "Can`t foreign_keys";
    }
}

QMap<int, VkGroup *> *dbManager::getGroups()
{
    QSqlQuery q;
    q.exec(QString("SELECT * FROM groups"));
    QSqlRecord r = q.record();
    QMap<int, VkGroup *>* groups = new QMap<int, VkGroup*>;
    while (q.next()) {
        auto gid = q.value(r.indexOf("gid")).toInt();
        auto name = q.value(r.indexOf("name")).toString();
        auto photoUrl = q.value(r.indexOf("photoUrl")).toString();
        VkGroup* group = new VkGroup(gid, name, photoUrl);
        groups->insert(groups->end(), gid, group);
    }
    return groups;
}

void dbManager::addGroup(int gid, QString& name, QString& photoUrl)
{
    QSqlQuery q;
    if(!q.exec(QString("INSERT INTO groups VALUES ('%1', '%2', '%3', NULL, '%4');").arg(gid).arg(name).arg(photoUrl).arg(0))){
        qDebug() << "Can`t add groups " << q.lastError().text() << " " << q.lastQuery();
    }
}
