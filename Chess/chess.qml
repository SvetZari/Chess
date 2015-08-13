import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "gameboard.js" as GameBoard

ApplicationWindow {
    id: window
    title: "Chess"
    width: 630; height: 670;
    visible: true

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
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column
                                        index: dataModel.index

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: console.log(modelData.row);
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

                                    GameFigure
                                    {
                                        id: chessFigure
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column
                                        index: dataModel.index

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: console.log(chessFigure.figure);
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
                    chessManPack.model = GameBoard.getChessManModel();
                }
            }
        }
    }
}
