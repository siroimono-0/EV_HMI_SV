import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root

    BackGround_Card{
        id: back
        anchors.fill: parent
    }

    Component.onCompleted: {
        // cpp 에서 시리얼 통신 -> mcu에 님 값 주세요
        // 값 지속적으로 받고 특정 값 도달하면
        // 이제 그만보내?
        cpp_module.charging_start_To_serial();
    }

    function stop()
    {
        cpp_module.charging_stop_To_serial();
    }


    Image {
        id: img
        source: ""
        fillMode: Image.PreserveAspectFit
        width: 500; height: 300;
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Column{
        id: root_col1
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 200

        spacing: 20

        Item{
            width: 150; height: 40;
            Label{
                id: lb_col1
                text: "경과시간"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col1_neon
                text: "경과시간"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col1
                anchors.margins: -20

                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col2
                text: "남은시간";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col2_neon
                text: "남은시간";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col3
                text: "충전속도";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col3_neon
                text: "충전속도";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col4
                text: "충전량";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col4_neon
                text: "충전량";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col5
                text: "충전금액";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col5_neon
                text: "충전금액";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
        Column{
        id: root_col2
        anchors.left: root_col1.right
        anchors.leftMargin: 60
        anchors.top: parent.top
        anchors.topMargin: 200

        spacing: 20

        Item{
            width: 150; height: 40;
            Label{
                id: lb_col6
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.elapsed_time)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col6_neon
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.elapsed_time)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col1
                anchors.margins: -20

                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col7
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.remaining_time)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col7_neon
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.remaining_time)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col8
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_speed)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col8_neon
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_speed)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col9
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_capacity)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col9_neon
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_capacity)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
            width: 150; height: 40;
            Label{
                id: lb_col10
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_amount)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col10_neon
                text: (cpp_module && cpp_module.statStore)
                      ? String(cpp_module.statStore.charging_amount)
                      : "-"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true

                anchors.centerIn: parent
                // anchors.fill: lb_col2
                anchors.margins: -20

                horizontalAlignment: Text.AlignRight;
                verticalAlignment: Text.AlignVCenter;
                // horizontalAlignment: Text.AlignHCenter;
                // verticalAlignment: Text.AlignVCenter;

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
        id: btn
        width: 300; height: 120;

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.stop();
        }

        Label{
            id: lb2
            text: "중지"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb2_neon
            text: "중지"
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
}
