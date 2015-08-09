import QtQuick 2.4

Item {
    id: plate

    property int column: 0
    property int row: 0

    Rectangle {
        anchors.fill: parent
        color: (column + row) % 2 == 0 ? "lightGray" : "darkGray"
    }
}
