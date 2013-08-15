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
    GroupsUpdateWorker(QMap <int, VkWallModel*>* posts, QString token, QObject *parent = 0);
    void start();
private:
    QMap <int, VkWallModel*>* m_posts;
    QString m_token;
    QMap <int, VkWallModel*>::iterator m_pos;
signals:
    void finished();
public slots:
    void proceed();
    void replyFinished(QNetworkReply* reply);
};

#endif // GROUPSUPDATEWORKER_H
