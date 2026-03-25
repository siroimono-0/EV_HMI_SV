import QtQuick
import HMI 1.0
import QtQuick.Controls

Item {
    id: root
    property string pageName: "HMI_main";
    property var mainWin;

    Component.onCompleted: function()
    {
        cpp_module.charging_type_clear_To_statStore();
        // 서버 연결 완료된 시점 storeId 확인대으로 이때에 갱신
        cpp_module.set_heartbit_storeId_hmiId();
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("Home");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("HMI_main");
        });
    }

    BackGround{
        id: background
        anchors.fill: parent
    }

    RecBtn{
        id: root_startBtn
        width: 300; height: 180;
        anchors.centerIn: parent

        Label{
            id: btnText
            text: "시작하기"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        onSig_Clicked: function()
        {
            root.stk_next();
        }
    }

    function stk_next()
    {
        StackView.view.push("Select_amount.qml", {mainWin : mainWin});

    }
}
