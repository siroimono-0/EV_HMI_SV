import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Card_Ready";
    property var mainWin;

    StackView.onActivated: {
        cpp_module.set_screen_name("카드 준비");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Card_Ready");
        });
    }

    Component.onCompleted: {
        }


    function stk_next()
    {
        StackView.view.push("Card_Socket.qml", {mainWin : mainWin});
    }

    BackGround_Card{
        id: background
        anchors.fill: parent
    }

    Image {
        id: card_img
        source: "./images/cardReady.svg"
        fillMode: Image.PreserveAspectFit
        width: 500; height: 300;
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label{
        id: lb
        text: "선결제 금액과 실제 충전금액이 다른 경우\n 차액만큼 결제 취소 처리됩니다\n(카드사 영업일 기준 1~7일 소요)"
        font.pixelSize: 40
        font.family: "DIN"
        font.bold: true
        anchors.top: card_img.bottom
        // anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        text: "선결제 금액과 실제 충전금액이 다른 경우\n 차액만큼 결제 취소 처리됩니다\n(카드사 영업일 기준 1~7일 소요)"
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
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.stk_next();
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
