import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent
    property string id: "";

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
        transitions: [
            Transition {
                from: "*"
                to: "*"
                NumberAnimation{
                    target: root_Keypad
                    properties: "width, height, opacity";
                    duration: 250
                }
            }
        ]

        RecBtn{
            id: okBtn
            width: 500; height: 200;

            anchors.top: keypad_number.bottom
            anchors.topMargin: 30;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 30;
            anchors.left: parent.left
            anchors.leftMargin: 40

            Label{
                id: okBtn_lb
                text: "확인"
                font.pixelSize: 50;
                font.family: "DIN";

                anchors.centerIn: parent
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
        RecBtn{
            id: backBtn
            width: 500; height: 200;

            anchors.top: keypad_number.bottom
            anchors.topMargin: 30;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 30;
            anchors.right: parent.right
            anchors.rightMargin: 40

            Label{
                id: backBtn_lb
                text: "취소"
                font.pixelSize: 50;
                font.family: "DIN";

                anchors.centerIn: parent
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
            text: "ID 입력하기"
            font.pixelSize: 50;
            font.family: "DIN";

            anchors.centerIn: parent
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


        Behavior on scale{
            NumberAnimation{
                duration: 250
            }
        }

        Label{
            id: root_rec_label
            text: "HMI Server Connection"
            anchors.centerIn: parent
        }
    }

    Label{
        id: root_printID;
        text: "입력된 ID : "
        font.pixelSize: 30
        font.bold: true;
        font.family: "DIN";
        color: "white";

        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: root_rec.top
        anchors.bottomMargin: 30;
    }

    Label{
        id: root_inputID;
        text: root.id
        font.pixelSize: 30
        font.bold: true;
        font.family: "DIN";
        color: "white";

        anchors.left: root_printID.right
        anchors.leftMargin: 10
        anchors.bottom: root_rec.top
        anchors.bottomMargin: 30;
    }

    Popup_Text{
        id: root_Pop_Text
        anchors.centerIn: parent
    }

    BusyIndicator{
        id: root_indicator
        width: 100; height: 100;
        running: false;
        visible: false;
        anchors.centerIn: parent
    }

    function next_page(s)
    {
        if(tf_id.text === "")
        {
            root_Pop_Text.open("ID를 입력하여 주십시오");
        }
        else
        {
            cpp_module.join_WebSv(tf_id.text, tf_location.text);
            // 로딩 이미지 띄워놓음
            root_indicator.visible = true;
            root_indicator.running = true;

            // 임시 서버 미연결 화면전환
            root.stk_push();
        }
    }

    function stk_push()
    {
        StackView.view.push("HMI_main.qml");
        // StackView.view.push("./Qml_Module/Keypad_Number.qml");
    }

    Connections{
        target: cpp_module

        function onSig_SocErr_ToQml(s){
            console.log(s);
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
    }
}
