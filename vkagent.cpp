#include "vkagent.h"
#include <QDebug>

VkGroupModel* VkAgent::m_groups = 0;

VkAgent::VkAgent(QObject *parent) :
    QObject(parent)
{
    if(m_groups == 0){
        m_groups = new VkGroupModel();
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
    foreach (QVariant group, groups) {
        //Пропуск элемента колличества
        if(group.toMap().isEmpty()){
            continue;
        }
        m_groups->addGroup(VkGroup(group.toMap()["name"].toString(), group.toMap()["photo_medium"].toString()));
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
