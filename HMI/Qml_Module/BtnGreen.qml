import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle{
    id: root_btnGreen
    signal sig_Clicked();

    color: "transparent"
    radius: 10;
    border.color: "#A6FFD6"   // 민트 그린 테두리
    border.width: 2;

    layer.enabled: true
    layer.effect: MultiEffect {
        shadowEnabled: true
        shadowBlur: 1.0
        shadowColor: "#3DFFB0" // 초록빛 글로우
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
    }

    MouseArea{
        id: root_mArea
        anchors.fill: parent
        onClicked: function()
        {
            ripple.restart();
            // 너 코드에 root_recBtn으로 되어있던데, id가 root_btnGreen이면 아래가 맞아
            root_btnGreen.sig_Clicked();
        }
    }

    Rectangle{
        id: btnBack;
        radius: parent.radius;
        anchors.fill: parent
        anchors.margins: 10

        gradient: Gradient {
            // 위쪽 밝은 민트 → 아래쪽 딥그린
            GradientStop { position: 0.0; color: "#BFFFE2" }
            GradientStop { position: 0.3; color: "#7FE7B7" }
            GradientStop { position: 0.7; color: "#2F9A63" }
            GradientStop { position: 1.0; color: "#0E3A24" }
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

            // ripple도 민트 그린 계열로
            GradientStop { position: 0.0; color: "#E8FFF4" }
            GradientStop { position: 0.2; color: "#BFFFE2" }
            GradientStop { position: 0.6; color: "#3DFFB0" }
            GradientStop { position: 1.0; color: "transparent" }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#78FFD0"
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
