import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: screen.width
    height: screen.height
    visible: true
    title: qsTr("Hello World")

    StackView{
        id: root_stkView
        initialItem: "Start_page.qml"
        // initialItem: "SV_info_page.qml"

        anchors.fill: parent
    }
}
