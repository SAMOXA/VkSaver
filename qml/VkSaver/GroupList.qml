import QtQuick 2.0

Rectangle {
    anchors.fill: parent;

    ListView {
        id: groupView
        model: gate.groupsList
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
                    source: modelData.photo_medium
                }
                Column{
                    Text {
                        width: parent.width - image.width - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideRight
                        renderType: Text.NativeRendering
                        text: "%1".arg(modelData.name)
                    }
                }

                Text {
                    width: parent.width - image.width - parent.spacing
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    renderType: Text.NativeRendering
                    text: "%1".arg(modelData.name)
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    gate.swithToGroup(modelData.gid);
                    //gate.pushPage("GroupWall");
                }
            }
        }
    }
}
