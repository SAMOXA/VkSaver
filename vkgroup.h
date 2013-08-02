#ifndef VKGROUP_H
#define VKGROUP_H

#include <QObject>
#include <QAbstractListModel>

class VkGroup// : public QObject
{
    //Q_OBJECT
public:
    VkGroup(QString name, QString photo);
    void setName(const QString &_name);
    QString Name() const;
    void setPhoto(const QString &_photo);
    QString Photo() const;
private:
    QString m_name;
    QString m_photo;
    int m_gid;
    bool m_closed;
signals:

public slots:
    
};

class VkGroupModel : public QAbstractListModel
{
    Q_OBJECT
    //Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum VkGroupRoles {
        NameRole = Qt::UserRole + 1,
        PhotoRole
    };
    VkGroupModel(QObject *parent = 0);
    void addGroup(const VkGroup& group);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    //int count();
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<VkGroup> m_groups;
signals:
    //void countChanged();
};

#endif // VKGROUP_H
