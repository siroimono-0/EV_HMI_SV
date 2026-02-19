import QtQuick
import QtQuick.Controls

Rectangle{
    id: root_recPop
    anchors.centerIn: parent
    width: 0; height: 0;
    color: "#1e1e1e"
    radius: 10

    function open(s)
    {
        root_recPop.width = 300;
        root_recPop.height = 100;

        recPop_Back.width = 25;
        recPop_Back.height = 25;
        recPop_lb.text = s;
        back_lb.visible = true;
    }
    function close()
    {
        root_recPop.width = 0;
        root_recPop.height = 0;

        recPop_Back.width = 0;
        recPop_Back.height = 0;
        recPop_lb.text = "";
        back_lb.visible = false;
    }

    Behavior on width {
        NumberAnimation{
            duration: 150
        }
    }

    Behavior on height {
        NumberAnimation{
            duration: 150
        }
    }

    Label{
        id: recPop_lb
        text: "";
        color: "white"
        font.pixelSize: 15
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
    }

    Rectangle{
        id: recPop_Back
        width: 0; height: 0;
        color: "#1e1e1e"
        anchors.right: parent.right
        anchors.top: parent.top
        radius: 10

        Label{
            id: back_lb
            text: "X"
            color: "white"
            font.pixelSize: 15;
            font.bold: true;
            anchors.centerIn: parent
            visible: false
        }

        MouseArea{
            id: back_mArea
            anchors.fill: parent

            onClicked: function()
            {
                root_recPop.close();
            }
        }
    }
}
