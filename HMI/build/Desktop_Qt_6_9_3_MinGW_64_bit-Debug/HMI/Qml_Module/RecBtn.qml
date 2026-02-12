import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle{
    id: root_recBtn
    signal sig_Clicked();

    color: "transparent"
    radius: 10;
    border.color: "#8FE8FF"
    border.width: 2;

    layer.enabled: true
    layer.effect: MultiEffect {

        shadowEnabled: true
        shadowBlur: 1.0
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
        id: btnBack;
        radius: parent.radius;
        anchors.fill: parent
        anchors.margins: 10

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#5FD7F2" }
            GradientStop { position: 0.3; color: "#3BA7BD" }
            GradientStop { position: 0.7; color: "#1F5E6D" }
            GradientStop { position: 1.0; color: "#0A2B34" }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            blurEnabled: true
            blur: 1
            blurMax: 32
        }
    }

    Rectangle{
        id: ripple
        width: parent.width / 10; height: parent.height / 10;
        radius: parent.radius
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
