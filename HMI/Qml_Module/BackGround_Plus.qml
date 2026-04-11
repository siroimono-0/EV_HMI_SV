import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    signal sig_stk_prev();
    signal sig_stk_home();

    BackGround{
        id: background
        anchors.fill: parent
    }

    Image {
        id: root_combo
        source: "../images/combo.svg"
        width: 180; height: 162;

        anchors.left: parent.left
        // anchors.leftMargin: 30
        anchors.top: parent.top
        // anchors.topMargin: 15
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

    BtnGreen{
        id: backBtn
        width: 350; height: 120;
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

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

        onSig_Clicked: function()
        {
            root.sig_stk_prev()
        }
    }

    BtnGreen{
        id: homeBtn
        width: 250; height: 100;
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 30

        Label{
            id: homeBtn_lb
            text: "HOME"
            font.pixelSize: 60
            font.family: "DIN"

            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: homeBtn_lb_neon
            text: "HOME"
            font.pixelSize: 60
            font.family: "DIN"

            anchors.fill:  homeBtn_lb
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

        onSig_Clicked: function()
        {
            root.sig_stk_home()
        }
    }
}

