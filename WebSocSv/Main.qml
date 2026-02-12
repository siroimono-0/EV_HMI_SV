import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    StackView{
        id: root_stkView
        initialItem: "Start_page.qml"

        anchors.fill: parent
    }
}
