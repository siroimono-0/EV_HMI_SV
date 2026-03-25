import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    // property bool cancle_payment_stat: true;
    property bool cancle_payment_stat: false;
    property string pageName: "Charging_Complet";
    property var mainWin;

    StackView.onActivated: {
        cpp_module.set_screen_name("충전 완료");
    }

    Component.onCompleted: {
        if(root.cancle_payment_stat === false)
        {
            console.log("root.cancle_payment_stat");
            /*pop.open("정산이 지연되고 있습니다\n
                    자동으로 정산 완료될 예정이나\n
                    미정산 상태가 지속된다면\n
                    고객센터로 연락 부탁드립니다\n
                    ");*/
            pop.open();
        }

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Charging_Complet");
        });
    }

    function stk_home()
    {
        // 충전 완료되었고 고객이 커넥터 원위치 한다고 가정함
        // 커넥터함 off  // 릴레이모듈 coil1 off
        cpp_module.chargingConnecter_close_To_serial();
        cpp_module.charging_end_stat_clear_To_statStore();

        while(StackView.view.depth > 2)
        {
            StackView.view.pop();
        }
    }


    BackGround_Card{
        id: background
        anchors.fill: parent
    }

    Popup_Text_card_err{
        id: pop;
        anchors.fill: parent
        // anchors.centerIn: parent
        z: 999;
    }

    Label{
        id: lb
        text: "충전이 완료되었습니다"
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
        id: lb_neon
        text: "충전이 완료되었습니다"
        font.pixelSize: 60
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


    Column{
        id: root_col1
        anchors.left: parent.left
        anchors.leftMargin: 250
        anchors.top: parent.top
        anchors.topMargin: 150

        spacing: 20

        Item{
            width: lb_col0.width; height: lb_col0.height;
            Label{
                id: lb_col0
                text: "충전률"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col0_neon
                text: "충전률"
                font.pixelSize: 45
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

                width: 830; height: 2;
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
            width: lb_col1.width; height: lb_col1.height;
            Label{
                id: lb_col1
                text: "경과시간"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
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
                id: line1

                width: 830; height: 2;
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
            width: lb_col2.width; height: lb_col2.height;
            Label{
                id: lb_col2
                text: "충전량"
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col2_neon
                text: "충전량"
                font.pixelSize: 45
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
                id: line2

                width: 830; height: 2;
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col3_neon
                text: "선결제 금액"
                font.pixelSize: 45
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

                width: 830; height: 2;
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col4_neon
                text: "결제취소 금액"
                font.pixelSize: 45
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

                width: 830; height: 2;
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col5_neon
                text: "실제청구 금액"
                font.pixelSize: 45
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

                width: 830; height: 2;
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
        anchors.top: parent.top
        anchors.topMargin: 150

        spacing: 20

        Item{
            width: lb_col00.width; height: lb_col00.height;
            Label{
                id: lb_col00
                text: (cpp_module && cpp_module.statStore) ?
                          String (cpp_module.statStore.battery_start_persent + " ▶ " + cpp_module.statStore.battery_current) : "-";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col00_neon
                text: lb_col00.text;
                font.pixelSize: 45
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
            width: lb_col11.width; height: lb_col11.height;
            Label{
                id: lb_col11
                text: (cpp_module && cpp_module.statStore) ?
                          String(cpp_module.statStore.elapsed_time) : "-";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col11_neon
                text: lb_col11.text
                font.pixelSize: 45
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
            width: lb_col22.width; height: lb_col22.height;
            Label{
                id: lb_col22
                text: (cpp_module && cpp_module.statStore) ?
                          String (cpp_module.statStore.charging_capacity) : "-";
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col22_neon
                text: lb_col22.text
                font.pixelSize: 45
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col33_neon
                text: lb_col33.text
                font.pixelSize: 45
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col44_neon
                text: lb_col44.text
                font.pixelSize: 45
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
                font.pixelSize: 45
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_col55_neon
                text: lb_col55.text
                font.pixelSize: 45
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
    BtnGreen{
        id: btn
        width: 300; height: 120;

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.stk_home();
        }

        Label{
            id: lb2
            text: "확인"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb2_neon
            text: "확인"
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
