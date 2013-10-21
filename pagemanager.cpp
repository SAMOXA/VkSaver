#include "pagemanager.h"

PageManager::PageManager(QObject *parent) :
    QObject(parent)
{
    m_pageStack.push(QString("NotLoggedWindow"));
}

void PageManager::pushPage(const QString pageName)
{
    m_pageStack.push(pageName);
}

QString PageManager::popPage()
{
    return m_pageStack.pop();
}

void PageManager::resetStack()
{
    QString temp = m_pageStack.pop();
    m_pageStack.clear();
    m_pageStack.push_back(temp);
}

void PageManager::resetStack(const QString pageName)
{
    m_pageStack.clear();
    m_pageStack.push_back(pageName);
}
