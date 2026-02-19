import QtQuick
import QtQuick.Controls
import WebSocSv 1.0

Rectangle{
    id: root_recPop
    anchors.centerIn: parent
    width: 0; height: 0;
    color: "#1e1e1e"
    radius: 10

    signal sig_Clicked(string id, string name, string text);

    function open(s)
    {
        root_recPop.width = 600;
        root_recPop.height = 200;

        recPop_Back.width = 25;
        recPop_Back.height = 25;
        back_lb.visible = true;
        row.visible = true;
    }
    function close()
    {
        root_recPop.width = 0;
        root_recPop.height = 0;

        recPop_Back.width = 0;
        recPop_Back.height = 0;
        back_lb.visible = false;
        row.visible = false;
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

    Row{
        id: row
        spacing: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        visible: false;

        Column{
            y: 10
            spacing: 10

            TextField{
                id: recPop_tfID
                placeholderText: "ID"
                placeholderTextColor: "gray"

                color: "black";
                font.pixelSize: 15
                width: 275
                verticalAlignment: Text.AlignVCenter
                // horizontalAlignment: Text.AlignHCenter

                background: Rectangle{
                    border.color: "white"
                    border.width: 2
                    radius: 10
                }
            }
            TextField{
                id: recPop_tfName
                placeholderText: "Name"
                placeholderTextColor: "gray"

                color: "black";
                font.pixelSize: 15
                width: 275
                verticalAlignment: Text.AlignVCenter
                // horizontalAlignment: Text.AlignHCenter

                background: Rectangle{
                    border.color: "white"
                    border.width: 2
                    radius: 10
                }
            }
            TextField{
                id: recPop_tfLocation
                placeholderText: "Location"
                placeholderTextColor: "gray"

                color: "black";
                font.pixelSize: 15
                width: 275
                verticalAlignment: Text.AlignVCenter
                // horizontalAlignment: Text.AlignHCenter

                background: Rectangle{
                    border.color: "white"
                    border.width: 2
                    radius: 10
                }
            }
        }

        RecBtn{
            id: createBtn
            width: 275; height: 120;

            Label{
                id:  createBtn_lb
                text: "Create New Store"
                color: "white"
                font.family: "DIN"
                font.pixelSize: 30
                anchors.centerIn: parent
            }
            onSig_Clicked: function()
            {
                root_recPop.sig_Clicked( recPop_tfID.text,  recPop_tfName.text,  recPop_tfLocation.text);
            }

        }
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
