import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root;
    property string err: ""
    property int font_size: 40
    property string pageName: "Card_Failed";
    property var mainWin;
    property int stk_depth;

    StackView.onActivated: {
        cpp_module.set_screen_name("카드 인증 실패");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Card_Failed");
        });

    }

    Component.onCompleted: {
        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    function stk_prev()
    {
        while(root.stk_depth > 2)
        {
            mainWin.stk_pop();
            root.stk_depth--;
        }
    }

    BackGround_Card{
        id: back;
        anchors.fill: parent
    }

    Label{
        id: lb
        text: root.err
        font.pixelSize: root.font_size
        font.family: "DIN"
        font.bold: true
        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        text: root.err
        font.pixelSize: root.font_size
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
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
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
