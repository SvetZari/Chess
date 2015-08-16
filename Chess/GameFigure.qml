import QtQuick 2.4
import QtQuick.Controls 1.3
import Chess.Figure 1.0

import "gameboard.js" as GameBoard

Item {
    id: root

    signal dragStarted
    signal dragFinished

    property int column: -1
    property int row: -1
    property int index: -1

    property int figure: Figure.Pawn
    property int side: Figure.White

    property var lastRoot: root

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        drag.target: tile
        onReleased: root.dragFinished()
        onPressed: root.dragStarted()


        Rectangle {
            id: tile

            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 32
            Drag.hotSpot.y: 32

            Image  {
                id: image
                source: loadImage(figure, side);
                fillMode: Image.PreserveAspectFit
                anchors.fill: parent
                anchors.margins: 2
            }

            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }
        }
    }

    function loadImage(figure, side) {
        var path = "";
        switch(figure) {
            case Figure.Pawn: path = "pawn"; break;
            case Figure.Bishop: path = "bishop"; break;
            case Figure.King: path = "king"; break;
            case Figure.Knight: path = "knight"; break;
            case Figure.Queen: path = "queen"; break;
            case Figure.Rook: path = "rook"; break;
            default: return path;
        }
        return "image/" + path + "_" + (side === Figure.White ? "white" : "black") + ".png";
    }
}
