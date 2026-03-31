import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    property string pageName: "Charging_Ready";
    property var mainWin;
    property int stk_depth;

    StackView.onActivated: {
        cpp_module.set_screen_name("커넥터 연결 준비");

         // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Charging_Ready");
        });
    }

    Component.onCompleted: {
        // cpp에 rs485릴레이 모듈 1번코일 on 실행
        // ... 전기차 커넥터 보관함 문 열리는거임 ... ㅋㅋ..
        cpp_module.chargingConnecter_open_To_serial();

        // 정지 사유 초기화
        cpp_module.set_stop_reason("Local");

        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });
    }

    function stk_next()
    {
        // 확인버튼 눌렀으면 케넉터 연결했다고 가정함
        // 그럼 rs485릴레이 2..3..4 코일 on 실행
        // 코일 다 켜졌으면 cpp -> qml signal 발생해서 다음페이지
        StackView.view.push("Charging_Monitoring.qml", {mainWin : mainWin});
    }

    function coli_set()
    {
        // 확인버튼 눌렀으면 케넉터 연결했다고 가정함
        // 그럼 rs485릴레이 2..3..4 코일 on 실행
        // 코일 다 켜졌으면 cpp -> qml signal 발생해서 다음페이지
        cpp_module.chargingConnecter_ready_To_serial();
    }

    Connections{
        target: cpp_module

        // 코일 다켜짐 응답 받았으니 다음 페이지로
        function onSig_coil_ready_ok_ToQml()
        {
            root.stk_next();
        }
    }

    BackGround_Card{
        id: background
        anchors.fill: parent
    }

    Image {
        id: img
        source: "./images/charging_ready.svg"
        fillMode: Image.PreserveAspectFit
        width: 500; height: 300;
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        layer.enabled: true;
        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#00FFD0"
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }

    }

    Label{
        id: lb
        text: "결제가 완료되었습니다.\n커넥터를 연결하여 충전을 시작해주세요"
        font.pixelSize: 40
        font.family: "DIN"
        font.bold: true
        anchors.top: img.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        text: "결제가 완료되었습니다.\n커넥터를 연결하여 충전을 시작해주세요"
        font.pixelSize: 40
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



    BtnGreen{
        id: btn
        width: 300; height: 120;
        anchors.top: lb.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

        onSig_Clicked: function()
        {
            root.coli_set();
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
