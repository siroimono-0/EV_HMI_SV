import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle{
    id: root_recBtn
    signal sig_Clicked();

    width: 120; height: 105;
    color: "transparent"
    radius: 3
    border.color: "#8FE8FF"
    border.width: 4;

    layer.enabled: true
    layer.effect: MultiEffect {

        shadowEnabled: true
        shadowBlur: 1.6
        shadowColor: "#00D9FF"
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
    }

    MouseArea{
        id: root_mArea
        anchors.fill: parent
        onClicked: function()
        {
            ripple.restart();
            root_recBtn.sig_Clicked();
        }
    }

    Rectangle{
        id: recBtn_line
        color: "transparent"
        border.color: "#8FE8FF"
        border.width: 2;
        radius: 4
        opacity: 1

        anchors.fill: parent
        anchors.margins: 10

        layer.enabled: true
        layer.effect: MultiEffect {

            shadowEnabled: true
            shadowBlur: 1.6
            shadowColor: "#00D9FF"
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }
    }

    Rectangle{
        id: btnBack;
        radius: parent.radius;
        anchors.fill: recBtn_line

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8FF5FF" }
            GradientStop { position: 0.4; color: "#4CC3D9" }
            GradientStop { position: 0.8; color: "#1C6F82" }
            GradientStop { position: 1.0; color: "#0E3A46" }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            blurEnabled: true
            blur: 0.3
            blurMax: 32
        }
    }

    Rectangle{
        id: ripple
        width: parent.width / 10; height: parent.height / 10;
        radius: 4
        opacity: 0;

        gradient: Gradient {
            orientation: Gradient.RadialGradient

            GradientStop { position: 0.0; color: "#AFFFFF" }
            GradientStop { position: 0.2; color: "#5FD7F2" }
            GradientStop { position: 0.6; color: "#00D9FF" }
            GradientStop { position: 1.0; color: "transparent" }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#00FFFF"
        }

        anchors.centerIn: parent

        ParallelAnimation{
            id: ripple_ParAni

            NumberAnimation{
                target: ripple
                property: "scale"
                from: 0.3
                to: 10
                duration: 300
            }
            NumberAnimation{
                target: ripple
                property: "opacity"
                from: 0.6
                to: 0
                duration: 300
            }
        }

        function restart()
        {
            ripple.scale = 0.3
            ripple_ParAni.restart();
        }
    }
}

