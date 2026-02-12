import QtQuick
import QtQuick.Controls
// import Cpp_WebSocSv

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent

    property string ip: ""

    Component.onCompleted: {
        console.log(ip);
    }

    function slot_stk_pop()
    {
        StackView.view.pop();
    }

    /*
    Cpp_WebSocSv{
        id: cppSv
    }*/

    BackBtn{
        id: root_backBtn
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5

        onClicked_BackBtn: function()
        {
            root.slot_stk_pop();
        }
    }

    Rectangle{
        id: root_rec
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 150
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        color: "lightgray"
        radius: 10;
        z: -999;


        Row {
            id: root_header
            height: 30
            spacing: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            Rectangle {
                id: root_header_no;

                width: 50
                height: 30
                border.color: "#DDDDDD"
                border.width: 2

                Behavior on scale {
                    NumberAnimation{
                        duration: 80
                        easing.type: Easing.InOutQuad
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "No."
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        root_header_no.scale = 0.9;
                    }
                    onReleased: {
                        root_header_no.scale = 1.0;
                    }
                }

            }
            Rectangle {
                id: root_header_id

                width: 150
                height: 30
                border.color: "#DDDDDD"
                border.width: 2

                Behavior on scale {
                    NumberAnimation{
                        duration: 80
                        easing.type: Easing.InOutQuad
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "ID"
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        root_header_id.scale = 0.9;
                    }
                    onReleased: {
                        root_header_id.scale = 1.0;
                    }
                }

            }
            Rectangle {
                id:  root_header_location

                width: 150
                height: 30
                border.color: "#DDDDDD"
                border.width: 2

                Behavior on scale {
                    NumberAnimation{
                        duration: 80
                        easing.type: Easing.InOutQuad
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Location"
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        root_header_location.scale = 0.9;
                    }
                    onReleased: {
                        root_header_location.scale = 1.0;
                    }
                }
            }
            Rectangle {
                id:   root_header_date

                width: 150
                height: 30
                border.color: "#DDDDDD"
                border.width: 2

                Behavior on scale {
                    NumberAnimation{
                        duration: 80
                        easing.type: Easing.InOutQuad
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Date"
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        root_header_date.scale = 0.9;
                    }
                    onReleased: {
                        root_header_date.scale = 1.0;
                    }
                }
            }
            Rectangle {
                id:   root_header_stat

                width: 150
                height: 30
                border.color: "#DDDDDD"
                border.width: 2

                Behavior on scale {
                    NumberAnimation{
                        duration: 80
                        easing.type: Easing.InOutQuad
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Stat"
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        root_header_stat.scale = 0.9;
                    }
                    onReleased: {
                        root_header_stat.scale = 1.0;
                    }
                }
            }

        } // header

        ListView{
            id: root_rec_lView
            model: cppSv ? cppSv.hmi_md : null
            spacing: 5
            clip: true

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: root_header.bottom
            // anchors.topMargin: 10
            anchors.bottom: parent.bottom


            delegate: Rectangle{
                // width: parent.width - 20
                width: root_rec_lView.width - 20
                height: 40  // 높이 명시적으로 설정

                border.color: "blue"
                border.width: 2

                Row {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 10

                    Label {
                        text: model.number
                        font.pixelSize: 18
                        width: 50
                        verticalAlignment: Text.AlignVCenter
                    } // No
                    Label {
                        text: model.id
                        font.pixelSize: 18
                        width: 150
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight  // 텍스트가 길면 생략 표시
                    } // Name
                    Label {
                        text: model.location
                        font.pixelSize: 18
                        width: 150
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    } // Location
                    Label {
                        text: model.date
                        font.pixelSize: 18
                        width: 150
                        verticalAlignment: Text.AlignVCenter
                    } // Date
                    Label {
                        text: model.stat
                        font.pixelSize: 18
                        width: 150
                        verticalAlignment: Text.AlignVCenter
                    } // Stat

                } // Row
            } // delegate
        } // root_rec_lView
    } // root_rec
}
