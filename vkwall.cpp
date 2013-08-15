#include "vkwall.h"

VkWall::VkWall(int wid, QString text, uint timeStamp)
{
    m_wid = wid;
    m_text = text;
    m_timeStamp = timeStamp;
}

int VkWall::Wid() const
{
    return m_wid;
}

uint VkWall::TimeStamp() const
{
    return m_timeStamp;
}

QString VkWall::Text() const
{
    return m_text;
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
        return post.Text();
        break;
    case TimeStampRole:
        return post.TimeStamp();
        break;
    case WidRole:
        return post.Wid();
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
