#ifndef VKWALL_H
#define VKWALL_H

#include <QDateTime>
#include <QAbstractListModel>
#include "attachments/photo.h"

class VkPost
{
public:
    VkPost(int wid, QString text, uint timeStamp);
    ~VkPost();
    int wid() const;
    uint timeStamp() const;
    QString text() const;
    VkPhotoModel* photos() const;
    void setWid(int wid);
    void setTimeStamp(uint timeStamp);
    void setText(QString& text);
    void addPhoto(VkPhoto& photo);
    bool containPhoto() const;
private:
    int m_wid;
    uint m_timeStamp;
    QString m_text;
    VkPhotoModel* m_photos;
    bool m_containPhoto;
};

class VkWallModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VkWallRopes {
        TimeStampRole = Qt::UserRole + 1,
        TextRole,
        WidRole,
        PhotosRole,
        ContainPhotoRole
    };
    VkWallModel(QObject *parent = 0);
    void addWall(const VkPost& wall);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<VkPost> m_posts;
signals:
};

#endif // VKWALL_H
