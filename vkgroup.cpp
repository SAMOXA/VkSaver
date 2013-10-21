#include "vkgroup.h"

QString VkGroup::name() const
{
    return m_name;
}

VkGroup::VkGroup(int gid, QString name, QString photoUrl, bool closed)
{
    m_gid = gid;
    m_name = name;
    m_photoUrl = photoUrl;
    m_closed = closed;
}

void VkGroup::setName(const QString &_name)
{
    if(m_name != _name){
        m_name = _name;
    }
}

QString VkGroup::photoUrl() const
{
    return m_photoUrl;
}

void VkGroup::setPhoto(const QString &_photo)
{
    if(m_photoUrl != _photo){
        m_photoUrl = _photo;
    }
}

int VkGroup::gid() const
{
    return m_gid;
}

void VkGroup::setGid(int gid)
{
    m_gid = gid;
}

VkGroupModel::VkGroupModel(QObject *parent)
{
    Q_UNUSED(parent)
}
#include <QDebug>
void VkGroupModel::addGroup(const VkGroup& group)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_groups.push_back(group);
    endInsertRows();
}

int VkGroupModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_groups.count();
}

QVariant VkGroupModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_groups.count())
        return QVariant();

    const VkGroup &group = m_groups[index.row()];
    switch(role){
    case NameRole:
        return group.name();
        break;
    case PhotoRole:
        return group.photoUrl();
        break;
    case GidRole:
        return group.gid();
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> VkGroupModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PhotoRole] = "photo";
    roles[GidRole] = "gid";
    return roles;
}
