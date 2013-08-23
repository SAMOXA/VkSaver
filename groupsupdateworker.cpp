#include "groupsupdateworker.h"
#include <QDebug>

GroupsUpdateWorker::GroupsUpdateWorker(QMap<int, VkWallModel *> *posts, QString token, QObject *parent) :
    QObject(parent)
{
    m_token = token;
    m_posts = posts;
    m_pos = m_posts->begin();
}

void GroupsUpdateWorker::proceed()
{
    QNetworkAccessManager *manager1 = new QNetworkAccessManager(this);
    connect(manager1, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);


    manager1->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              //"count=1&"
                                              "access_token=%2").arg(-m_pos.key()).arg(m_token))));
    m_pos++;
    if(m_pos == m_posts->end()){
        emit finished();
        return;
    }
    QNetworkAccessManager *manager2 = new QNetworkAccessManager(this);
    connect(manager2, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);
    manager2->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              //"count=1&"
                                              "access_token=%2").arg(-m_pos.key()).arg(m_token))));
    m_pos++;
    if(m_pos == m_posts->end()){
        emit finished();
        return;
    }
    QNetworkAccessManager *manager3 = new QNetworkAccessManager(this);
    connect(manager3, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)), Qt::QueuedConnection);
    manager3->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/wall.get?"
                                              "owner_id=%1&"
                                              //"extended=1&"
                                              //"count=1&"
                                              "access_token=%2").arg(-m_pos.key()).arg(m_token))));
    m_pos++;
    if(m_pos == m_posts->end()){
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
    uint timeStamp = 0;
    foreach (QVariant post, posts) {

        if(post.toMap().isEmpty()){
            continue;
        }
        if(timeStamp == 0){
            timeStamp = post.toMap()["date"].toUInt();
        }
        JsonArray attachments = post.toMap()["attachments"].toList();
        foreach (QVariant attachment, attachments) {
            qDebug() << attachment.toMap()["type"];
            qDebug() << "";
        }
        qDebug() << "";

//        if(attachments["type"] == "photo"){
//            qDebug() << attachments;
//
//        }
        (*m_posts)[-post.toMap()["from_id"].toInt()]->addWall(VkWall(post.toMap()["id"].toInt(), post.toMap()["text"].toString(), post.toMap()["date"].toUInt()));
    }
}
