import QtQuick 2.0

Rectangle {
    anchors.fill: parent;

    ListView {
        id: groupWall
        model: currentWall
        anchors.fill: parent
        delegate: Rectangle {
            width: parent.width
            //height: 100
            anchors.horizontalCenter: parent.horizontalCenter
            color: 'red'
            Column{
                Text {
                    width: parent.width - parent.spacing
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    renderType: Text.NativeRendering
                    text: "%1".arg(model.text)
                }
            }
//            Row {
//                anchors.fill: parent
//                spacing: 10
//                Image {
//                    id: image
//                    height: parent.height
//                    fillMode: Image.PreserveAspectFit
//                    source: model.photo
//                }


//                Text {
//                    width: parent.width - image.width - parent.spacing
//                    anchors.verticalCenter: parent.verticalCenter
//                    elide: Text.ElideRight
//                    renderType: Text.NativeRendering
//                    text: "%1".arg(name)
//                }
//            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
//                    console.log(model.gid)
//                    console.log(parent.currentPage)
                }
            }
            Component.onCompleted: {
                console.log(model)
            }
        }
        Component.onCompleted: {
//            console.log(gate)
//            console.log(gate.getCurrentGroup())

        }
    }
}
