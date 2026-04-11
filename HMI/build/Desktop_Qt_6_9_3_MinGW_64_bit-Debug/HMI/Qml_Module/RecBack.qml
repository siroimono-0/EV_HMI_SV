import QtQuick
import QtQuick.Controls
import QtQuick.Effects


Rectangle{
    id: recBack;
    radius: 10;

    gradient: Gradient {
        // GradientStop { position: 0.0; color: "#6FD0E8" }
        // GradientStop { position: 1.0; color: "#1B4C5A" }
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
