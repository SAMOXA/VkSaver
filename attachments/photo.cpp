#include "photo.h"

VkPhoto::VkPhoto(int pid, QString src, QString srcBig)
{
    m_pid = pid;
    m_src = src;
    m_srcBig = srcBig;
}

int VkPhoto::Pid() const
{
    return m_pid;
}

QString VkPhoto::Src() const
{
    return m_src;
}

QString VkPhoto::SrcBig() const
{
    return m_srcBig;
}


VkPhotoModel::VkPhotoModel(QObject *parent)
{
    Q_UNUSED(parent)
}

void VkPhotoModel::addPhoto(const VkPhoto &photo)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_photos.push_back(photo);
    endInsertRows();
}

int VkPhotoModel::rowCount(const QModelIndex &parent) const
{
   return m_photos.count();
}

QVariant VkPhotoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_photos.count())
        return QVariant();

    const VkPhoto &photo = m_photos[index.row()];
    switch (role) {
    case PidRole:
        return photo.Pid();
        break;
    case PreViewRole:
        return photo.Src();
        break;
    case SrcRole:
        return photo.SrcBig();
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> VkPhotoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PidRole] = "pid";
    roles[PreViewRole] = "preview";
    roles[SrcRole] = "src";
    return roles;
}
