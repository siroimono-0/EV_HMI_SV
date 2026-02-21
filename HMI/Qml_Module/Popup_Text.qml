import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Rectangle{
    id: root
    color: "transparent"

    function open(s)
    {
        root.state = "open";
        pop_lb.text = s;
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
            text: ""
            font.pixelSize: 80
            font.family: "DIN"

            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: pop_lb_neon
            text: ""
            font.pixelSize: 80
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



