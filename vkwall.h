#ifndef VKWALL_H
#define VKWALL_H

#include <QDateTime>
#include <QAbstractListModel>
#include "attachments/photo.h"

class VkWall
{
public:
    VkWall(int wid, QString text, uint timeStamp);
    ~VkWall();
    int wid() const;
    uint timeStamp() const;
    QString text() const;
    VkPhotoModel* photos() const;
    void setWid(int wid);
    void setTimeStamp(uint timeStamp);
    void setText(QString& text);
    void addPhoto(VkPhoto& photo);
private:
    int m_wid;
    uint m_timeStamp;
    QString m_text;
    VkPhotoModel* m_photos;
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
