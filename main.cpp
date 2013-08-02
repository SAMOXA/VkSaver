#include <QtGui/QGuiApplication>
<<<<<<< HEAD
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "vkagent.h"
=======
#include "qtquick2applicationviewer.h"
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
<<<<<<< HEAD
    //QApplication::setApplicationName("VkSaver");
    //QApplication::setApplicationVersion("0.01a");
    VkAgent agent;
    QtQuick2ApplicationViewer viewer;
    qmlRegisterType<VkAgent>("VkSaver", 1, 0, "VkAgent");
    QQmlContext *root = viewer.rootContext();
    root->setContextProperty("groups", agent.groups());
    viewer.setMainQmlFile(QStringLiteral("qml/VkSaver/main.qml"));

    viewer.showExpanded();
=======

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/VkSaver/main.qml"));
    viewer.showExpanded();

>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74
    return app.exec();
}
