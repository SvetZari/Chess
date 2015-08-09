import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item
{
    width: 300
    height: 50

    property alias btnStart: btnStart
    property alias btnLoad: btnLoad
    RowLayout
    {
        id: menuStart
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        visible: true

        Button
        {
            id: btnStart
            text: qsTr("Start")
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            anchors.leftMargin: 50
        }

        Button
        {
            id: btnLoad
            text: qsTr("Load")
            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            anchors.rightMargin: 50
        }
    }
}
