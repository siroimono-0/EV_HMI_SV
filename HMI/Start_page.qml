import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent
    property string id: "";
    property string pageName: "Start_page";
    property var mainWin;

    StackView.onActivated: {
        cpp_module.set_screen_name("관리자 로그인");

        // home화면 이동 타이머 초기화
        Qt.callLater(function() {
        mainWin.timer_reset("Start_page");
        });
    }

    Component.onCompleted: {

        // console.log(root.pageName + " ____ " +  StackView.view.depth+ "  ___________");
    }

    BackGround{
        id: background
        anchors.fill: parent
    }

    Rectangle{
        id: root_Keypad
        anchors.centerIn: parent
        width: 0; height: 0;
        visible: false;
        opacity: 0;

        state: "hide"

        BackGround{
            id: keypad_back
            bottom_text_visible: false
            anchors.fill: parent
        }

        TextField{
            id: keypad_tf
            height: 100;
            font.pixelSize: 80;
            font.family: "DIN";
            font.bold: true;
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            activeFocusOnPress: false;

            background: Rectangle{
                radius: 10
                color: "transparent"

                border.color: "#8FE8FF"
                border.width: 2;

                layer.enabled: true
                layer.effect: MultiEffect {

                    shadowEnabled: true
                    shadowBlur: 1.0
                    shadowColor: "#00D9FF"
                    shadowVerticalOffset: 0
                    shadowHorizontalOffset: 0
                }
            }

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
        }

        Keypad_Number{
            id: keypad_number
            anchors.top: keypad_tf.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 40

            onSig_btnClicked: function(s)
            {
                if(s === "<<")
                {
                    keypad_tf.text = keypad_tf.text.slice(0,-1);
                }
                else if(s === "delete")
                {
                    keypad_tf.clear();
                }
                else
                {
                    keypad_tf.text += s;
                }
            }
        }

        states: [
            State {
                name: "hide"
                PropertyChanges {
                    target: root_Keypad
                    width: 0; height: 0;
                    opacity: 0; z: -999;
                    visible: false;
                }
            },
            State {
                name: "open"
                PropertyChanges {
                    target: root_Keypad
                    width: 1280; height: 800
                    opacity: 1; z: 999;
                    visible: true;
                }
            }
        ]


        BtnGreen{
            id: okBtn
            width: 500; height: 200;

            anchors.top: keypad_number.bottom
            anchors.topMargin: 30;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 30;
            anchors.left: parent.left
            anchors.leftMargin: 40

            Label{
                id: lb
                text: "확인"
                font.pixelSize: 50
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                // anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb_neon
                text: "확인"
                font.pixelSize: 50
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

            onSig_Clicked:function()
            {
                root.id = keypad_tf.text
                keypad_tf.clear();

                // 키패드 무시하고 눌리는거 방지 해제
                root_idBtn.visible = true;
                root_rec.visible = true;
                root_Keypad.state = "hide";
            }
        }
        BtnLed{
            id: backBtn
            width: 500; height: 200;

            anchors.top: keypad_number.bottom
            anchors.topMargin: 30;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 30;
            anchors.right: parent.right
            anchors.rightMargin: 40
            Label{
                id: lb2
                text: "취소"
                font.pixelSize: 50
                font.family: "DIN"
                font.bold: true
                anchors.centerIn: parent
                // anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }

            Label{
                id: lb2_neon
                text: "취소"
                font.pixelSize: 50
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

            onSig_Clicked: function()
            {
                keypad_tf.clear();

                // 키패드 무시하고 눌리는거 방지 해제
                root_idBtn.visible = true;
                root_rec.visible = true;
                root_Keypad.state = "hide";
            }
        }
    }

    RecBtn{
        id: root_idBtn;
        width: 590; height: 240
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter

        Label{
            id: root_idBtn_label
            text: "ID 입력"
            color: "white"
            font.family: "DIN"
            font.pixelSize: 100

            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Label{
            id: root_idBtn_label_neon
            text: "ID 입력"
            color: "white"
            font.family: "DIN"
            font.pixelSize: 100

            anchors.fill:  root_idBtn_label
            anchors.margins: -20;

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

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


            MouseArea{
                id: root_idBtn_mArea
                anchors.fill: parent

                onClicked: function()
                {
                    if(root_Keypad.state === "hide")
                    {
                        // 키패드 무시하고 눌리는거 방지
                        root_idBtn.visible = false;
                        root_rec.visible = false;

                        root_Keypad.state = "open";
                    }
                }
            }
        }

        RecBtn{
            id: root_rec
            width: 590; height: 240;

            anchors.left: root_idBtn.right
            anchors.leftMargin: 20;
            anchors.verticalCenter: parent.verticalCenter

           Label{
                id: root_rec_label
                text: "서버 접속"
                color: "white"
                font.family: "DIN"
                font.pixelSize: 100

                anchors.centerIn: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Label{
                id: root_rec_label_neon
                text: "서버 접속"
                color: "white"
                font.family: "DIN"
                font.pixelSize: 100

                anchors.fill:  root_rec_label
                anchors.margins: -20;

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

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

            onSig_Clicked: function()
            {
                root.next_page(root.id);
            }
        }

        Label{
            id: root_printID;
            text: "입력된 ID : "
            font.pixelSize: 50
            font.bold: true;
            font.family: "DIN";
            color: "white";

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: root_rec.top
            anchors.bottomMargin: 60;
        }

        Label{
            id: root_printID_neon;
            text: "입력된 ID : "
            font.pixelSize: 50
            font.bold: true;
            font.family: "DIN";
            color: "white";

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: root_rec.top
            anchors.bottomMargin: 60;

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
            id: root_inputID;
            text: root.id
            font.pixelSize: 50
            font.bold: true;
            font.family: "DIN";
            color: "white";

            anchors.left: root_printID.right
            anchors.leftMargin: 10
            anchors.bottom: root_rec.top
            anchors.bottomMargin: 60;
        }

        Label{
            id: root_inputID_neon;
            text: root.id
            font.pixelSize: 50
            font.bold: true;
            font.family: "DIN";
            color: "white";

            anchors.left: root_printID.right
            anchors.leftMargin: 10
            anchors.bottom: root_rec.top
            anchors.bottomMargin: 60;

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

        Popup_Text{
            id: root_Pop_Text
            anchors.centerIn: parent
        }

        BusyIndicator{
            id: root_indicator
            width: 400; height: 400;
            running: false;
            visible: false;
            anchors.centerIn: parent
        }

        function next_page(s)
        {
            if(root.id === "")
            {
                root_Pop_Text.open("ID를 입력하여 주십시오");
            }
            else
            {
                // 이미 서버 연결시도 했으면 중복 X해야댐
                // ID만 다시 물어볼 수 있도록
                cpp_module.join_WebSv(root.id);
                // 로딩 이미지 띄워놓음
                root_indicator.visible = true;
                root_indicator.running = true;

                // 임시 서버 미연결 화면전환
                // root.stk_push();
            }
        }

        function stk_push()
        {
            StackView.view.push("HMI_main.qml", {mainWin : mainWin});
            // StackView.view.push("./Qml_Module/Keypad_Number.qml");
        }

        Connections{
            target: cpp_module

            function onSig_SocErr_ToQml(s){

                root_Pop_Text.open(s);
                // 로딩 이미지 투명
                // 실패 팝업창 생성
                root_indicator.visible = false;
                root_indicator.running = false;
            }

            function onSig_SocSuccess_ToQml(){
                // 로딩 이미지 투명
                root_indicator.visible = false;
                root_indicator.running = false;
                root.stk_push();
            }

            function onSig_SocFailed_ToQml(s){

                root_Pop_Text.open(s);
                // 로딩 이미지 투명
                root_indicator.visible = false;
                root_indicator.running = false;
            }
        }
}
