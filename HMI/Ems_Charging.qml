import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Ems_Charging";
    property var mainWin;
    property int stk_depth;
    property int font_size_0 : 30

    function stk_pop()
    {
        StackView.view.pop();
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("Ems_Charging");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
            mainWin.timer_reset("Ems_Charging");
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
            anchors.topMargin: -30
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

        Column{
            id: root_col1
            anchors.top: lb_msg1.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 250

            spacing: 10

            Item{
                width: lb_col0.width; height: lb_col0.height;
                Label{
                    id: lb_col0
                    text: "충전률"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col0_neon
                    text: "충전률"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
                Rectangle{
                    id: line0

                    width: 670; height: 2;
                    border.color: "#FFFFFF"
                    border.width: 3

                    anchors.top:  parent.bottom
                    anchors.topMargin: -5;

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
            Item{
                width: lb_col3.width; height: lb_col3.height;
                Label{
                    id: lb_col3
                    text: "선결제 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col3_neon
                    text: "선결제 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
                Rectangle{
                    id: line3

                    width: 670; height: 2;
                    border.color: "#FFFFFF"
                    border.width: 3
                    anchors.top:  parent.bottom
                    anchors.topMargin: -5;

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
            Item{
                width: lb_col4.width; height: lb_col4.height;
                Label{
                    id: lb_col4
                    text: "결제취소 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col4_neon
                    text: "결제취소 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
                Rectangle{
                    id: line4

                    width: 670; height: 2;
                    border.color: "#FFFFFF"
                    border.width: 3
                    anchors.top:  parent.bottom
                    anchors.topMargin: -5;

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
            Item{
                width: lb_col5.width; height: lb_col5.height;
                Label{
                    id: lb_col5
                    text: "실제청구 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col5_neon
                    text: "실제청구 금액"
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
                Rectangle{
                    id: line5

                    width: 670; height: 2;
                    border.color: "#FFFFFF"
                    border.width: 3
                    anchors.top:  parent.bottom
                    anchors.topMargin: -5;

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

        Column{
            id: root_col2
            anchors.left: root_col1.right
            anchors.leftMargin: 100
            anchors.top: lb_msg1.bottom
            anchors.topMargin: 20

            spacing: 10

            Item{
                width: lb_col00.width; height: lb_col00.height;
                Label{
                    id: lb_col00
                    text: (cpp_module && cpp_module.statStore) ?
                              String (cpp_module.statStore.battery_start_persent + " ▶ " + cpp_module.statStore.battery_current) : "-";
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col00_neon
                    text: lb_col00.text;
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
            Item{
                width: lb_col33.width; height: lb_col33.height;
                Label{
                    id: lb_col33
                    text: (cpp_module && cpp_module.statStore) ?
                              String(cpp_module.statStore.advance_payment) : "-";
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col33_neon
                    text: lb_col33.text
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
            Item{
                width: lb_col44.width; height: lb_col44.height;
                Label{
                    id: lb_col44
                    text: (cpp_module && cpp_module.statStore) ?  String(cpp_module.statStore.cancle_payment) : "-";
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col44_neon
                    text: lb_col44.text
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
            Item{
                width: lb_col55.width; height: lb_col55.height;
                Label{
                    id: lb_col55
                    text:(cpp_module && cpp_module.statStore) ?
                             String(cpp_module.statStore.actual_payment) : "-";
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true
                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb_col55_neon
                    text: lb_col55.text
                    font.pixelSize: root.font_size_0
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: parent
                    // anchors.fill: lb_col1
                    anchors.margins: -20

                    // horizontalAlignment: Text.AlignHCenter;
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
