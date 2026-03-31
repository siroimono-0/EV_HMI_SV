import QtQuick
import QtQuick.Controls

Rectangle {
    id: root;
    property string text: ""
    property int text_size: 15

    signal sig_Clicked();

    width: 50
    height: 30
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

    Text {
        id: ttt
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: root.text_size
        font.family: "DIN"
        color: "#FFFFFF"
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
