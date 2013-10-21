#include "vkagent.h"
#include <QDebug>

QVariantMap VkAgent::storage;
dbManager* VkAgent::m_dbManager = 0;
PageManager VkAgent::m_pageManager;

VkAgent::VkAgent(QObject *parent) :
    QObject(parent)
{
    if(m_dbManager == 0){
        m_dbManager = new dbManager(QString("dbase.sqlite"));
    }
    m_currentGroupId = -1;
}

void VkAgent::replyFinished(QNetworkReply *reply)
{

    using QtJson::JsonObject;
    using QtJson::JsonArray;
    bool ok;
    JsonObject result = QtJson::parse(reply->readAll(), ok).toMap();
    Q_ASSERT(ok != false);
    JsonArray groups = result["response"].toList();
    //auto groupsFromDb = m_dbManager->getGroups();
    int i = 0;
    foreach (QVariant group, groups) {
        //Пропуск элемента колличества
        if(group.toMap().isEmpty()){
            continue;
        }
        QString gid = group.toMap()["gid"].toString();
        group.toMap()["positionFromVk"] = i;
        storage[gid] = group.toMap();
        storage[gid].toMap()["gid"] = gid.toInt();
        i++;
//        if(!groupsFromDb->contains(gid.toInt())){
//            m_dbManager->addGroup(gid, name, photoUrl);
//        }
        qApp->processEvents();
    }
    emit groupsListChanged();
    QThread* thread = new QThread;
    GroupsUpdateWorker* worker = new GroupsUpdateWorker(&storage, m_token);
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

void VkAgent::updateFromVk()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(QString("https://api.vk.com/method/groups.get?count=54&fields=photo_medium&extended=1&filter=publics&access_token=%1").arg(m_token))));
}

void VkAgent::setToken(QString token)
{
    m_token = token;
}

void VkAgent::getUpdates()
{
}

void VkAgent::pushPage(QString pageName)
{
    m_pageManager.pushPage(pageName);
    emit pageChangedSignal(pageName);
}

QString VkAgent::popPage()
{
    QString temp = m_pageManager.popPage();
    emit pageChangedSignal(temp);
    return temp;
}

void VkAgent::resetPageStack(QString newRootPageName)
{
    m_pageManager.resetStack(newRootPageName);
    emit pageChangedSignal(newRootPageName);
}

void VkAgent::swithToGroup(int gid)
{
    qDebug() << gid;
    m_currentGroupId = gid;
    qDebug() << QString::number(gid);
}

QVariantList VkAgent::getGroupsList()
{
    qDebug() << "Start";
    QVariantList rval;
    foreach (QVariant i, storage) {
        rval.insert(i.toMap()["positionFromVk"].toInt(), i);
    }
    qDebug() << "Stop";
    return rval;
}

QVariantList VkAgent::getGroupPosts()
{

}
