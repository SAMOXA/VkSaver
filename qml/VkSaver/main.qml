import QtQuick 2.0
import VkSaver 1.0
import 'URLQuery.js' as URLQuery
import 'XHR.js' as XHR


Rectangle {
    id: main
    VkAgent{
        id: gate
        objectName: "gate"
    }
    property var authToken

    width: 400
    height: 640

    LoginWindow {
        id: loginWindow
        title: "Login Window"
        applicationId: "3754205"
        permissions: 'status'
        onSucceeded: {
            processLoginSuccess(token)
            main.state = "groupList"
        }
    }
    NotLoggedWindow {
        id: notLoggedWindow
        anchors.fill: parent
        onLogin: {
            loginWindow.login()
            main.state = "logging"
        }
    }
    AnimatedImage  {
        id: loadingImage
        source: "qrc:qml/image/loading.gif"
        anchors.centerIn: parent
    }

    GroupList {
        id: groupList
    }

    function processLoginSuccess(token) {
        gate.setToken(token)
        gate.getGroups()
        main.state = "groupList"
    }

    state: "notLogged"

    states: [
        State {
            name: "notLogged"
            PropertyChanges { target: notLoggedWindow; visible: true }
            PropertyChanges { target: loadingImage; visible: false }
            PropertyChanges { target: groupList; visible: false }
            PropertyChanges { target: loginWindow; visible: false }
        },
        State {
            name: "logging"
            PropertyChanges { target: notLoggedWindow; visible: false }
            PropertyChanges { target: loadingImage; visible: true }
            PropertyChanges { target: groupList; visible: false }
            PropertyChanges { target: loginWindow; visible: true }
        },
        State {
            name: "groupList"
            PropertyChanges { target: notLoggedWindow; visible: false }
            PropertyChanges { target: loadingImage; visible: false }
            PropertyChanges { target: groupList; visible: true }
            PropertyChanges { target: loginWindow; visible: false }
        }
    ]
}
