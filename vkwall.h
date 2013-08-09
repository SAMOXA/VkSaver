#ifndef VKWALL_H
#define VKWALL_H

#include <QDateTime>
#include <QAbstractListModel>

class VkWall
{
public:
    VkWall(int wid, QString& text, qint64 timeStamp);
    int Wid() const;
    qint64 TimeStamp() const;
    QString Text() const;
private:
    int m_wid;
    qint64 m_timeStamp;
    QString m_text;
};

class VkWallModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VkWallRopes {
        TimeStampRole = Qt::UserRole + 1,
        TextRole,
        WidRole
    };
    VkWallModel(QObject *parent = 0);
    void addWall(const VkWall& wall);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<VkWall> m_posts;
signals:
};

#endif // VKWALL_H
