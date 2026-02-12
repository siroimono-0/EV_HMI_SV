import QtQuick
import HMI 1.0
import QtQuick.Controls

Item {
    id: root

    BackGround{
        id: background
        anchors.fill: parent
    }

    Rectangle{
        id: root_startBtn
        width: 300; height: 180;
        color: "#800000FF"
        border.color: "blue"
        border.width: 2
        radius: 10

        anchors.centerIn: parent

        Label{
            id: btnText
            text: "시작하기"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.stk_next();
            }
        }
    }

    function stk_next()
    {
        StackView.view.push("Select_charge.qml");

    }
}
