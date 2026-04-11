import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts
import HMI 1.0

Rectangle{
    id: root
    width: 1200; height: 440;
    radius: 30;
    border.color: Qt.rgba(0.2, 0.6, 1.0, 0.6)
    border.width: 2

    signal sig_btnClicked(string number);

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#0d1419" }
            GradientStop { position: 0.5; color: "#0b1014" }
            GradientStop { position: 1.0; color: "#070c10" }
        }
    }

    Column{
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        spacing: 20;

        Row{
            id: row1
            spacing: 20;
            anchors.left: parent.left
            anchors.leftMargin: 10

            Circle_Number{
                id: btn1_back
                width: 180; height: 180;

                Label{
                    id: btn1_lb
                    text: "1"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: btn1_lb_neon
                    text: "1"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill: btn1_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("1");
                }
            } // btn1
            Circle_Number{
                id: btn2_back
                width: 180; height: 180;

                Label{
                    id: btn2_lb
                    text: "2"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: btn2_lb_neon
                    text: "2"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill: btn2_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
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
                    root.sig_btnClicked("2");
                }
            } // btn2
            Circle_Number{
                id: btn3_back
                width: 180; height: 180;

                Label{
                    id: btn3_lb
                    text: "3"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: btn3_lb_neon
                    text: "3"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill: btn3_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("3");
                }
            } // btn3
            Circle_Number{
                id: btn4_back
                width: 180; height: 180;

                Label{
                    id: btn4_lb
                    text: "4"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: btn4_lb_neon
                    text: "4"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill: btn4_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("4");
                }
            } // btn4
            Circle_Number{
                id: btn5_back
                width: 180; height: 180;

                Label{
                    id: btn5_lb
                    text: "5"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: btn5_lb_neon
                    text: "5"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill: btn5_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("5");
                }
            } // btn5
            Circle_Number{
                id: btnDel1_back
                width: 180; height: 180;

                Label{
                    id: btnDel1_lb
                    text: "<<"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 80

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: btDel_lb_neon
                    text: "<<"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 80

                    anchors.fill:  btnDel1_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("<<");
                }
            } // btn1
        } // Row1
        Row{
            id: row2
            spacing: 20;
            anchors.left: parent.left
            anchors.leftMargin: 10

            Circle_Number{
                id: btn6_back
                width: 180; height: 180;

                Label{
                    id: btn6_lb
                    text: "6"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: bt6_lb_neon
                    text: "6"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btn6_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("6");
                }
            } // btn6
            Circle_Number{
                id: btn7_back
                width: 180; height: 180;

                Label{
                    id: btn7_lb
                    text: "7"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: bt7_lb_neon
                    text: "7"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btn7_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("7");
                }
            } // btn7
            Circle_Number{
                id: btn8_back
                width: 180; height: 180;

                Label{
                    id: btn8_lb
                    text: "8"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: bt8_lb_neon
                    text: "8"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btn8_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("8");
                }
            } // btn8
            Circle_Number{
                id: btn9_back
                width: 180; height: 180;

                Label{
                    id: btn9_lb
                    text: "9"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: bt9_lb_neon
                    text: "9"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btn9_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("9");
                }
            } // btn9
            Circle_Number{
                id: btn0_back
                width: 180; height: 180;

                Label{
                    id: btn0_lb
                    text: "0"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: bt0_lb_neon
                    text: "0"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btn0_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("0");
                }
            } // btn0
            Circle_Number{
                id: btnDel2_back
                width: 180; height: 180;

                Label{
                    id: btnDel2_lb
                    text: "X"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 80

                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label{
                    id: btDel2_lb_neon
                    text: "X"
                    color: "white"
                    font.family: "DIN"
                    font.pixelSize: 160

                    anchors.fill:  btnDel2_lb
                    anchors.margins: -20;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

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
                    root.sig_btnClicked("delete");
                }
            } // btnDel2
        } // Row2
    } // Col
}
