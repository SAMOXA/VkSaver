#include "vkwall.h"
#include <QDebug>

VkPost::VkPost(int wid, QString text, uint timeStamp)
{
    m_wid = wid;
    m_text = text;
    m_timeStamp = timeStamp;
    m_photos = 0;
    m_containPhoto = false;
}

VkPost::~VkPost()
{
    delete m_photos;
}

int VkPost::wid() const
{
    return m_wid;
}

uint VkPost::timeStamp() const
{
    return m_timeStamp;
}

QString VkPost::text() const
{
    return m_text;
}

VkPhotoModel* VkPost::photos() const
{
    return m_photos;
}

void VkPost::setWid(int wid)
{
    m_wid = wid;
}

void VkPost::setTimeStamp(uint timeStamp)
{
    m_timeStamp = timeStamp;
}

void VkPost::setText(QString &text)
{
    m_text = text;
}

void VkPost::addPhoto(VkPhoto &photo)
{
    if(m_photos == 0){
        m_photos = new VkPhotoModel();
        m_containPhoto = true;
    }
    m_photos->addPhoto(photo);
}

bool VkPost::containPhoto() const
{
    return m_containPhoto;
}

//VkWallModel::VkWallModel(VkPost* initData, QObject *parent)
//{
//    m_posts = initData;
//    Q_UNUSED(parent)
//}

void VkWallModel::addWall(const VkPost &wall)
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
    qDebug() << "Data";
    if (index.row() < 0 || index.row() >= m_posts.count())
        return QVariant();

    const VkPost &post = m_posts[index.row()];
    //TODO рефактировать в if return формат
    auto photosModel = post.photos();
    QVariantList photos;
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
    case PhotosRole:
        for(int i=0; i<photosModel->rowCount(); i++){
            photos.append(photosModel->data(photosModel->index(1), VkPhotoModel::PidRole));
        }
        return photos;
        break;
    case ContainPhotoRole:
        return post.containPhoto();
        break;
    default:
        return QVariant();
        break;
    }
}

//void VkWallModel::setNewModel(VkPost *newData)
//{
//}

QHash<int, QByteArray> VkWallModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "text";
    roles[TimeStampRole] = "date";
    roles[WidRole] = "wid";
    roles[PhotosRole] = "photos";
    roles[ContainPhotoRole] = "containPhoto";
    return roles;
}
