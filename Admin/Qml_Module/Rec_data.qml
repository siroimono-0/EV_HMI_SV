import QtQuick
import QtQuick.Controls

Rectangle {
    id: root;
    property string text: ""
    property int text_size: 15

    signal sig_Clicked();

    width: 50
    height: 30
    color: "transparent"
    border.color: "#DDDDDD"
    border.width: 1

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
        onClicked: {
            root.sig_Clicked();
        }
    }
}
