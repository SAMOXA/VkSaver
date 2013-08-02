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
<<<<<<< HEAD
SOURCES += main.cpp \
    vkagent.cpp \
    vkgroup.cpp \
    json.cpp
=======
SOURCES += main.cpp
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

<<<<<<< HEAD
QMAKE_CXXFLAGS += -std=c++11

QT +=   webkit \
        network \
        xml

=======
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74
OTHER_FILES += \
    qml/VkSaver/URLQuery.js \
    qml/VkSaver/XHR.js \
    qml/VkSaver/LoginWindow.qml
<<<<<<< HEAD

HEADERS += \
    vkagent.h \
    vkgroup.h \
    json.h

RESOURCES += \
    res.qrc
=======
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74
