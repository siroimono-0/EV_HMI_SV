import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Card_Socket";
    property var mainWin;
    property int stk_depth;

    StackView.onActivated: {
        cpp_module.set_screen_name("카드 삽입 및 인증");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Card_Socket");
        });

    }

    Component.onCompleted: {
        // 카드 인증 시리얼 통신 열음
        cpp_module.set_card_stat_To_serial(true);

        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    function stk_back()
    {
        cpp_module.set_card_stat_To_serial(false);

        if(cpp_module.get_card_type() === "membershipCard")
        {
            mainWin.stk_pop();
        }
        else
        {
            mainWin.stk_pop();
            mainWin.stk_pop();
        }
    }

    function card_authorized_success()
    {
        console.log("card_authorized_success()");
        // 카드 인증 시리얼 통신 막음
        cpp_module.set_card_stat_To_serial(false);

        // db 업데이트 요청 // 카드 인증 완료됨
        // statStore -> webSoc -> Sv -> db update
        cpp_module.chard_ok_To_statStore();
    }

    function stk_next()
    {
        StackView.view.push("Charging_Ready.qml", {mainWin : mainWin});
    }

    function stk_next_failed(msg)
    {
        cpp_module.set_card_stat_To_serial(false);
        StackView.view.push("Card_Failed.qml", {err: msg, mainWin : mainWin});
    }

    Connections{
        target: cpp_module

        function onSig_card_success_ToQml()
        {
            root.card_authorized_success();
        }

        function onSig_card_authorized_db_update_ack_ToQml()
        {
            root.stk_next();
        }

        function onSig_card_failed_ToQml(msg)
        {
            root.stk_next_failed(msg);
        }

        function onSig_card_compare_ToQml()
        {
            root_indicator.running = true;
            root_indicator.visible = true;
            btn.visible = false;
        }
    }

    BackGround_Card{
        id: background
        anchors.fill: parent
    }

    Image {
        id: card_img
        source: "./images/cardInsert.svg"
        fillMode: Image.PreserveAspectFit
        width: 500; height: 300;
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label{
        id: lb
        text: "카드를 단말기에 삽입해주세요"
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
        text: "카드를 단말기에 삽입해주세요"
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
            root.stk_back();
        }

        Label{
            id: lb2
            text: "취소"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb2_neon
            text: "취소"
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

    BusyIndicator{
        id: root_indicator
        width: 400; height: 400;
        running: false;
        visible: false;
        anchors.centerIn: parent
    }
}
