import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root

    function stk_home()
    {
        while(StackView.view.depth > 2)
        {
            StackView.view.pop();
        }
    }

    function stk_prev()
    {
        StackView.view.pop();
    }

    function stk_next(s_int)
    {
        cpp_module.charging_type_To_statStore("won", s_int);
        StackView.view.push("Select_card.qml");
    }

    BackGround_Amount{
        id: back
        unit_type: "원"

        anchors.fill: parent

        onSig_BtnHome_Cilcked: function()
        {
            root.stk_home();
        }

        onSig_BtnCancle_Cilcked: function()
        {
            root.stk_prev();
        }

        onSig_BtnOk_Cilcked: function(s)
        {
            let s_int = parseInt(s, 10);
            if(s === "")
            {
                pop.open("충전 금액을 \n입력해주세요")
            }
            else if(s_int < 1000)
            {
                pop.open("1000원 이상 \n충전 가능합니다")
            }
            else{
            root.stk_next(s_int);
            }
        }
    }

    Popup_Text{
        id: pop
        anchors.fill: parent
    }

    Label{
        id: lb
        text: "충전 금액을 입력하여 주세요"
        font.pixelSize: 50
        font.family: "DIN"
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: 50
        // anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        text: "충전 금액을 입력하여 주세요"
        font.pixelSize: 50
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
}
