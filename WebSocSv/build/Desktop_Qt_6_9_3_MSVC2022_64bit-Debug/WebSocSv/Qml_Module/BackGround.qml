import QtQuick
import QtQuick.Effects

Item {
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#0d1419" }
            GradientStop { position: 0.5; color: "#0b1014" }
            GradientStop { position: 1.0; color: "#070c10" }
        }
    }

    Rectangle {
        id: topGlow
        width: parent.width
        height: 120
        // radius: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        // anchors.topMargin: 20

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#66aaddff" }
            GradientStop { position: 1.0; color: "transparent" }
        }

        opacity: 0.5
    }

    MultiEffect {
        anchors.fill: topGlow
        source: topGlow
        blurEnabled: true
        blur: 0.8
    }

    Rectangle {
        id: bottomGlow
        width: parent.width
        height: 220
        // radius: 110
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        // anchors.bottomMargin: 30

        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: "#66ccff" }
        }

        opacity: 0.4
    }


    MultiEffect {
        anchors.fill: bottomGlow
        source: bottomGlow
        blurEnabled: true
        blur: 0.9
    }

}
