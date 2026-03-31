import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Item {
    id: root;
    property string price;
    property bool bottom_text_visible : true

    function set_bottom_text_visible(set)
    {
        root.bottom_text_visible = set;
    }


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

    Label{
        id: lb
        visible: root.bottom_text_visible;
        text: "1kWh 금액: " + cpp_module.statStore.charge_price_kWh;
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: lb2.top
        // anchors.bottomMargin: 10

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb_neon
        visible: root.bottom_text_visible;
        text: "1kWh 금액: " + cpp_module.statStore.charge_price_kWh;
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true

        anchors.fill: lb
        anchors.margins: -20

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        layer.enabled: true;

        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
    }

        Label{
        id: lb2
        visible: root.bottom_text_visible;
        text: "고객센터: 000-0000-0000"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Label{
        id: lb2_neon
        visible: root.bottom_text_visible;
        text: "고객센터: 000-0000-0000"
        font.pixelSize: 30
        font.family: "DIN"
        font.bold: true

        anchors.fill: lb2
        anchors.margins: -20

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        layer.enabled: true;

        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
    }

}
