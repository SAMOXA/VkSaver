#ifndef PHOTO_H
#define PHOTO_H

#include <QString>
#include <QAbstractListModel>

class VkPhoto
{
public:
    VkPhoto(int pid, QString src, QString srcBig);
    int Pid() const;
    QString Src() const;
    QString SrcBig() const;
private:
    int m_pid;
    QString m_src;
    QString m_srcBig;
};

class VkPhotoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VkPhotoRopes {
        PidRole = Qt::UserRole + 1,
        PreViewRole,
        SrcRole
    };
    VkPhotoModel(QObject *parent = 0);
    void addPhoto(const VkPhoto& photo);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<VkPhoto> m_photos;
signals:
};


#endif // PHOTO_H
