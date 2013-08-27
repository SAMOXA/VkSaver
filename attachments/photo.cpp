#include "photo.h"
uint VkPhoto::pid() const
{
    return m_pid;
}

void VkPhoto::setPid(uint pid)
{
    m_pid = pid;
}

QString VkPhoto::srcBig() const
{
    return m_srcBig;
}

void VkPhoto::setSrcBig(const QString &srcBig)
{
    m_srcBig = srcBig;
}

QString VkPhoto::src() const
{
    return m_src;
}

void VkPhoto::setSrc(const QString &src)
{
    m_src = src;
}

VkPhoto::VkPhoto(uint pid, QString src, QString srcBig)
{
    m_pid = pid;
    m_src = src;
    m_srcBig = srcBig;
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
    Q_UNUSED(parent)
    return m_photos.count();
}

QVariant VkPhotoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_photos.count())
        return QVariant();

    const VkPhoto &photo = m_photos[index.row()];
    switch (role) {
    case PidRole:
        return photo.pid();
        break;
    case PreViewRole:
        return photo.src();
        break;
    case SrcRole:
        return photo.srcBig();
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
