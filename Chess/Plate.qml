import QtQuick 2.4

Item {
    id: plate

    property int type: 0

    Rectangle {
        anchors.fill: parent
        color: type == 0 ? "white" : "black"
    }
}
