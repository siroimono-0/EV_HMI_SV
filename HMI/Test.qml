import QtQuick
import QtQuick.Controls
import HMI 1.0

Item {
    BackGround{
        anchors.fill: parent

    }


    Component.onCompleted: {
        console.log("width =", width)
        console.log("height =", height)
        console.log("Screen.width =", Screen.width)
        console.log("Screen.height =", Screen.height)
        console.log("Screen.devicePixelRatio =", Screen.devicePixelRatio)
        console.log("Screen.pixelDensity =", Screen.pixelDensity)
    }
}
