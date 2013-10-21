#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QObject>
#include <QStack>

class PageManager : public QObject
{
    Q_OBJECT
public:
    explicit PageManager(QObject *parent = 0);
    void pushPage(const QString pageName);
    QString popPage();
    void resetStack();
    void resetStack(const QString pageName);
private:
    QStack <QString> m_pageStack;
signals:
    
public slots:
    
};

#endif // PAGEMANAGER_H
