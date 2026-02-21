import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import HMI 1.0

Item {
    id: root
    signal sig_BtnOk_Cilcked(string s);
    signal sig_BtnHome_Cilcked();
    signal sig_BtnCancle_Cilcked();

    property string unit_type : ""
    property int unit_size : 60

    BackGround{
        id: background
        anchors.fill: parent
    }

    Image {
        id: root_combo
        source: "../images/combo.svg"
        width: 180; height: 162;

        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 15
        fillMode: Image.PreserveAspectFit;

        layer.enabled: true;
        layer.effect: MultiEffect{
            shadowEnabled: true;
            shadowBlur: 1
            shadowColor: "#00FFD0"
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
    }

    Rectangle{
        id: root_rec
        height: 120
        color: "transparent"
        anchors.top: keypad.top
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.right: keypad.left
        anchors.rightMargin: 50

        border.color: "#FFFFFF"
        border.width: 3
        radius: 5

        layer.enabled: true;

        layer.effect: MultiEffect{
            shadowEnabled: true
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }

        TextField{
            id: tf

            font.pixelSize: 75;
            font.family: "DIN"

            anchors.left: parent.left
            anchors.right: lb3.left
            anchors.verticalCenter: parent.verticalCenter

            background: Rectangle{
                color: "transparent"
            }

            activeFocusOnPress: false;
            horizontalAlignment: Text.AlignRight;
            verticalAlignment: Text.AlignVCenter;

            layer.enabled: true;

        layer.effect: MultiEffect{
            shadowEnabled: true
            shadowBlur: 1
            shadowColor: "#FFFFFF"
            shadowOpacity: 1
            shadowVerticalOffset: 0;
            shadowHorizontalOffset: 0;
        }
        }

        Label{
            id: lb3
            width: 100
            text: root.unit_type
            font.pixelSize: root.unit_size
            font.family: "DIN"

            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: lb3_neon
            text: root.unit_type
            font.pixelSize: root.unit_size
            font.family: "DIN"

            anchors.fill: lb3
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

    Keypad_New{
        id: keypad
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.verticalCenter: parent.verticalCenter

        onSig_Cilcked: function(s)
        {
            if(s === "back")
            {
                tf.text = tf.text.slice(0, -1);
            }
            else if(s === "X")
            {
                tf.clear();
            }
            else
            {
                tf.text += s;
            }
        }
    }

    BtnGreen{
        id: btn_ok
        width: 250; height: 100;
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        Label{
            id: lb1
            text: "확인"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: lb1_neon
            text: "확인"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill: lb1
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
        onSig_Clicked: function()
        {
            let s = tf.text;
            root.sig_BtnOk_Cilcked(s);
            tf.clear();
        }
    }

    BtnLed{
        id: backBtn
        width: 250; height: 100;
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        Label{
            id: backBtn_lb
            text: "취소"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Label{
            id: backBtn_lb_neon
            text: "취소"
            font.pixelSize: 60
            font.family: "DIN"
            font.bold: true

            anchors.fill:  backBtn_lb
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

        onSig_Clicked: function()
        {
            root.sig_BtnCancle_Cilcked();
        }
    }

    BtnGreen{
        id: homeBtn
        width: 250; height: 100;
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 30

        Label{
            id: homeBtn_lb
            text: "HOME"
            font.pixelSize: 60
            font.family: "DIN"

            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Label{
            id: homeBtn_lb_neon
            text: "HOME"
            font.pixelSize: 60
            font.family: "DIN"

            anchors.fill:  homeBtn_lb
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

        onSig_Clicked: function()
        {
            root.sig_BtnHome_Cilcked();
        }

    }
}

