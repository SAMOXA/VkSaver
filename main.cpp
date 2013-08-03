#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "vkagent.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //QApplication::setApplicationName("VkSaver");
    //QApplication::setApplicationVersion("0.01a");
    VkAgent agent;
    QtQuick2ApplicationViewer viewer;
    qmlRegisterType<VkAgent>("VkSaver", 1, 0, "VkAgent");
    QQmlContext *root = viewer.rootContext();
    root->setContextProperty("groups", agent.groups());
    viewer.setMainQmlFile(QStringLiteral("qml/VkSaver/main.qml"));

    viewer.showExpanded();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/VkSaver/main.qml"));
    viewer.showExpanded();
    return app.exec();
}
