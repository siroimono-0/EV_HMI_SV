import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Ems_Nomal";
    property var mainWin;
    property int stk_depth;

    function stk_pop()
    {
        StackView.view.pop();
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("Ems_Nomal");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Ems_Nomal");
        });
    }

    Component.onCompleted: {
        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    BackGround{
        id: back
        anchors.fill: parent
    }

    Rectangle{
        id: rec
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        color: "#1e1e1e"
        radius: 10
        border.color: "#FF2D3D"
        border.width: 1;

        SequentialAnimation{
            running: true;
            loops: Animation.Infinite
            NumberAnimation{
                id: any1
                target: rec;
                property: "border.width";
                from: 1;
                to: 4;
                duration: 500;
                easing.type: Easing.InOutSine
            }

            NumberAnimation{
                id: any2
                target: rec;
                property: "border.width";
                from: 4;
                to: 1;
                duration: 500;
                easing.type: Easing.InOutSine
            }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FF2D3D" // 레드 글로우
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        Image {
            id: warning
            source: "./images/warning.svg"
            width: 300; height: 300;

            anchors.top: parent.top
            // anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit;

            layer.enabled: true;
            layer.effect: MultiEffect{
                shadowEnabled: true;
                shadowBlur: 1
                shadowColor: "#FF2D3D"
                shadowVerticalOffset: 0;
                shadowHorizontalOffset: 0;
            }

            SequentialAnimation{
                running: true;
                loops: Animation.Infinite
                NumberAnimation{
                    id: any3
                    target:  warning;
                    property: "opacity";
                    from: 1;
                    to: 0.1;
                    duration: 700;
                    easing.type: Easing.InOutSine
                }

                NumberAnimation{
                    id: any4
                    target:  warning;
                    property: "opacity";
                    from: 0.1;
                    to: 1;
                    duration: 700;
                    easing.type: Easing.InOutSine
                }
            }
        }

        Label{
            id: lb_msg1
            text: "긴급 정지 버튼 활성화";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.top: warning.bottom
            anchors.topMargin: -10
            anchors.horizontalCenter: parent.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb_msg1_neon
            text: "긴급 정지 버튼 활성화";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.fill:  lb_msg1
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
            id: lb_msg2
            text: "설비에 문제가 있다면";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.top: lb_msg1.bottom
            // anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb_msg2_neon
            text: "설비에 문제가 있다면";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.fill:  lb_msg2
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
            id: lb_msg3
            text: "고객 센터로 연락 부탁드립니다";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.top: lb_msg2.bottom
            // anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb_msg3_neon
            text: "고객 센터로 연락 부탁드립니다";
            font.pixelSize: 45
            font.family: "DIN"
            font.bold: true

            anchors.fill:  lb_msg3
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

        BtnLed{
            id: btn_ok
            width: 250; height: 100;

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onSig_Clicked: {
                root.stk_pop();
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
