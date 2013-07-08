import QtQuick 2.0
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
        onFailed: {
            console.log('Login failed', error)
            Qt.quit()
        }
    }

    Component.onCompleted: {
        loginWindow.visible = true
        loginWindow.login()
    }
}
