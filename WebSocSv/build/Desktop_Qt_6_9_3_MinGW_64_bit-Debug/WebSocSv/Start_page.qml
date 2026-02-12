import QtQuick
import QtQuick.Controls

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent

    TextField{
        id: root_tf
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.right: root_rec.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        placeholderText: "input ip"
        font.pixelSize: 15
    }

    Rectangle{
        id: root_rec
        color: "lightblue";
        width: 200; height: 80;
        radius: 10

        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.verticalCenter: parent.verticalCenter

        Behavior on scale{
            NumberAnimation{
                duration: 250
            }
        }

        Label{
            id: root_rec_label
            text: "Start Server"
            anchors.centerIn: parent
        }

        MouseArea{
            id: root_rec_mArea
            anchors.fill: parent

            onClicked: function()
            {
                root.next_page(root_tf.text);
            }

            onPressed: function()
            {
                root_rec.scale = 0.9;
            }

            onReleased: function()
            {
                root_rec.scale = 1;
            }
        }
    }

    function next_page(s)
    {
        cppSv.set_webSoc_Sv(root_tf.text);
        StackView.view.push("SV_info_page.qml");
        root_tf.clear();
    }
}
