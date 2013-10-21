#include "groupsupdateworker.h"
#include <QDebug>

void GroupsUpdateWorker::proceed()
{
    QNetworkAccessManager *manager1 = new QNetworkAccessManager(this);
    connect(manager1, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);


    manager1->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              "count=100&"
                                               "access_token=%2").arg(-m_pos.key().toInt()).arg(m_token))));
    m_pos++;
    if(m_pos == m_storage->end()){
        emit finished();
        return;
    }
    QNetworkAccessManager *manager2 = new QNetworkAccessManager(this);
    connect(manager2, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);
    manager2->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              "count=100&"
                                               "access_token=%2").arg(-m_pos.key().toInt()).arg(m_token))));
    m_pos++;
    if(m_pos == m_storage->end()){
        emit finished();
        return;
    }
    QNetworkAccessManager *manager3 = new QNetworkAccessManager(this);
    connect(manager3, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);
    manager3->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              "count=100&"
                                               "access_token=%2").arg(-m_pos.key().toInt()).arg(m_token))));
    m_pos++;
    if(m_pos == m_storage->end()){
        emit finished();
        return;
    }
}

void GroupsUpdateWorker::replyFinished(QNetworkReply *reply)
{
    using QtJson::JsonObject;
    using QtJson::JsonArray;
    bool ok;
    JsonObject result = QtJson::parse(reply->readAll(), ok).toMap();
    Q_ASSERT(ok != false);
    JsonArray posts = result["response"].toList();
    uint lastTimeStamp = 0;
    if(posts.at(0).toInt() == 0){
        return;
    }
    QString wid = QString::number(-posts.at(1).toMap()["from_id"].toInt());
    (*m_storage)[wid].toMap()["posts"] = posts;
}
