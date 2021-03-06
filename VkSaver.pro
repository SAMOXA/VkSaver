# Add more folders to ship with the application, here
folder_01.source = qml/VkSaver
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    vkagent.cpp \
    vkgroup.cpp \
    json.cpp \
    dbmanager.cpp \
    groupsupdateworker.cpp \
    vkwall.cpp \
    attachments/photo.cpp \
    pagemanager.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11

QT +=   webkit \
        network \
        xml \
        sql

OTHER_FILES += \
    qml/VkSaver/URLQuery.js \
    qml/VkSaver/XHR.js \
    qml/VkSaver/LoginWindow.qml

HEADERS += \
    vkagent.h \
    vkgroup.h \
    json.h \
    dbmanager.h \
    groupsupdateworker.h \
    vkwall.h \
    attachments/photo.h \
    pagemanager.h

RESOURCES += \
    res.qrc

