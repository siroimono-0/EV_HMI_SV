import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Effects

Item {
    id: root
    property int l_size : 220;

    Rectangle{
        id: line

        color: "transparent"
        width: root.l_size
        height: 1
        border.color: "#FFFFFF"
        border.width: 2

        layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: true
                shadowBlur: 1.0
                shadowColor: "#FFFFFF"
                shadowVerticalOffset: 0
                shadowHorizontalOffset: 0
            }
    }
    Rectangle{
        id: line2

        color: "transparent"
        width: root.l_size / 7
        height: 1
        border.color: "#FFFFFF"
        border.width: 2
        rotation: 45
        x: line.x + line.width - line2.width + 5
        y: line.y - (line2.width / 2) + (5);
        // x: 100
        // y: 200



        layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: true
                shadowBlur: 1.0
                shadowColor: "#FFFFFF"
                shadowVerticalOffset: 0
                shadowHorizontalOffset: 0
            }
    }
    Rectangle{
        id: line3

        color: "transparent"
        width: root.l_size / 7
        height: 1
        border.color: "#FFFFFF"
        border.width: 2
        rotation: -45
        x: line.x + line.width - line2.width + 5
        y: line.y + (line2.width / 2) - (5);



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
