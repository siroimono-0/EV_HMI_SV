import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle{
    id: root_btnRed
    signal sig_Clicked();

    color: "transparent"
    radius: 10;
    border.color: "#FF9AA6"   // 라이트 레드/핑크 테두리
    border.width: 2;

    layer.enabled: true
    layer.effect: MultiEffect {
        shadowEnabled: true
        shadowBlur: 1.0
        shadowColor: "#FF2D3D" // 레드 글로우
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
    }

    MouseArea{
        id: root_mArea
        anchors.fill: parent
        onClicked: function()
        {
            ripple.restart();
            root_btnRed.sig_Clicked();
        }
    }

    Rectangle{
        id: btnBack;
        radius: parent.radius;
        anchors.fill: parent
        anchors.margins: 10

        gradient: Gradient {
            // 위쪽 라이트 레드 → 아래쪽 딥 레드
            GradientStop { position: 0.0; color: "#FFD6DB" } // 아주 연한 레드
            GradientStop { position: 0.3; color: "#FF7A86" } // 밝은 레드/코랄
            GradientStop { position: 0.7; color: "#B11722" } // 딥 레드
            GradientStop { position: 1.0; color: "#3A0B10" } // 거의 블랙 레드
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

            // ripple도 레드 계열
            GradientStop { position: 0.0; color: "#FFF0F2" } // 거의 흰빛 레드
            GradientStop { position: 0.2; color: "#FFD6DB" }
            GradientStop { position: 0.6; color: "#FF2D3D" } // 네온 레드
            GradientStop { position: 1.0; color: "transparent" }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 1.0
            shadowColor: "#FF8A95"
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
