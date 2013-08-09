#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QDateTime>
#include "vkgroup.h"

class dbManager : public QObject
{
    Q_OBJECT
public:
    dbManager(QString path, QObject *parent = 0);
    QMap<int, VkGroup*>* getGroups();
    void addGroup(int gid, QString& name, QString& photoUrl);
private:
    QSqlDatabase dbase;
signals:
    void SIGNALdbError(QString& str);
public slots:
    
};

#endif // DBMANAGER_H
