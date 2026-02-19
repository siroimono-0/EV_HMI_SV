import QtQuick
import QtQuick.Controls
import WebSocSv 1.0

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent

    property real bashW: 1920;
    property real bashH: 1080;
    property real uiScale: Math.min(root.width / root.bashW, root.height / root.bashH);

    function cnv (val)
    {
        return val * root.uiScale;
    }

    BackGround{
        id: background
        anchors.fill: parent
    }

    TextField{
        id: root_tf1
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.right: root_rec.left
        anchors.rightMargin: 10
        anchors.top : root_rec.top

        placeholderText: "아이디를 입력하세요"
        font.pixelSize: 15
    }

        TextField{
        id: root_tf2
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.right: root_rec.left
        anchors.rightMargin: 10
        anchors.top : root_tf1.bottom
        anchors.topMargin: 10

        placeholderText: "비밀번호를 입력하세요"
        font.pixelSize: 15
    }

    RecBtn{
        id: root_rec
        width: root.cnv(400); height: root.cnv(160);
        radius: 10

        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.verticalCenter: parent.verticalCenter

        Label{
            id: root_rec_label
            text: "Start Server"
            color: "white"
            font.family: "DIN"
            font.pixelSize: 30
            anchors.centerIn: parent
        }

        onSig_Clicked: function()
        {
            root.next_page(root_tf1.text);
        }
    }

    function next_page(s)
    {
        // cppSv.set_webSoc_Sv();
        StackView.view.push("SV_info_page.qml");
        // root_tf.clear();
    }
}
