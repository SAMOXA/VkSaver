#ifndef VKAGENT_H
#define VKAGENT_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "json.h"
#include "vkgroup.h"

class VkAgent : public QObject
{
    Q_OBJECT
public:
    explicit VkAgent(QObject *parent = 0);
    Q_INVOKABLE
    void getGroups();
    Q_INVOKABLE
    void setToken(QString token);
    VkGroupModel *groups();

private:
    QString m_token;
    //Модель необходимо задавать извне ибо при экспорте объекта в QML создаётся новая копия объекта и изменения модели применяются к ней
    static VkGroupModel* m_groups;
signals:

public slots:

private slots:
    void replyFinished(QNetworkReply*);
};

#endif // VKAGENT_H
