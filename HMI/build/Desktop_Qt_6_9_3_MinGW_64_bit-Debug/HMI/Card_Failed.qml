import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root;
    property string err: ""

    StackView.onActivated: {
        cpp_module.set_screen_name("카드 인증 실패");
    }

    function stk_prev()
    {
        while(StackView.view.depth > 2)
        {
            StackView.view.pop();
        }
    }

    BackGround_Card{
        id: back;
        anchors.fill: parent
    }

    Label{
        id: lb
        text: root.err
        font.pixelSize: 40
        font.family: "DIN"
        font.bold: true
        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        text: root.err
        font.pixelSize: 40
        font.family: "DIN"
        font.bold: true

        anchors.fill: lb
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



    BtnGreen{
        id: btn
        width: 300; height: 120;
        anchors.top: lb.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.stk_prev();
        }

        Label{
            id: lb2
            text: "확인"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb2_neon
            text: "확인"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb2
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

}
