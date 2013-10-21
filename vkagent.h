//TODO Удаление групп

#ifndef VKAGENT_H
#define VKAGENT_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThread>
#include <QMap>
#include <QQmlContext>
#include "json.h"
#include "dbmanager.h"
#include "groupsupdateworker.h"
#include "pagemanager.h"
#include "qtquick2applicationviewer.h"

class VkAgent : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QVariantList groupsList READ getGroupsList NOTIFY groupsListChanged)
    Q_PROPERTY(QVariantList groupPosts READ getGroupPosts NOTIFY groupPostsChanged)

    VkAgent(QObject *parent = 0);
    Q_INVOKABLE
    void updateFromVk();
    Q_INVOKABLE
    void setToken(QString token);
    Q_INVOKABLE
    void getUpdates();

    Q_INVOKABLE
    void pushPage(QString pageName);
    Q_INVOKABLE
    QString popPage();
    Q_INVOKABLE
    void resetPageStack(QString newRootPageName);

    Q_INVOKABLE
    void swithToGroup(int gid);

    Q_INVOKABLE
    QVariantList getGroupsList();
    Q_INVOKABLE
    QVariantList getGroupPosts();


private:
    QString m_token;
    //Модель необходимо задавать извне ибо при экспорте объекта в QML создаётся
    //новая копия объекта и изменения модели применяются к ней
    static dbManager* m_dbManager;
    static PageManager m_pageManager;
    QThread workThread;
    static QVariantMap storage;
    int m_currentGroupId;

signals:
    void pageChangedSignal(QString pageName);
    void groupsListChanged();
    void groupPostsChanged();
public slots:

private slots:
    void replyFinished(QNetworkReply*);
};

#endif // VKAGENT_H
