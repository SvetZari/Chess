import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import Logic 1.0
import Figure 1.0


import "gameboard.js" as GameBoard

ApplicationWindow {
    id: window
    title: "Chess"
    width: 630; height: 670;
    visible: true

    Connections {
      target: controller
    }

    Rectangle {
        id: screen
        anchors.fill: parent

        function getSize() {
            return Math.min(scene.width/GameBoard.columns, scene.height/GameBoard.rows);
        }

        Item {
            width: window.width
            anchors { top: parent.top; bottom: actionBar.top }

            Rectangle {
                id: background
                anchors.fill: parent
                color: "gray"
            }

            Item {
                id: scene
                width: window.width - 40; height: window.height - 80;
                anchors.centerIn: parent

                Item
                {
                    id: currentMove
                    property int fromRow: -1
                    property int fromColumn: -1
                    property int toRow: -1
                    property int toColumn: -1
                    property int figure: -1
                    property int side: -1
                }

                Rectangle {
                    anchors.fill: parent
                    Grid {
                        id: chessBoardGrid
                        rows: GameBoard.rows; columns: GameBoard.columns;

                        Instantiator {
                            id: chessBoardPack
                            model: GameBoard.getChessBoardModel()
                            onObjectAdded: object.parent = chessBoardGrid;

                            delegate: Component
                            {
                                Item {
                                    width: screen.getSize();
                                    height: screen.getSize();
                                    property var dataModel: chessBoardPack.model[index]

                                    BoardPlate
                                    {
                                        id: boardPlate
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column

                                        onFigureEntered:
                                        {
                                            currentMove.toRow = dataModel.row;
                                            currentMove.toColumn = dataModel.column;

                                            controller.isAllowed(currentMove.toRow,
                                                               currentMove.toColumn,
                                                               currentMove.figure,
                                                               currentMove.side)
                                        }

                                        onFigureExited:
                                        {
                                            currentMove.toRow = -1;
                                            currentMove.toColumn = -1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Grid {
                        id: chessManGrid
                        rows: GameBoard.rows; columns: GameBoard.columns;

                        Instantiator {
                            id: chessManPack
                            model: null
                            onObjectAdded: object.parent = chessManGrid

                            delegate: Component
                            {
                                Item {
                                    Component.onCompleted: {chessFigure.init()}

                                    width: screen.getSize();
                                    height: screen.getSize();
                                    property var dataModel: chessManPack.model[index]

                                    Text
                                    {
                                        text: chessFigure.row + " " + chessFigure.column
                                    }

                                    GameFigure
                                    {
                                        id: chessFigure
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column

                                        onDragStarted:
                                        {
                                            currentMove.figure = chessFigure.figure;
                                            currentMove.side = chessFigure.side;
                                            currentMove.fromColumn = chessFigure.column;
                                            currentMove.fromRow = chessFigure.row;
                                        }

                                        onDragFinished:
                                        {
                                            if(currentMove.toRow > -1 && currentMove.toColumn > -1)
                                            controller.logMove(currentMove.toRow,
                                                               currentMove.toColumn,
                                                               currentMove.figure,
                                                               currentMove.side)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: actionBar
            width: window.width; height: 40
            anchors.bottom: screen.bottom

            ActionMenu {
                id: actionMenu
                anchors.fill: parent

                btnStart.onClicked: {
                    controller.initChessman();
                    chessManPack.model = "";
                    chessManPack.model = controller.chessman;
                }

                btnSave.onClicked:
                {
                }
            }
        }
    }
}
