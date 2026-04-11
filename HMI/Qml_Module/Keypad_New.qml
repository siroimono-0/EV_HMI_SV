import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import HMI 1.0


Item {
    id: root
    width: 380; height: 450;
    signal sig_Cilcked(string s);

    Column{
        anchors.fill: parent
        spacing: 10

        Row{
            anchors.left: parent.left
            spacing: 10

            Rec_Number{
                id: btn1

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("1")
                }

                Label{
                    id: lb1
                    text: "1"
                    font.pixelSize: 80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb1_neon
                    text: "1"
                    font.pixelSize: 80
                    font.family: "DIN"
                    // font.bold: true

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
            } //btn1
            Rec_Number{
                id: btn2

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("2")
                }

                Label{
                    id: lb2
                    text: "2"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb2_neon
                    text: "2"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

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
            } // btn2
            Rec_Number{
                id: btn3

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("3")
                }

                Label{
                    id: lb3
                    text: "3"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb3_neon
                    text: "3"
                    font.pixelSize: 80
                    font.family: "DIN"
                    // font.bold: true

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
            } // btn3
        }
        Row{
            anchors.left: parent.left
            spacing: 10

            Rec_Number{
                id: btn4

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("4")
                }

                Label{
                    id: lb4
                    text: "4"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb4_neon
                    text: "4"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb4
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
            } //btn4
            Rec_Number{
                id: btn5

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("5")
                }

                Label{
                    id: lb5
                    text: "5"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb5_neon
                    text: "5"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb5
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
            } // btn5
            Rec_Number{
                id: btn6

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("6")
                }

                Label{
                    id: lb6
                    text: "6"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb6_neon
                    text: "6"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb6
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
            } // btn6
        } // row2
        Row{
            anchors.left: parent.left
            spacing: 10

            Rec_Number{
                id: btn7

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("7")
                }

                Label{
                    id: lb7
                    text: "7"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb7_neon
                    text: "7"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb7
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
            } //btn7
            Rec_Number{
                id: btn8

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("8")
                }

                Label{
                    id: lb8
                    text: "8"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb8_neon
                    text: "8"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb8
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
            } // btn8
            Rec_Number{
                id: btn9

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("9")
                }

                Label{
                    id: lb9
                    text: "9"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb9_neon
                    text: "9"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb9
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
            } // btn9
        } // row3
        Row{
            anchors.left: parent.left
            spacing: 10

            Rec_Number{
                id: btnB

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("back")
                }

                Label{
                    id: lbB
                    text: "◀"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lbB_neon
                    text: "◀"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lbB
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
            } //btnB
            Rec_Number{
                id: btn0

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("0")
                }

                Label{
                    id: lb0
                    text: "0"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lb0_neon
                    text: "0"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lb0
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
            } // btn0
            Rec_Number{
                id: btnX

                onSig_Clicked: function()
                {
                    root.sig_Cilcked("X")
                }

                Label{
                    id: lbX
                    text: "X"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -2.5
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                }

                Label{
                    id: lbX_neon
                    text: "X"
                    font.pixelSize:80
                    font.family: "DIN"
                    // font.bold: true

                    anchors.fill: lbX
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
            } // btnX
        } // row4
    }
}
