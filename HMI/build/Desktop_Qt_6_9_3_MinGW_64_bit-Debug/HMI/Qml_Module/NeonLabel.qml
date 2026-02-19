import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects

// 데모
Item{

    Label{
        id: backBtn_lb
        text: "이전 단계"
        font.pixelSize: 60
        font.family: "DIN"
        font.bold: true
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: backBtn_lb_neon
        text: "이전 단계"
        font.pixelSize: 60
        font.family: "DIN"
        font.bold: true

        anchors.fill:  backBtn_lb
        anchors.margins: -20

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        layer.enabled: true;

        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
    }


}
