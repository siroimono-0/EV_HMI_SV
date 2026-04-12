import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Select_amount";
    property var mainWin;
    property int stk_depth;

    Component.onCompleted: function()
    {

    }

    StackView.onActivated: {
        cpp_module.charging_type_clear_To_statStore();

        Qt.callLater(function(){
            // root.stk_depth =  StackView.view.depth;
            // root.stk_depth =  mainWin.;
        });

        cpp_module.set_screen_name("충전 방식 선택");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Select_amount");
        });
    }

    function stk_home()
    {
        while(root.stk_depth > 2)
        {
            mainWin.stk_pop();
            root.stk_depth--;
        }
    }

    function stk_prev()
    {
        StackView.view.pop()
    }

    function stk_next(s)
    {
        if(s === "time")
        {
            // StackView.view.push("Input_Time.qml", {mainWin : mainWin});
            StackView.view.push(mainWin.ld_Input_Time_item);
        }
        else if(s === "won")
        {
            // StackView.view.push("Input_Won.qml", {mainWin : mainWin});
            StackView.view.push(mainWin.ld_Input_Won_item);
        }
        else if(s === "kWh")
        {
            // StackView.view.push("Input_Kwh.qml", {mainWin : mainWin});
            StackView.view.push(mainWin.ld_Input_Kwh_item);
        }
        else if(s === "persent")
        {
            cpp_module.charging_type_To_statStore(s, 80);
            // StackView.view.push("Select_card.qml", {mainWin : mainWin});
            StackView.view.push(mainWin.ld_select_card_item);
        }
    }

    BackGround_Plus{
        id: background
        anchors.fill: parent
        onSig_stk_home: function()
        {
            root.stk_home();
        }

        onSig_stk_prev: function()
        {
            root.stk_prev();
        }
    }

    Label{
        id: root_lb
        text: "충전 방식을 선택하세요"
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
        text: "충전 방식을 선택하세요"
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
        id: root_time

        width: 295
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("time");
        }

        Image{
            id: img_time
            source: "./images/time.svg"
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
            id: lb_time
            text: "시간(분)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.top: img_time.bottom
            anchors.topMargin: 15;
            anchors.horizontalCenter: img_time.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: lb_time_neon
            text: "시간(분)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb_time
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
        id: root_won

        width: 295
        anchors.left: root_time.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("won");
        }

        Image{
            id: img_won
            source: "./images/won.svg"
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
            id: lb_won
            text: "충전금액(원)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.top: img_won.bottom
            anchors.topMargin: 15;
            anchors.horizontalCenter: img_won.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: lb_won_neon
            text: "충전금액(원)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb_won
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
        id: root_kw

        width: 295
        anchors.left: root_won.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("kWh");
        }

        Image{
            id: img_kw
            source: "./images/voltage.svg"
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
            id: lb_kw
            text: "전력량(kWh)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.top: img_kw.bottom
            anchors.topMargin: 15;
            anchors.horizontalCenter: img_kw.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: lb_kw_neon
            text: "전력량(kWh)"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb_kw
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
        id: root_p

        width: 295
        anchors.left: root_kw.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200

        onSig_Clicked: function()
        {
            root.stk_next("persent");
        }

        Image{
            id: img_p
            source: "./images/battery.svg"
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
            id: lb_p
            text: "80%까지 충전"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.top: img_p.bottom
            anchors.topMargin: 15;
            anchors.horizontalCenter: img_p.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: lb_p_neon
            text: "80%까지 충전"
            color: "white"
            font.pixelSize: 40
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb_p
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
}
