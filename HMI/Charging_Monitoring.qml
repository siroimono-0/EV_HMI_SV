import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property bool cancle_payment_stat: true;
    property string pageName: "Charging_Monitoring";
    property var mainWin;
    property int stk_depth;
    property bool ems_stat: false;
    property bool admin_stat: false;

    BackGround_Card{
        id: back
        anchors.fill: parent
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("충전 모니터링");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Charging_Monitoring");
        });

    }

    Component.onCompleted: {
        // cpp 에서 시리얼 통신 -> mcu에 님 값 주세요
        // 값 지속적으로 받고 특정 값 도달하면
        // 이제 그만보내?
        cpp_module.charging_start_To_serial();

        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    function stop_btn()
    {
        // 중지 버튼 눌렀으면 serial에 중지 요청
        // 버튼 안누르고 기다리면
        // 조건 만족시 cpp에서 검사해서 중지요청 보냄
        cpp_module.charging_stop_To_serial();
    }

    function admin_stop()
    {
        root.admin_stat = true;
        cpp_module.charging_stop_To_serial();
    }

    function ems_btn()
    {
        root.ems_stat = true;
        cpp_module.charging_stop_To_serial();
    }

    function stk_next()
    {
        if(root.ems_stat === true)
        {
            mainWin.stk_home();
            mainWin.stk_push_emsPage();
            return;
        }
        else if(root.admin_stat === true)
        {
            console.log("admin home");
            mainWin.stk_home();
        }
        else
        {
            StackView.view.push("Charging_Complet.qml", {cancle_payment_stat : cancle_payment_stat ,mainWin : mainWin});
        }
    }

    Connections{
        target: cpp_module

        // serial 에서 중지 요청 ack 확인했으면
        function onSig_charging_stop_ToQml()
        {
            // 릴레이 모듈 234코일 중지
            cpp_module.chargingConnecter_off_To_serial();
        }

        // 234코일 중지 확인 모드버스 받았으면
        function onSig_coil234_off_check_ToQml()
        {
            if(cpp_module.statStore.soc_connect_stat === false)
            {
                mainWin.netErr_charging_monitoring();
                return;
            }

            // 충전금액 정산
            // http sv 차액 결제 취소 요청
            cpp_module.set_payment_To_statStore();
        }

        // 신용 카드의 경우
        function onSig_cancle_payment_ok_ToQml(stat)
        {
            cpp_module.charging_finished_To_statStore();
        }

        // 멤버쉽 카드의 경우
        function onSig_cancle_payment_ok_member_ToQml(stat)
        {
            // 멤버쉽 카드 db 업데이트 결과
            // 다음 스택뷰에 넘겨줌
            root.cancle_payment_stat = stat;

            // charging_finished으로 세션 상태 업데이트
            // module -> statStore -> soc -> sv
            // -> http sv 승인취소 요청 -> 응답 확인 -> soc -> db
            // ack로 완료처리 응답 받고서 다음 페이지 진행
            cpp_module.charging_finished_To_statStore();
        }

        function  onSig_charging_finished_ack_ToQml()
        {
            root.stk_next();
        }
    }

    Label{
        id: lb_root
        text: "충전중"
        font.pixelSize: 75
        font.family: "DIN"
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_root_neon
        text: "충전중"
        font.pixelSize: 75
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill:  lb_root
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

    Rectangle{
        id: back_border
        color: "transparent"
        radius: 10;
        border.color: "#FFFFFF"
        border.width: 2;

        anchors.top: lb_p0.top
        anchors.topMargin: -30
        anchors.bottom: btn.top
        anchors.bottomMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 60
        anchors.right: parent.right
        anchors.rightMargin: 60


        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FFFFFF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        SequentialAnimation{
            loops: Animation.Infinite
            running: true;
            NumberAnimation{
                target: back_border
                properties: "opacity"
                from: 1; to: 0.1;
                duration: 1000;
            }
            NumberAnimation{
                target: back_border
                properties: "opacity"
                from: 0.1; to: 1;
                duration: 1000;
            }
        }

    }

    Label{
        id: lb_p0
        text: "0%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true
        anchors.left: rec_border.left
        // anchors.leftMargin: -40;
        anchors.bottom: rec_border.top
        anchors.bottomMargin: 5

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_p0_neon
        text: "0%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill: lb_p0
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
        id: lb_p1
        text: "50%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true
        anchors.horizontalCenter: rec_border.horizontalCenter
        anchors.bottom: rec_border.top
        anchors.bottomMargin: 5

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_p1_neon
        text: "50%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill: lb_p1
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
        id: lb_p2
        text: "100%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true
        anchors.right: rec_border.right
        // anchors.leftMargin: -70;
        anchors.bottom: rec_border.top
        anchors.bottomMargin: 5

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_p2_neon
        text: "100%"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill: lb_p2
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
        id: lb_battery_start
        text: "시작 ";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        anchors.top: rec_border.bottom
        anchors.topMargin: 30
        anchors.left: rec_border.left
        anchors.leftMargin: 10

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id:  lb_battery_start_neon
        text: "시작 ";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill:  lb_battery_start
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
        id: lb_battery_start2
        text: (cpp_module && cpp_module.statStore) ?  String (cpp_module.statStore.battery_start_persent) : "-";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        anchors.top: rec_border.bottom
        anchors.topMargin: 30
        anchors.left: lb_battery_start.right
        anchors.leftMargin: 30

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id:  lb_battery_start2_neon
        text: (cpp_module && cpp_module.statStore) ?  String (cpp_module.statStore.battery_start_persent) : "-";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill:  lb_battery_start2
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


    Rectangle{
        id: line_start

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left:  lb_battery_start.left
        // anchors.leftMargin: -15
        anchors.right:  lb_battery_start2.right;
        // anchors.rightMargin: -15
        anchors.top:  lb_battery_start.bottom
        anchors.topMargin: 2;
        // anchors.topMargin: 5

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

    Label{
        id:  lb_battery_current
        text: "현재 ";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        anchors.top: lb_battery_start.bottom
        anchors.topMargin: 20
        anchors.left: rec_border.left
        anchors.leftMargin: 10

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id:   lb_battery_current_neon
        text: "현재 ";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill:  lb_battery_current
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
        id:  lb_battery_current2
        text: (cpp_module && cpp_module.statStore) ?  String (cpp_module.statStore.battery_current) : "-";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        anchors.top: lb_battery_start.bottom
        anchors.topMargin: 20
        anchors.left: lb_battery_current.right
        anchors.leftMargin: 30

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id:   lb_battery_current2_neon
        text: (cpp_module && cpp_module.statStore) ?  String (cpp_module.statStore.battery_current) : "-";
        font.pixelSize: 45
        font.family: "DIN"
        font.bold: true

        // anchors.centerIn: parent
        anchors.fill:  lb_battery_current2
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

    Rectangle{
        id: line_current

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left:     lb_battery_current.left
        // anchors.leftMargin: -15
        anchors.right:       lb_battery_current2.right;
        // anchors.rightMargin: -15
        anchors.top:       lb_battery_current.bottom
        anchors.topMargin: 2;
        // anchors.topMargin: 5

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


    Rectangle{
        id: rec_border

        height: 150
        color: "transparent"
        radius: 10;
        border.color: "#8FE8FF"

        anchors.top: parent.top
        anchors.topMargin: 230
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: -30
        anchors.right: parent.right
        anchors.rightMargin: 100

        layer.enabled: true
        layer.effect: MultiEffect {

            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#00D9FF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        Rectangle{
            id: rec_in
            property string battery_current_p:
                (cpp_module && cpp_module.statStore)
                ? String(cpp_module.statStore.battery_current)
                : "-"


            width: (parent.width - 40) * cnv_int(battery_current_p) / 100;
            color: "#FFFFFF"
            radius: 10;
            border.color: "#FFFFFF"

            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            // anchors.fill: parent
            // anchors.margins: 20

            layer.enabled: true
            layer.effect: MultiEffect {

                shadowEnabled: true
                shadowBlur: 1.0
                shadowColor: "#00D9FF"
                shadowVerticalOffset: 0
                shadowHorizontalOffset: 0
            }

            function cnv_int(s)
            {
                let ss = s.slice(0, -1);
                return parseInt(ss,10);
            }

            /*
        Image {
        id: img
        source: "./images/voltage_green.svg"
        fillMode: Image.PreserveAspectFit

        // width: 500; height: 300;
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.left
        anchors.rightMargin: -140
        anchors.top: parent.top
        // anchors.topMargin:
        anchors.bottom: parent.bottom
        // anchors.bottomMargin: 10
    }
    */
        }
    }

    Rectangle{
        id: line1

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left: root_col1.left
        anchors.leftMargin: -15
        anchors.right: root_col2.right;
        anchors.rightMargin: -30
        anchors.top: root_col1.top
        anchors.topMargin: 45;
        // anchors.topMargin: 5

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

    Rectangle{
        id: line2

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left: root_col1.left
        anchors.leftMargin: -15
        anchors.right: root_col2.right;
        anchors.rightMargin: -30
        anchors.top: root_col1.top
        anchors.topMargin: 115
        // anchors.topMargin: 5

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

    Rectangle{
        id: line3

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left: root_col1.left
        anchors.leftMargin: -15
        anchors.right: root_col2.right;
        anchors.rightMargin: -30
        anchors.top: root_col1.top
        anchors.topMargin: 185
        // anchors.topMargin: 5

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

    Rectangle{
        id: line4

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left: root_col1.left
        anchors.leftMargin: -15
        anchors.right: root_col2.right;
        anchors.rightMargin: -30
        anchors.top: root_col1.top
        anchors.topMargin: 255
        // anchors.topMargin: 5

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

    Rectangle{
        id: line5

        height: 2;
        border.color: "#FFFFFF"
        border.width: 3
        anchors.left: root_col1.left
        anchors.leftMargin: -15
        anchors.right: root_col2.right;
        anchors.rightMargin: -30
        anchors.top: root_col1.top
        anchors.topMargin: 325
        // anchors.topMargin: 5

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


    Column{
        id: root_col1
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 230

        spacing: 30

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
        anchors.leftMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 230

        spacing: 30

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
        anchors.bottomMargin: 50;
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.stop_btn();
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
