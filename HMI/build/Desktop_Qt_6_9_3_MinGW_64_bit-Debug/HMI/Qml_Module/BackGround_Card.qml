import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root

    BackGround{
        id: background
        anchors.fill: parent
    }

    Image {
        id: root_combo
        source: "../images/combo.svg"
        width: 180; height: 162;

        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 15
        fillMode: Image.PreserveAspectFit;

        layer.enabled: true;
        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#00FFD0"
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }

    }

}

