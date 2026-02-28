import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root

    StackView.onActivated: {
        cpp_module.set_screen_name("원화 입력");
    }

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
        // StackView.view.push("Select_card.qml", {charging_tpye: "won"}, {charging_val: s_int});
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

    Column{
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 320
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 400

        spacing: 20

        Row{
            spacing: 20
            RecBtn{
                id: btn1
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "1000";
                }

                Label{
                    id: lb1
                    text: "1,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb1_neon
                    text: "1,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb1
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
                id: btn2
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "3000";
                }

                Label{
                    id: lb2
                    text: "3,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb2_neon
                    text: "3,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb2
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
                id: btn3
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "5000";
                }

                Label{
                    id: lb3
                    text: "5,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb3_neon
                    text: "5,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb3
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

        Row{
            spacing: 20
            RecBtn{
                id: btn4
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "10000";
                }

                Label{
                    id: lb4
                    text: "10,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb4_neon
                    text: "10,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb4
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
                id: btn5
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "15000";
                }

                Label{
                    id: lb5
                    text: "15,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb5_neon
                    text: "15,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb5
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
                id: btn6
                width: 203; height: 100;

                onSig_Clicked: function()
                {
                    back.tf_text = "20000";
                }

                Label{
                    id: lb6
                    text: "20,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }
                Label{
                    id: lb6_neon
                    text: "20,000원"
                    color: "white"
                    font.pixelSize: 40
                    font.family: "DIN"
                    font.bold: true

                    anchors.fill: lb6
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
