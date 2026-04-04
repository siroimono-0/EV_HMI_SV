import QtQuick
import HMI 1.0
import QtQuick.Controls
import QtMultimedia
import QtQuick.Effects

Item {
    id: root
    property string pageName: "HMI_main";
    property var mainWin;
    property int stk_depth;

    Component.onCompleted: function()
    {
        Qt.callLater(function(){
            root.stk_depth =  StackView.view.depth;
        });

        cpp_module.charging_type_clear_To_statStore();
        // 서버 연결 완료된 시점 storeId 확인대으로 이때에 갱신
        cpp_module.set_heartbit_storeId_hmiId();

        Qt.callLater(function(){
            cpp_module.first_ad_To_Soc();
        });
    }

    StackView.onActivated: {
        cpp_module.set_screen_name("Home");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("HMI_main");
        });
        player.play();
    }

    Connections{
        target: cpp_module

        function onSig_ad_play_ToQml()
        {
            player.play();
        }

    }

    function screen_stop()
    {
        player.stop();
    }

    BackGround{
        id: background
        anchors.fill: parent
    }

    Rectangle{
        id: screen;

        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 220


        color: "transparent"
        // radius: 10;
        border.color: "#FFFFFF"
        border.width: 2;

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FFFFFF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        /*
        SequentialAnimation{
            running: true;
            loops: Animation.Infinite
            NumberAnimation{
                target: screen
                properties: "border.width"
                from: 1;
                to: 3;
                duration: 500;
                easing.type: Easing.InOutSine
            }
            NumberAnimation{
                target: screen
                properties: "border.width"
                from: 3;
                to: 1;
                duration: 500;
                easing.type: Easing.InOutSine
            }
        }*/


        MediaPlayer{
            id: player
            source: (cpp_module && cpp_module.statStore) ?  String (cpp_module.statStore.cur_advertisement) : "-";

            loops: 1;
            videoOutput: videoOut
            audioOutput:  AudioOutput{}

            onMediaStatusChanged: function(status)
            {
                if(status === MediaPlayer.EndOfMedia)
                {
                    cpp_module.next_ad_To_statStore();
                }
            }
        }

        VideoOutput{
            id:videoOut
            // width: 500; height: 500;
            // source: player
            fillMode: VideoOutput.Stretch
            anchors.fill: parent
            anchors.margins: 2;
        }

    }

    BtnGreen{
        id: root_startBtn
        width: 300; height: 160;
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30;
        anchors.horizontalCenter: parent.horizontalCenter

        Label{
            id: btnText
            text: "시작하기"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id:  btnText_neon
            text: "시작하기"
            color: "white"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill:    btnText
            anchors.margins: -20;

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

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

        onSig_Clicked: function()
        {
            root.stk_next();
        }
    }

    function stk_next()
    {
        player.stop();
        StackView.view.push("Select_amount.qml", {mainWin : mainWin});
    }
}
