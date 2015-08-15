import QtQuick 2.4
import QtQuick.Controls 1.3

import Logic 1.0

import "gameboard.js" as GameBoard

Item {
    id: root

    signal dragStarted
    signal dragFinished

    property int column: -1
    property int row: -1
    property int index: -1

    property int figure: Logic.Pawn
    property int side: Logic.White

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
                source: ""
                fillMode: Image.PreserveAspectFit
                anchors.fill: parent
                anchors.margins: 2
            }

            states: State {
                when: mouseArea.drag.active
                ParentChange { target: tile; parent: root }
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }
        }
    }

    /*
    1 king
    1 queen
    2 rook
    2 bishop
    2 knight
    8 pawn
    */
    function init() {
        if(row == 0 || row == 1)
            side = Logic.Black;
        else if(row == GameBoard.rows - 1 || row == GameBoard.rows - 2)
            side = Logic.White
        else
            return;

        if(row == 1 || row == GameBoard.rows - 2)
            figure = Logic.Pawn
        else {
            if(column == 0 || column == GameBoard.columns - 1)
                figure = Logic.Rook
            else if(column == 1 || column == GameBoard.columns - 2)
                figure = Logic.Knight
            else if(column == 2 || column == GameBoard.columns - 3)
                figure = Logic.Bishop
            else if(column == 3)
                figure = Logic.Queen
            else if(column == 4)
                figure = Logic.King
            else
                return;
        }

        image.source = getImageSource(figure, side);
    }

    function getImageSource(figure, side) {
        var path = "";

        switch(figure) {
        case Logic.Pawn:
            path = "pawn";
            break;

        case Logic.Bishop:
            path = "bishop";
            break;

        case Logic.King:
            path = "king";
            break;

        case Logic.Knight:
            path = "knight";
            break;

        case Logic.Queen:
            path = "queen";
            break;

        case Logic.Rook:
            path = "rook";
            break;

        default:
            return path;
        }

        return "image/" + path + "_" + (side == Logic.White ? "white" : "black") + ".png";
    }
}
