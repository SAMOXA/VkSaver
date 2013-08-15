#include "vkagent.h"
#include <QDebug>

VkGroupModel* VkAgent::m_groups = 0;
dbManager* VkAgent::m_dbManager = 0;
QMap <int, VkWallModel*> VkAgent::m_posts;

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
    Q_ASSERT(ok != false);
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
        m_groups->addGroup(VkGroup(gid, name, photoUrl, closed));
        if(!groupsFromDb->contains(gid)){
            m_dbManager->addGroup(gid, name, photoUrl);
        }
        VkWallModel* tempModel = new VkWallModel(this);
        m_posts.insert(gid, tempModel);
        qApp->processEvents();
    }
    QThread* thread = new QThread;
    GroupsUpdateWorker* worker = new GroupsUpdateWorker(&m_posts, m_token);
    worker->moveToThread(thread);
    //Таймер делается здесь ибо в другом потоке нет очереди событий
    QTimer* timer = new QTimer(0);
    timer->setInterval(1000);
    timer->moveToThread(thread);
    connect(timer, SIGNAL(timeout()), worker, SLOT(proceed()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(thread, SIGNAL(started()), timer, SLOT(start()));
    connect(worker, SIGNAL(finished()), timer, SLOT(stop()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), timer, SLOT(deleteLater()));
    thread->start();
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

void VkAgent::getUpdates()
{
}
