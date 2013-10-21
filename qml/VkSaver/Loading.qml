import QtQuick 2.0

Rectangle{
    width: 400
    height: 640
    AnimatedImage  {
        width: 300
        height: 300
        id: loadingImage
        source: "qrc:qml/image/loading.gif"
        anchors.centerIn: parent
    }
}
