import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2


ApplicationWindow {
    title: "Chess"
    width: 490; height: 400;
    visible: true

    Rectangle {
        id: gameScreen
        anchors.fill: parent

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
        }

        Rectangle {
            id: actionBar
            width: parent.width; height: 30
            anchors.bottom: gameScreen.bottom

            ActionMenu {
                id: actionMenu
                anchors.fill: parent
            }
        }
    }
}
