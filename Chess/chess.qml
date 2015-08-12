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
        id: gameScreen
        anchors.fill: parent

        Component.onCompleted: {
            GameBoard.createGameBoard()
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
                id: gameBoard

                width: parent.width - 40
                height: parent.height - 40
                width: window.width - 40
                height: window.height - 80
                anchors.centerIn: parent

            }
        }

        Rectangle {
            id: actionBar
            width: window.width; height: 40
            anchors.bottom: gameScreen.bottom

            ActionMenu {
                id: actionMenu
                anchors.fill: parent

                btnStart.onClicked: GameBoard.startGame()
            }
        }
    }
}
