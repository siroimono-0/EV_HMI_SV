import QtQuick
import QtQuick.Controls
import HMI 1.0

Item {

    BackGround{
        id: background
        anchors.fill: parent
    }

    Rectangle{
        id: root_percent

        width: 150; height: 200;
        color: "white"
        border.color: "blue"
        border.width: 2
        radius: 10

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        Label{
            id: left_BtnText
            text: "80% 까지 충전"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                // 임시 cpp 충전 시작하는 버튼으로 진행
            }
        }
    }

}
