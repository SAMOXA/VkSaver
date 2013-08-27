#include "vkwall.h"

VkWall::VkWall(int wid, QString text, uint timeStamp)
{
    m_wid = wid;
    m_text = text;
    m_timeStamp = timeStamp;
    m_photos = 0;
    m_containPhoto = false;
}

VkWall::~VkWall()
{
    delete m_photos;
}

int VkWall::wid() const
{
    return m_wid;
}

uint VkWall::timeStamp() const
{
    return m_timeStamp;
}

QString VkWall::text() const
{
    return m_text;
}

VkPhotoModel* VkWall::photos() const
{
    return m_photos;
}

void VkWall::setWid(int wid)
{
    m_wid = wid;
}

void VkWall::setTimeStamp(uint timeStamp)
{
    m_timeStamp = timeStamp;
}

void VkWall::setText(QString &text)
{
    m_text = text;
}

void VkWall::addPhoto(VkPhoto &photo)
{
    if(m_photos == 0){
        m_photos = new VkPhotoModel();
        m_containPhoto = true;
    }
    m_photos->addPhoto(photo);
}

VkWallModel::VkWallModel(QObject *parent)
{
    Q_UNUSED(parent)
}

void VkWallModel::addWall(const VkWall &wall)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_posts.push_back(wall);
    endInsertRows();
}



int VkWallModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_posts.count();
}

QVariant VkWallModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_posts.count())
        return QVariant();

    const VkWall &post = m_posts[index.row()];
    switch (role) {
    case TextRole:
        return post.text();
        break;
    case TimeStampRole:
        return post.timeStamp();
        break;
    case WidRole:
        return post.wid();
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> VkWallModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "name";
    roles[TimeStampRole] = "date";
    roles[WidRole] = "wid";
    return roles;
}
