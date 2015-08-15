import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item
{
    width: 400
    height: 40

    property alias btnStart: btnStart
    property alias btnLoad: btnLoad

    property alias btnStop: btnStop
    property alias btnSave: btnSave

    property alias btnPrev: btnPrev
    property alias btnNext: btnNext

    RowLayout {
        spacing: 50
        anchors.fill: parent

        Rectangle {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
        }

        Rectangle {
            id: menuStart
            width: 150
            Layout.fillHeight: true
            visible: true

            Button {
                id: btnStart
                text: qsTr("Start")
                anchors { left: parent.left; verticalCenter: parent.verticalCenter }
                onClicked: {
                    menuStart.visible = false;
                    menuGame.visible = true;
                    menuSavedGame.visible = false;
                }
            }

            Button {
                id: btnLoad
                text: qsTr("Load")
                anchors { right: parent.right; verticalCenter: parent.verticalCenter }
                onClicked: {
                    menuSavedGame.visible = true;
                }
            }
        }

        Rectangle {
            id: menuGame
            width: 150
            Layout.fillHeight: true
            visible: false

            Button {
                id: btnStop
                text: qsTr("Stop")
                anchors { left: parent.left; verticalCenter: parent.verticalCenter }
                onClicked: {
                    menuGame.visible = false;
                    menuSavedGame.visible = false;
                    menuStart.visible = true;
                }
            }

            Button {
                id: btnSave
                text: qsTr("Save")
                anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            }
        }

        Rectangle {
            id: menuSavedGame
            width: 150
            Layout.fillHeight: true
            visible: false

            Button {
                id: btnPrev
                text: qsTr("Prev")
                anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            }

            Button {
                id: btnNext
                text: qsTr("Next")
                anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            }
        }

        Rectangle {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
        }
    }
}
