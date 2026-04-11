import QtQuick
import QtQuick.Controls
import Diagram 1.0
import QtQuick.Effects

Rectangle
{
    id: root
    property string set_text: "tmp"
    color: "transparent"
    border.color: "#FFFFFF"
    border.width: 2

    Component.onCompleted: {
        if(set_text === "Admin")
        {
            lb1.font.pixelSize = 30;
        }
    }

    layer.enabled: true
    layer.effect: MultiEffect {
        shadowEnabled: true
        shadowBlur: 1.0
        shadowColor: "#FFFFFF"
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
    }

    Label{
        id: lb1
        text: root.set_text
        font.pixelSize: 35
        anchors.centerIn: parent
        visible: root.visible
    }
}
