import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Maintenance";
    property var mainWin;
    property int stk_depth;

    function stk_pop()
    {
        StackView.view.pop();
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("Maintenance");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Maintenance");
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
        border.color: "#FFF3A6"
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
                duration: 700;
                easing.type: Easing.InOutSine
            }

            NumberAnimation{
                id: any2
                target: rec;
                property: "border.width";
                from: 4;
                to: 1;
                duration: 700;
                easing.type: Easing.InOutSine
            }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FFF3A6"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        Image {
            id: img
            source: "./images/maintenance.svg"
            width: 400; height: 400;

            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit;

            layer.enabled: true;
            layer.effect: MultiEffect{
                shadowEnabled: true;
                shadowBlur: 1
                shadowColor: "#FFF3A6"
                shadowVerticalOffset: 0;
                shadowHorizontalOffset: 0;
            }

            RotationAnimation{
                target: img

                id: any_ro
                running: true;
                loops: Animation.Infinite
                from: 0;
                to: 360;
                duration: 5000;
            }
        }

        Label{
            id: lb_msg1
            text: "시스템을 보수 중 입니다";
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.top: img.bottom
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb_msg1_neon
            text: "시스템을 보수 중 입니다";
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill:  lb_msg1
            anchors.margins: -30

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
