import QtQuick 2.0

Rectangle {
    id: notLogged
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
                loginWindow.visible = true
                loginWindow.login()
                gate.pushPage("Loading")
                visible = false;
            }
        }
    }

    LoginWindow {
        id: loginWindow
        title: "Login Window"
        applicationId: "3754205"
        permissions: 'friends,photos,audio,video,docs,notes,pages,status,wall,groups,messages'
        onSucceeded: {
            processLoginSuccess(token)
            visible = false;
        }
    }

    Connections {
        target:gate
        onGroupsListChanged: {
            gate.resetPageStack("GroupList")
        }
    }

    function processLoginSuccess(token) {
        gate.setToken(token)
        gate.updateFromVk()
    }

}
