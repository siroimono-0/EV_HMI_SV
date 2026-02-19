import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 50; height: 50;

    signal clicked_BackBtn();

    Rectangle{
        id: root_rec

        gradient: Gradient {
            GradientStop { position: 0.0; color: "black" }
            GradientStop { position: 0.5; color: "gray" }
            GradientStop { position: 1.0; color: "lightgray" }
        }
        radius: 5

        anchors.fill: parent

        Behavior on scale {
            NumberAnimation{
                duration: 250
            }
        }

        Label{
            id: root_rec_label
            text: "Back";
            color: "white"
            font.pixelSize: 15
            font.bold: true

            anchors.centerIn: parent
        }

        MouseArea{
            id: root_rec_mArea
            anchors.fill: parent

            onClicked: function()
            {
                root.clicked_BackBtn();
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
}
