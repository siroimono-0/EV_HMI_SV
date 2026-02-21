import QtQuick
import HMI 1.0
import QtQuick.Controls

Item {
    id: root

    Component.onCompleted: function()
    {
        cpp_module.charging_type_clear_To_statStore();
    }

    BackGround{
        id: background
        anchors.fill: parent
    }

    RecBtn{
        id: root_startBtn
        width: 300; height: 180;
        anchors.centerIn: parent

        Label{
            id: btnText
            text: "시작하기"
            font.pixelSize: 15
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        onSig_Clicked: function()
        {
            root.stk_next();
        }
    }

    function stk_next()
    {
        StackView.view.push("Select_amount.qml");

    }
}
