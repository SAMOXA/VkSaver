import QtQuick 2.0

Rectangle {
    signal login()
    Text {
        anchors.centerIn: parent
        color: "blue"
        font.underline: true
        font.pixelSize: 20
        id: clickToLogin
        text: qsTr("Click here to login")
        MouseArea{
            anchors.fill: parent
            onClicked:{
                login()
            }
        }
    }

}
