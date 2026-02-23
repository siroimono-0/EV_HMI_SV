import QtQuick
import QtQuick.Controls
import HMI 1.0

Window {
    id: root
    width: 1280
    height: 800
    visible: true
    title: qsTr("Hello World")

    StackView{
        id: root_stkView
        initialItem: "Start_page.qml"
        // initialItem: "Input_Time.qml"
        // initialItem: "Charging_Monitoring.qml"
        // initialItem: "./Qml_Module/BackGround_Amount.qml"

        anchors.fill: parent
    }
}
