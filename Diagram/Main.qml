import QtQuick
import QtQuick.Controls
import Diagram 1.0
import QtQuick.Effects

Window {
    id: root
    width: 640
    height: 830
    visible: true
    title: qsTr("Hello World")
    color: "#1e1e1e"
    flags: Qt.FramelessWindowHint

    Item {
        id: root_anc
        anchors.fill: parent
    }

    Group_AWS{
        id: aws

        anchors.horizontalCenter: root_anc.horizontalCenter
        anchors.top: root_anc.top
        anchors.topMargin: 30
    }

    Line_head{
        id: a1
        anchors.top: root_anc.top
        anchors.topMargin: 300
        anchors.left: root_anc.left
        anchors.leftMargin: 100
        rotation: -50

        visible: root.a1_v
    }

    Line_head{
        id: a2
        anchors.top: root_anc.top
        anchors.topMargin: 140
        anchors.left: root_anc.left
        anchors.leftMargin: 280
        rotation: 125

        visible: root.a2_v
    }

    Line_head{
        id: a3
        anchors.top: root_anc.top
        anchors.topMargin: 300
        anchors.left: root_anc.left
        anchors.leftMargin: 535
        rotation: -130

        visible: root.a3_v
    }

    Line_head{
        id: a4
        anchors.top: root_anc.top
        anchors.topMargin: 140
        anchors.left: root_anc.left
        anchors.leftMargin: 360
        rotation: 55

        visible: root.a4_v
    }


    Group_Local{
        id: local

        anchors.left: root_anc.left
        anchors.leftMargin: 15
        anchors.bottom: root_anc.bottom
        anchors.bottomMargin: 400
    }

    Group_Admin{
        id: admin

        anchors.right: root_anc.right
        anchors.rightMargin: 15
        anchors.bottom: root_anc.bottom
        anchors.bottomMargin: 400
    }

    Line_head_2{
        id: a5
        l_size: 330
        anchors.left: local.right
        anchors.leftMargin: 30
        anchors.top: local.top
        anchors.topMargin: 20

        visible: root.a5_v
    }

    Line_head_2{
        id: a6
        l_size: 330
        anchors.left: admin.left
        anchors.leftMargin: -30
        anchors.top: admin.top
        anchors.topMargin: 60

        rotation: 180

        visible: root.a6_v
    }

    // property bool a1_v: true
    property bool a1_v: false

    // property bool a2_v: true
    property bool a2_v: false

    property bool a3_v: true
    // property bool a3_v: false

    // property bool a4_v: true
    property bool a4_v: false

    // property bool a5_v: true
    property bool a5_v: false

    // property bool a6_v: true
    property bool a6_v: false

    //=================================================================
    //=================================================================

    property bool b1_v: true
    // property bool b1_v: false
    property string b1_from: "Admin"
    property string b1_up: "Http 서버로"
    property string b1_down: "파일 전송"
    property string b1_to: "AWS"

    property bool b2_v: true
    // property bool b2_v: false
    property string b2_from: "AWS"
    property string b2_up: ""
    property string b2_down: "파일 수신 후 저장"
    property string b2_to: "AWS"

    // property bool b3_v: true
    property bool b3_v: false
    property string b3_from: "Admin"
    property string b3_up: "웹 소켓 서버로"
    property string b3_down: "설비 재시작 요청"
    property string b3_to: "AWS"

    // property bool b4_v: true
    property bool b4_v: false
    property string b4_from: "AWS"
    property string b4_up: ""
    property string b4_down: "설비 재시작 요청"
    property string b4_to: "Local"

    //=================================================================
    //=================================================================
    //=================================================================
    //=================================================================
    Rec_lb
    {
        id: lb1
        set_text: root.b1_from
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 40
        anchors.left: root_anc.left
        anchors.leftMargin: 15
        visible: root.b1_v
    }

    Label{
        id: lb1_text_1
        text: root.b1_up
        font.pixelSize: 20;
        anchors.left: b1.left
        anchors.leftMargin: 5
        anchors.bottom: b1.top
        anchors.bottomMargin: 25
        visible: root.b1_v
    }

    Label{
        id: lb1_text_2
        text: root.b1_down
        font.pixelSize: 20;
        anchors.left: b1.left
        anchors.leftMargin: 5
        anchors.bottom: b1.top
        anchors.bottomMargin: 2
        visible: root.b1_v
    }

    Line_head_3{
        id: b1
        anchors.left: lb1.right
        anchors.leftMargin: 30
        anchors.right: lb1__.left
        anchors.rightMargin: 20
        anchors.bottom: lb1.bottom
        anchors.bottomMargin: 10
        visible: root.b1_v
    }

    Rec_lb{
        id: lb1__
        set_text: root.b1_to
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 40
        anchors.right: root_anc.right
        anchors.rightMargin: 15

        visible: root.b1_v
    }
    //=================================================================
    //=================================================================
    //=================================================================
    //=================================================================
    Rec_lb
    {
        id: lb2
        set_text: root.b2_from
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 130
        anchors.left: root_anc.left
        anchors.leftMargin: 15
        visible: root.b2_v
    }

    Label{
        id: lb2_text_1
        text: root.b2_up
        font.pixelSize: 20;
        anchors.left: b2.left
        anchors.leftMargin: 5
        anchors.bottom: b2.top
        anchors.bottomMargin: 25
        visible: root.b2_v
    }

    Label{
        id: lb2_text_2
        text: root.b2_down
        font.pixelSize: 20;
        anchors.left: b2.left
        anchors.leftMargin: 5
        anchors.bottom: b2.top
        anchors.bottomMargin: 2
        visible: root.b2_v
    }

    Line_head_3{
        id: b2
        anchors.left: lb2.right
        anchors.leftMargin: 30
        anchors.right: lb2__.left
        anchors.rightMargin: 20
        anchors.bottom: lb2.bottom
        anchors.bottomMargin: 10
        visible: root.b2_v
    }

    Rec_lb{
        id: lb2__
        set_text: root.b2_to
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 130
        anchors.right: root_anc.right
        anchors.rightMargin: 15

        visible: root.b2_v
    }
    //=================================================================
    //=================================================================
    //=================================================================
    //=================================================================
Rec_lb
    {
        id: lb3
        set_text: root.b3_from
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 220
        anchors.left: root_anc.left
        anchors.leftMargin: 15
        visible: root.b3_v
    }

    Label{
        id: lb3_text_1
        text: root.b3_up
        font.pixelSize: 20;
        anchors.left: b3.left
        anchors.leftMargin: 5
        anchors.bottom: b3.top
        anchors.bottomMargin: 25
        visible: root.b3_v
    }

    Label{
        id: lb3_text_2
        text: root.b3_down
        font.pixelSize: 20;
        anchors.left: b3.left
        anchors.leftMargin: 5
        anchors.bottom: b3.top
        anchors.bottomMargin: 2
        visible: root.b3_v
    }

    Line_head_3{
        id: b3
        anchors.left: lb3.right
        anchors.leftMargin: 30
        anchors.right: lb3__.left
        anchors.rightMargin: 20
        anchors.bottom: lb3.bottom
        anchors.bottomMargin: 10
        visible: root.b3_v
    }

    Rec_lb{
        id: lb3__
        set_text: root.b3_to
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 220
        anchors.right: root_anc.right
        anchors.rightMargin: 15

        visible: root.b3_v
    }
    //=================================================================
    //=================================================================
    //=================================================================
    //=================================================================
    Rec_lb
    {
        id: lb4
        set_text: root.b4_from
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 310
        anchors.left: root_anc.left
        anchors.leftMargin: 15
        visible: root.b4_v
    }

    Label{
        id: lb4_text_1
        text: root.b4_up
        font.pixelSize: 20;
        anchors.left: b4.left
        anchors.leftMargin: 5
        anchors.bottom: b4.top
        anchors.bottomMargin: 25
        visible: root.b4_v
    }

    Label{
        id: lb4_text_2
        text: root.b4_down
        font.pixelSize: 20;
        anchors.left: b4.left
        anchors.leftMargin: 5
        anchors.bottom: b4.top
        anchors.bottomMargin: 2
        visible: root.b4_v
    }

    Line_head_3{
        id: b4
        anchors.left: lb4.right
        anchors.leftMargin: 30
        anchors.right: lb4__.left
        anchors.rightMargin: 20
        anchors.bottom: lb4.bottom
        anchors.bottomMargin: 10
        visible: root.b4_v
    }

    Rec_lb{
        id: lb4__
        set_text: root.b4_to
        width: 100; height: 50
        anchors.top: local.bottom
        anchors.topMargin: 310
        anchors.right: root_anc.right
        anchors.rightMargin: 15

        visible: root.b4_v
    }


}
