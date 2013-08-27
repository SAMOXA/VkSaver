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
    uint lastTimeStamp = 0;
    foreach (QVariant post, posts) {
        if(post.toMap().isEmpty()){
            continue;
        }
        auto wid = post.toMap()["id"].toInt();
        auto text = post.toMap()["text"].toString();
        auto timeStamp = post.toMap()["date"].toUInt();
        auto gid = post.toMap()["from_id"].toInt();
        if(lastTimeStamp == 0){
            lastTimeStamp = timeStamp;
        }
        auto wall = new VkWall(wid, text, timeStamp);
        JsonArray attachments = post.toMap()["attachments"].toList();
        foreach (QVariant attachment, attachments) {
            if(attachment.toMap()["type"] == "photo"){
                auto attachmentMap = attachment.toMap()["photo"].toMap();
                auto src = attachmentMap["src"].toString();
                auto pid = attachmentMap["pid"].toUInt();
                QString srcBig;
                if(attachmentMap.contains("src_xxxbig")){
                    srcBig = attachmentMap["src_xxxbig"].toString();
                }else if(attachmentMap.contains("src_xxbig")){
                    srcBig = attachmentMap["src_xxbig"].toString();
                }else if(attachmentMap.contains("src_xbig")){
                    srcBig = attachmentMap["src_xbig"].toString();
                }else {
                    srcBig = attachmentMap["src_big"].toString();
                }
                wall->addPhoto(*(new VkPhoto(pid, src, srcBig)));
            }
        }
        (*m_posts)[-gid]->addWall(*wall);
    }
}
