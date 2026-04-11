import QtQuick
import QtQuick.Controls

Rectangle {
    id: root;
    property string text: ""
    property string text_2: ""
    property int text_size: 15

    signal sig_Clicked();

    width: 100
    height: 60
    radius: 10
    color: "transparent"
    border.color: "#DDDDDD"
    border.width: 2

    Behavior on scale {
        NumberAnimation{
            duration: 80
            easing.type: Easing.InOutQuad
        }
    }

    Rectangle{
        id: tmp1
        anchors.top: parent.top
        anchors.topMargin: 2;
        width: parent.width
        height: parent.height / 2
        color: "transparent"

        Text {
            id: ttt1
            anchors.centerIn: parent

            text: root.text
            font.pixelSize: root.text_size
            font.family: "DIN"
            color: "#FFFFFF"
        }
    }

    Rectangle{
        id: tmp2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2;
        width: parent.width
        height: parent.height / 2
        color: "transparent"

        Text {
            id: ttt2
            anchors.centerIn: parent

            text: root.text_2
            font.pixelSize: root.text_size
            font.family: "DIN"
            color: "#FFFFFF"
        }
    }

    MouseArea{
        anchors.fill: parent
        onPressed: {
            root.scale = 0.9;
        }
        onReleased: {
            root.scale = 1.0;
        }
        onClicked: {
            root.sig_Clicked();
        }
    }

}
