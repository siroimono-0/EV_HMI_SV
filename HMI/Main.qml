import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 1280
    height: 800
    visible: true
    title: qsTr("Hello World")

    StackView{
        id: root_stkView
        initialItem: "Start_page.qml"

        anchors.fill: parent
    }
}
