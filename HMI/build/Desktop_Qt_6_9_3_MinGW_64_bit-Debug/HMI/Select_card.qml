import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    // property string charging_type: "";
    property string pageName: "Select_card";
    property var mainWin;
    property int stk_depth;
    property int method;

    StackView.onActivated: {
        cpp_module.set_screen_name("카드 종류 선택");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Select_card");
        });

        Qt.callLater(function() {
            root.method = cpp_module.statStore.m_type;
            console.log(root.method);

            root.compare_method();
        });
    }

    Component.onCompleted: {
        // cppSv 카드리더기 상태 온
        cpp_module.set_card_stat_To_serial(true);
        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    function compare_method()
    {
        if(root.method === 0)
        {
            root_left.visible = true;
            root_right.visible = true;
        }
        else if(root.method === 1)
        {
            root_left.visible = true;
            root_right.visible = false;
        }
        else if(root.method === 2)
        {
            root_left.visible = false;
            root_right.visible = true;
        }
    }

    function stk_next(s)
    {
        if(s === "membershipCard")
        {
            cpp_module.set_card_type_To_statStore("membershipCard");
            cpp_module.set_card_type_To_serial("membershipCard");
            StackView.view.push("Card_Socket.qml", {mainWin : mainWin});
        }
        else if(s === "creditCard")
        {
            cpp_module.set_card_type_To_statStore("creditCard");
            cpp_module.set_card_type_To_serial("creditCard");
            StackView.view.push("Card_Ready.qml", {mainWin : mainWin});
        }
    }

    function stk_prev()
    {
        StackView.view.pop();
    }

    function stk_home()
    {
        while(root.stk_depth > 2)
        {
            mainWin.stk_pop();
            root.stk_depth--;
        }
    }

    BackGround_Plus{
        id: back
        anchors.fill: parent

        onSig_stk_prev: function(){
            root.stk_prev();
        }
        onSig_stk_home: function()
        {
            root.stk_home();
        }
    }

    Label{
        id: root_lb
        text: "결제 방식을 선택하세요"
        color: "white"
        font.pixelSize: 60
        font.family: "DIN"
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }
    Label{
        id: root_lb_neon
        text: "결제 방식을 선택하세요"
        color: "white"
        font.pixelSize: 60
        font.family: "DIN"
        font.bold: true

        anchors.fill:   root_lb
        anchors.margins: -20;

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        layer.enabled: true

        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
    }

    RecBtn{
        id: root_left

        anchors.left: parent.left
        anchors.leftMargin: 75
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("membershipCard");
        }

        Image{
            id: left_img
            source: "./images/memberCard.svg"
            fillMode: Image.PreserveAspectFit;
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 30

            layer.enabled: true;
            layer.effect: MultiEffect{
                shadowEnabled: true;
                shadowBlur: 1
                shadowColor: "#00FFD0"
                shadowVerticalOffset: 0;
                shadowHorizontalOffset: 0;
            }
        }

        Label{
            id: left_BtnText
            text: "회원인증"
            color: "white"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.top: left_img.bottom
            anchors.horizontalCenter: left_img.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: left_BtnText_neon
            text: "회원인증"
            color: "white"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill: left_BtnText
            anchors.margins: -20;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

            layer.enabled: true

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

    RecBtn{
        id: root_right

        anchors.right: parent.right
        anchors.rightMargin: 75
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("creditCard");
        }

        Image{
            id: right_img
            source: "./images/creditCard.svg"
            fillMode: Image.PreserveAspectFit;

            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 30

            layer.enabled: true;
            layer.effect: MultiEffect{
                shadowEnabled: true;
                shadowBlur: 1
                shadowColor: "#00FFD0"
                shadowVerticalOffset: 0;
                shadowHorizontalOffset: 0;
            }
        }

        Label{
            id: right_BtnText
            text: "신용카드"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.top: right_img.bottom
            anchors.horizontalCenter: right_img.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: right_BtnText_neon
            text: "신용카드"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill: right_BtnText
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
