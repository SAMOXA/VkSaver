#include "vkagent.h"
#include <QDebug>

VkGroupModel* VkAgent::m_groups = 0;
dbManager* VkAgent::m_dbManager = 0;

VkAgent::VkAgent(QObject *parent) :
    QObject(parent)
{
    if(m_groups == 0){
        m_groups = new VkGroupModel();
    }
    if(m_dbManager == 0){
        m_dbManager = new dbManager(QString("dbase.sqlite"));
    }
}

VkGroupModel *VkAgent::groups()
{
    return m_groups;
}

void VkAgent::replyFinished(QNetworkReply *reply)
{
    using QtJson::JsonObject;
    using QtJson::JsonArray;
    bool ok;
    JsonObject result = QtJson::parse(reply->readAll(), ok).toMap();
    JsonArray groups = result["response"].toList();
    auto groupsFromDb = m_dbManager->getGroups();
    foreach (QVariant group, groups) {
        //Пропуск элемента колличества
        if(group.toMap().isEmpty()){
            continue;
        }
        auto gid = group.toMap()["gid"].toInt();
        auto name = group.toMap()["name"].toString();
        auto photoUrl = group.toMap()["photo_medium"].toString();
        auto closed = group.toMap()["is_closed"].toBool();
        qDebug() << group.toMap();
        m_groups->addGroup(VkGroup(gid, name, photoUrl, closed));
        if(!groupsFromDb->contains(gid)){
            m_dbManager->addGroup(gid, name, photoUrl);
        }
    }

}

void VkAgent::getGroups()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/groups.get?fields=photo_medium&extended=1&filter=publics&access_token=%1").arg(m_token))));
}

void VkAgent::setToken(QString token)
{
    m_token = token;
}
