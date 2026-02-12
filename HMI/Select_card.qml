import QtQuick
import QtQuick.Controls
import HMI 1.0

Item {
    id: root

    BackGround{
        id: background
        anchors.fill: parent
    }


    Rectangle{
        id: root_left
        color: "white"
        border.color: "blue"
        border.width: 2
        radius: 10

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        Label{
            id: left_BtnText
            text: "회원 카드"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.stk_next("left");
            }
        }
    }

    Rectangle{
        id: root_right
        color: "white"
        border.color: "blue"
        border.width: 2
        radius: 10

        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        Label{
            id: right_BtnText
            text: "신용 카드"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.stk_next("right");
            }
        }
    }

    function stk_next(s)
    {
        // 임시 그냥 다음 화면으로
        StackView.view.push("Select_amount.qml");
    }
}
