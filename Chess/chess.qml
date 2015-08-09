import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "gameboard.js" as GameBoard

ApplicationWindow {
    title: "Chess"
    width: 630; height: 670;
    visible: true

    Rectangle {
        id: gameScreen
        anchors.fill: parent

        Component.onCompleted: {
            GameBoard.createGameBoard()
        }

        Item {
            width: parent.width
            anchors { top: parent.top; bottom: actionBar.top }

            Rectangle {
                id: background
                anchors.fill: parent
                color: "gray"
            }

            Item {
                id: gameBoard

                width: parent.width - 40
                height: parent.height - 40
                anchors.centerIn: parent

            }
        }

        Rectangle {
            id: actionBar
            width: parent.width; height: 40
            anchors.bottom: gameScreen.bottom

            ActionMenu {
                id: actionMenu
                anchors.fill: parent

                btnStart.onClicked: GameBoard.startGame()
            }
        }
    }
}
