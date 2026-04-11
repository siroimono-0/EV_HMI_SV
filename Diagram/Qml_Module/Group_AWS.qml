import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Item {
    id: root
    width: 120
    height: 90
    property string set_text : "AWS"
    property int set_font_size : 20
    property int set_font_size_2 : 15

    Rectangle{
        id: border_

        color: "transparent"
        // width: root.set_width
        // height: root.set_height
        border.color: "#FFFFFF"
        border.width: 2

        // anchors.centerIn: parent
        anchors.fill: parent

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FFFFFF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }
    }
    Column{
        id: col

        anchors.left: border_.left
        anchors.leftMargin: 5
        anchors.right: border_.right
        anchors.rightMargin: 5
        anchors.top: border_.top
        anchors.topMargin: 5

        spacing: 5

        Item{
            width: 90; height: 15
            Label{
                id: lb3
                text: "WebSocket SV"
                font.pixelSize: root.set_font_size_2
                font.family: "DIN"
                font.bold: true

                anchors.left: parent.left
            }

            /*
                Label{
                    id: lb4
                    text: "WebSocket SV"
                    font.pixelSize: root.set_font_size_2
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: lb3
                    anchors.margins: -10

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowBlur: 0.1
                        shadowColor: "#FFFFFF"
                        shadowVerticalOffset: 0
                        shadowHorizontalOffset: 0
                    }
                }*/
        }
        Item{
            width: 90; height: 15
            Label{
                id: lb5
                text: "Http SV"
                font.pixelSize: root.set_font_size_2
                font.family: "DIN"
                font.bold: true

                anchors.left: parent.left
            }

            /*
                Label{
                    id: lb6
                    text: "Http SV"
                    font.pixelSize: root.set_font_size_2
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: lb5
                    anchors.margins: -10

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowBlur: 0.1
                        shadowColor: "#FFFFFF"
                        shadowVerticalOffset: 0
                        shadowHorizontalOffset: 0
                    }
                }*/
        }
        Item{
            width: 90; height: 15
            Label{
                id: lb7
                text: "SQLITE"
                font.pixelSize: root.set_font_size_2
                font.family: "DIN"
                font.bold: true

                anchors.left: parent.left
            }

            /*
                Label{
                    id: lb8
                    text: "SQLITE"
                    font.pixelSize: root.set_font_size_2
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: lb7
                    anchors.margins: -10

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowBlur: 0.1
                        shadowColor: "#FFFFFF"
                        shadowVerticalOffset: 0
                        shadowHorizontalOffset: 0
                    }
                }*/
        }

        Item{
            width: 90; height: 15
            Label{
                id: lb9
                text: "postgreSQL"
                font.pixelSize: root.set_font_size_2
                font.family: "DIN"
                font.bold: true

                anchors.left: parent.left
            }

            /*
                Label{
                    id: lb10
                    text: "postgreSQL"
                    font.pixelSize: root.set_font_size_2
                    font.family: "DIN"
                    font.bold: true

                    anchors.centerIn: lb9
                    anchors.margins: -10

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowBlur: 0.1
                        shadowColor: "#FFFFFF"
                        shadowVerticalOffset: 0
                        shadowHorizontalOffset: 0
                    }
                }*/
        }
    }

    Label{
        id: lb1
        text: "AWS"
        font.pixelSize: root.set_font_size
        font.family: "DIN"
        font.bold: true

        anchors.horizontalCenter: border_.horizontalCenter
        anchors.bottom:  border_.top
        anchors.bottomMargin: 2

    }

    Label{
        id: lb2
        text: "AWS"
        font.pixelSize: root.set_font_size
        font.family: "DIN"
        font.bold: true

        anchors.centerIn: lb1
        anchors.margins: -20

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FFFFFF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }
    }
}
