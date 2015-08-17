import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0

import Chess.Logic 1.0
import Chess.Figure 1.0
import Chess.Move 1.0

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

                Move { id: currentMove }
                Connections {
                    target: controller
                    onChessmanChanged: {
                        chessBoardPack.active = false;
                        chessBoardPack.model = GameBoard.chessBoardModel()
                        chessBoardPack.active = true;

                        chessManPack.active = false;
                        chessManPack.model = controller.chessman;
                        chessManPack.active = true;
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    Grid {
                        id: chessBoardGrid
                        rows: GameBoard.rows; columns: GameBoard.columns;

                        Instantiator {
                            id: chessBoardPack
                            model: GameBoard.chessBoardModel()
                            onObjectAdded: object.parent = chessBoardGrid;

                            delegate: Component
                            {
                                Item {
                                    width: screen.getSize(); height: screen.getSize();
                                    property var dataModel: chessBoardPack.model[index]

                                    BoardPlate
                                    {
                                        id: boardPlate
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column

                                        onFigureEntered: {
                                            currentMove.rowTo = dataModel.row;
                                            currentMove.columnTo = dataModel.column;
                                            dropAllowed = controller.allowed(currentMove)
                                        }

                                        onFigureExited: {
                                            currentMove.rowTo = -1;
                                            currentMove.columnTo = -1;
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
                                    width: screen.getSize(); height: screen.getSize();
                                    property var dataModel: chessManPack.model[index]

                                    Text { text: chessFigure.row + " " + chessFigure.column + " " + index }

                                    GameFigure
                                    {
                                        id: chessFigure
                                        anchors.fill: parent
                                        row: dataModel.row
                                        column: dataModel.column
                                        figure: dataModel.figure
                                        side: dataModel.side

                                        onDragStarted: {
                                            currentMove.clear();
                                            currentMove.figure = chessFigure.figure;
                                            currentMove.side = chessFigure.side;
                                            currentMove.columnFrom = chessFigure.column;
                                            currentMove.rowFrom = chessFigure.row;
                                        }

                                        onDragFinished: {
                                             if(controller.allowed(currentMove))
                                                 controller.setCurrentMove(currentMove);
                                             else
                                                currentMove.clear();
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
                    controller.clear();
                    controller.initChessman();
                    chessManPack.active = false;
                    chessManPack.model = controller.chessman;
                    chessManPack.active = true;
                }

                btnStop.onClicked:  {
                    chessManPack.active = false;
                }

                btnSave.onClicked: {
                    controller.saveGame();
                }

                btnLoad.onClicked: {
                    controller.loadGame();
                }

                btnPrev.onClicked: {

                }

                btnNext.onClicked: {

                }
            }
        }
    }
}
