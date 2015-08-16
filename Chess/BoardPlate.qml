import QtQuick 2.4

Item {
    id: root

    signal figureEntered;
    signal figureExited;

    property int column: -1
    property int row: -1

    Rectangle {
        id: plate
        anchors.fill: parent
        color: (column + row) % 2 == 0 ? "lightGray" : "darkGray"
    }

    DropArea {
        id: dragTarget
        anchors.fill: parent
        onEntered: root.figureEntered()
        onExited: root.figureExited()
    }
}
