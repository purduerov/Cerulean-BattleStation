import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: thruster
    property string orientation
    property string value
    antialiasing: true
    width: 120
    height: 120
    property string thrusterColor: "#808080"

    Rectangle {
        id: propeller
        width: 80
        height: 40
        color: thrusterColor
        border.color: mainColor
        border.width: 3
        anchors.horizontalCenter: parent.horizontalCenter
        visible: (thruster.orientation == "horizontal")


    }

    Rectangle {
        height: 80
        anchors.top: propeller.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        width: 40
        color: thrusterColor
        border.color: mainColor
        border.width: 3
        visible: (thruster.orientation == "horizontal")
    }

    Rectangle {
        height: 80
        width: 80
        radius: 75
        color: thrusterColor
        border.color: mainColor
        border.width: 3
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: thruster.horizontalCenter
        visible: (thruster.orientation == "vertical")
    }

    Text {
        id: horizontalText
        text: thruster.value
        rotation: (thruster.rotation > 100) ? 180 : 0;
        anchors.verticalCenter: propeller.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16
        visible: (thruster.orientation == "horizontal")
    }

    Text {
        id: verticalText
        text: thruster.value
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16
        visible: (thruster.orientation == "vertical")
    }

}
