import QtQuick 2.0
import 'URLQuery.js' as URLQuery
import 'XHR.js' as XHR

Rectangle {
    //ListModel { id: groups }
    function getUserGroups(authToken) {
        var params = {
            fields: 'photo_medium',
            //uid: main.userId,
            extended: 1,
            filter: "publics",
            access_token: authToken
        }
        console.debug(URLQuery.serializeParams(params))
//        function callback(request) {
//            if (request.status && request.status === 200) {
//                var result = JSON.parse(request.responseText)
//                for (var b in result.response) {
//                    var o = result.response[b];
//                    if(typeof o.photo_medium === 'undefined'){
//                        continue
//                    }
//                    //groups.append({photo_medium: o.photo_medium, name: o.name, screen_name: o.screen_name});
//                }
//                //gate.groupListReceved(groups)
//            } else {
//                console.log("HTTP:", request.status, request.statusText)
//            }
//        }
//        XHR.sendXHR('POST', 'https://api.vk.com/method/groups.get', callback, URLQuery.serializeParams(params))
    }
    anchors.fill: parent;

    ListView {
        id: groupView
        model: groups
        anchors.fill: parent
        delegate: Rectangle {
            width: groupView.width
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter
            color: 'white'
            Row {
                anchors.fill: parent
                spacing: 10
                Image {
                    id: image
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: photo
                }
                Column{
                    Text {
                        width: parent.width - image.width - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideRight
                        renderType: Text.NativeRendering
                        text: "%1".arg(name)
                    }
                }

                Text {
                    width: parent.width - image.width - parent.spacing
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    renderType: Text.NativeRendering
                    text: "%1".arg(name)
                }
            }
        }
    }
}
