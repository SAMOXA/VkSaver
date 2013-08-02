#include "vkgroup.h"

VkGroup::VkGroup(QString _name, QString _photo)
{
    m_name = _name;
    m_photo = _photo;
}

QString VkGroup::Name() const
{
    return m_name;
}

void VkGroup::setName(const QString &_name)
{
    if(m_name != _name){
        m_name = _name;
    }
}

QString VkGroup::Photo() const
{
    return m_photo;
}

void VkGroup::setPhoto(const QString &_photo)
{
    if(m_photo != _photo){
        m_photo = _photo;
    }

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
    //emit countChanged(m_groups.count());
    //emit countChanged();
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
    if (role == NameRole)
        return group.Name();
    else if (role == PhotoRole)
        return group.Photo();
    return QVariant();
}

QHash<int, QByteArray> VkGroupModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PhotoRole] = "photo";
    return roles;
}
