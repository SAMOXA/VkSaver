import QtQuick 2.0
import VkSaver 1.0

Rectangle {
    id: main
    width: 400
    height: 640
    property variant pagesList : [
        "main",
        "GroupList",
        "Loading",
        "NotLoggedWindow",
        "GroupWall"
    ];
    property string  currentPage : "NotLoggedWindow";

    VkAgent{
        id: gate
        objectName: "gate"
        onPageChangedSignal: {
            currentPage = pageName;
        }
    }

    Repeater {
        model: pagesList;
        delegate: Loader {
            active: false;
            asynchronous: true;
            anchors.fill: parent;
            visible: (currentPage === modelData);
            source: "%1.qml".arg(modelData)
            onVisibleChanged:      { loadIfNotLoaded(); }
            Component.onCompleted: { loadIfNotLoaded(); }
            function loadIfNotLoaded () {
                if (visible && !active) {
                    active = true;
                }
            }
        }
    }
}
