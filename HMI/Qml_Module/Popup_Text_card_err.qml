import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Rectangle{
    id: root
    color: "transparent"
    property int font_size: 40;

    function open(s)
    {
        root.state = "open";
        // pop_lb.text = s;
        // pop_lb_neon.text = s;
    }

    function set_font_size(set)
    {
        i_set = Math.ceil(set);
        pop_lb.font.pixelSize = i_set;
        pop_lb_neon.text = s;
    }


    state: "hide"

    states: [
        State {
            name: "hide"
            PropertyChanges {
                target: root
                visible: false;
            }
            PropertyChanges {
                target: root_recPop
                width: 0; height:0
                visible: false;
            }
            PropertyChanges {
                target: pop_lb
                visible: false;
            }
            PropertyChanges {
                target: pop_lb_neon
                visible: false;
            }
            PropertyChanges {
                target: btn_ok
                visible: false;
            }
            PropertyChanges {
                target:  mArea
                visible: false;
            }

        },
        State {
            name: "open"
            PropertyChanges {
                target: root
                visible: true;
            }
            PropertyChanges {
                target: root_recPop
                width: 1000; height:500
                visible: true;
            }
            PropertyChanges {
                target: pop_lb
                visible: true;
            }
            PropertyChanges {
                target: pop_lb_neon
                visible: true;
            }
            PropertyChanges {
                target: btn_ok
                visible: true;
            }
            PropertyChanges {
                target:  mArea
                visible: true;
            }
        }
    ]
    MouseArea{
        id: mArea
        anchors.fill: parent

        // 이벤트 처리했음 선언 모달 효과
        onPressed: function(o_ev) {
            o_ev.accepted = true;
        }

        onClicked: function(o_ev) {
            o_ev.accepted = true;
        }

        onReleased: function(o_ev) {
            o_ev.accepted = true;
        }
    }

    Rectangle{
        id: root_recPop
        anchors.centerIn: parent
        width: 0; height: 0;
        color: "#1e1e1e"
        radius: 10
        layer.enabled: true;
        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }

        Label{
            id: pop_lb
            text: "정산이 지연되고 있습니다"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.top: parent.top
            anchors.topMargin: 30
            // anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: pop_lb_neon
            text: "정산이 지연되고 있습니다"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.fill:  pop_lb
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

        Label{
            id: pop_lb2
            text: "자동으로 정산 완료 예정이나"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.top: pop_lb.bottom
            anchors.topMargin: 10;
            // anchors.horizontalCenter: parent.horizontalCenter

            anchors.left: parent.left
            anchors.leftMargin: 30;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: pop_lb2_neon
            text: "자동으로 정산 완료 예정이나"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.fill:  pop_lb2
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

        Label{
            id: pop_lb3
            text: "미정산 상태가 지속된다면"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.top: pop_lb2.bottom
            anchors.topMargin: 10
            // anchors.horizontalCenter: parent.horizontalCenter

            anchors.left: parent.left
            anchors.leftMargin: 30;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: pop_lb3_neon
            text: "미정산 상태가 지속된다면"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.fill:  pop_lb3
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

        Label{
            id: pop_lb4
            text: "고객센터로 연락 부탁드립니다"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.top: pop_lb3.bottom
            anchors.topMargin: 10
            // anchors.horizontalCenter: parent.horizontalCenter

            anchors.left: parent.left
            anchors.leftMargin: 30;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: pop_lb4_neon
            text: "고객센터로 연락 부탁드립니다"
            font.pixelSize: root.font_size
            font.family: "DIN"

            anchors.fill:  pop_lb4
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

        Image {
            id: img
            source: "../images/settlement_delay.svg"
            // width: 180; height: 162;

            anchors.left: pop_lb4.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            // anchors.rightMargin: 10
            anchors.top: parent.top
            // anchors.topMargin: 10

            fillMode: Image.PreserveAspectFit;

            layer.enabled: true;
            layer.effect: MultiEffect{
                shadowEnabled: true;
                shadowBlur: 1
                shadowColor: "#FFFFFF"
                shadowVerticalOffset: 0;
                shadowHorizontalOffset: 0;
            }

        }


        BtnGreen{
            id: btn_ok
            width: 250; height: 100;

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50

            onSig_Clicked: function()
            {
                root.state = "hide";
            }

            Label{
                id: lb2
                text: "확인"
                font.pixelSize: 60
                font.family: "DIN"

                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
            Label{
                id: lb2_neon
                text: "확인"
                font.pixelSize: 60
                font.family: "DIN"

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
}



