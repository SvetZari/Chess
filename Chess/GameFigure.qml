import QtQuick 2.4
import QtQuick.Controls 1.3

import Figure 1.0
import Side 1.0

import "gameboard.js" as GameBoard

Item {
    id: root

    property int column: 0
    property int row: 0

    property int figure: ChessFigure.Pawn
    property int side: ChessSide.White

    property var lastRoot: root

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        drag.target: tile
        onReleased: {
            if(tile.Drag.target !== null)
                lastRoot = tile.Drag.target;
            parent = lastRoot;
        }

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
                source: "image/pawn_white.png"
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
            side = ChessSide.Black;
        else if(row == GameBoard.rows - 1 || row == GameBoard.rows - 2)
            side = ChessSide.White
        else
            return;

        if(row == 1 || row == GameBoard.rows - 2)
            figure = ChessFigure.Pawn
        else {
            if(column == 0 || column == GameBoard.columns - 1)
                figure = ChessFigure.Rook
            else if(column == 1 || column == GameBoard.columns - 2)
                figure = ChessFigure.Knight
            else if(column == 2 || column == GameBoard.columns - 3)
                figure = ChessFigure.Bishop
            else if(column == 3)
                figure = ChessFigure.Queen
            else if(column == 4)
                figure = ChessFigure.King
            else
                return;
        }

        image.source = getImageSource(figure, side);
    }

    function getImageSource(figure, side) {
        var path = "";

        switch(figure) {
        case ChessFigure.Pawn:
            path = "pawn";
            break;

        case ChessFigure.Bishop:
            path = "bishop";
            break;

        case ChessFigure.King:
            path = "king";
            break;

        case ChessFigure.Knight:
            path = "knight";
            break;

        case ChessFigure.Queen:
            path = "queen";
            break;

        case ChessFigure.Rook:
            path = "rook";
            break;

        default:
            return path;
        }

        return "image/" + path + "_" + (side == ChessSide.White ? "white" : "black") + ".png";
    }
}
