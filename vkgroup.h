#ifndef VKGROUP_H
#define VKGROUP_H

#include <QObject>
#include <QAbstractListModel>
#include <QImage>

class VkGroup
{
public:
    VkGroup(int gid, QString name, QString photoUrl, bool closed = false);
    void setName(const QString &_name);
    QString name() const;
    void setPhoto(const QString &_photo);
    QString photoUrl() const;
    int gid() const;
    void setGid(int gid);
private:
    QString m_name;
    QString m_photoUrl;
    QImage m_photo;
    int m_gid;
    bool m_closed;
    bool m_new;
    int m_changeCount;
signals:

public slots:
    
};

class VkGroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VkGroupRoles {
        NameRole = Qt::UserRole + 1,
        PhotoRole,
        GidRole
    };
    VkGroupModel(QObject *parent = 0);
    void addGroup(const VkGroup& group);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<VkGroup> m_groups;
signals:
};

#endif // VKGROUP_H
