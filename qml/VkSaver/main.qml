import QtQuick 2.0
<<<<<<< HEAD
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
=======
import 'URLQuery.js' as URLQuery
import 'XHR.js' as XHR

Rectangle {
    id: main

    property int userId: 21741326
    property var authToken

    width: 640
    height: 320


    function processLoginSuccess(token) {
        loginWindow.visible = false
        authToken = token
        visible = true
        console.log("Success")
        //setStatus()
    }

    function setStatus() {
        var params = {
            access_token: main.authToken,
            text: 'Тестирование QML OAuth'
        }

        function callback(request) {
            if (request.status == 200) {
                console.log('result', request.responseText)
                var result = JSON.parse(request.responseText)
                if (result.error) {
                    console.log('Error:', result.error.error_code,result.error.error_msg)
                } else {
                    console.log('Success')
                }
            } else {
                console.log('HTTP:', request.status, request.statusText)
            }

            Qt.quit()
        }

        XHR.sendXHR('POST', 'https://api.vk.com/method/status.set', callback, URLQuery.serializeParams(params))
    }

    LoginWindow {
        id: loginWindow
        applicationId: "3754205"
        permissions: 'status'
        visible: false
        onSucceeded: processLoginSuccess(token)
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74
        onFailed: {
            console.log('Login failed', error)
            Qt.quit()
        }
    }

<<<<<<< HEAD
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
=======
    Component.onCompleted: {
        loginWindow.visible = true
        loginWindow.login()
    }
>>>>>>> c951ebba88108b8a93b0fd044f6735f884ab6e74
}
