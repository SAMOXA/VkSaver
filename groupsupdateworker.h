#ifndef GROUPSUPDATEWORKER_H
#define GROUPSUPDATEWORKER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMap>
#include <QList>
#include "json.h"
#include "vkwall.h"

class GroupsUpdateWorker : public QObject
{
    Q_OBJECT
public:
    GroupsUpdateWorker(QVariantMap *storage, QString token, QObject *parent = 0)
        :m_storage(storage), m_token(token)
    { m_pos = m_storage->begin(); }
    void start();
private:
    QVariantMap *m_storage;
    QString m_token;
    QVariantMap::iterator m_pos;
signals:
    void finished();
public slots:
    void proceed();
    void replyFinished(QNetworkReply* reply);
};

#endif // GROUPSUPDATEWORKER_H
