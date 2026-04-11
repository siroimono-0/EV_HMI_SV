import QtQuick
import QtQuick.Controls
// import WebSocSv 1.0
// import Cpp_WebSocSv

Item {
    id: root
    // StackView 가 알아서 width height 채워넣음
    // anchors.fill: parent

    anchors.fill: parent
    // color: "transparent"

    function cnv (val)
    {
        return val * root.uiScale;
    }

    BackGround{
        id: back;
        anchors.fill: parent
        z: -999;
    }

    Component.onCompleted: {
        // console.log(cppModel.)
    }

    Rectangle{
        id: root_rec
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        color: "transparent"
        radius: 10;


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

            Rec_header{
                id: header_store_id;

                width: 100
                height: 30
                text: "store_id"
            }
            Rec_header{
                id: header_hmi_id;

                width: 100
                height: 30
                text: "hmi_id";

            }
            Rec_header{
                id: header_ocpp_tx_id;

                width: 150
                height: 30
                text: "ws_connected"
            }
            Rec_header{
                id: header_card_uid;

                width: 150
                height: 30
                text: "last_heartbeat_at"
            }
            Rec_header{
                id: header_start_time;

                width: 150
                height: 30
                text: "screen_name"
            }
            Rec_header{
                id: header_update;

                width:150
                height: 30
                text: "updated_at"
            }

        } // header

        ListView{
            id: root_rec_lView
            model: cppModel ? cppModel : null
            spacing: 5
            clip: true

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: root_header.bottom
            anchors.topMargin: 10
            anchors.bottom: parent.bottom


            delegate: Rectangle{
                // width: parent.width - 20
                width: root_rec_lView.width - 20
                height: 30  // 높이 명시적으로 설정

                color: "transparent"
                // border.color: "blue"
                // border.width: 2

                Row {
                    id: root_header2
                    height: 30
                    // spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    // anchors.leftMargin: 5

                    Rec_data{
                        id: header_store_id2;

                        width: 105
                        height: 30
                        text: model.store_id
                    }
                    Rec_data{
                        id: header_hmi_id2;

                        width: 110
                        height: 30
                        text: model.hmi_id;

                    }
                    Rec_data{
                        id: header_ocpp_tx_id2;

                        width: 160
                        height: 30
                        text: model.ws_connected
                    }
                    Rec_data{
                        id: header_card_uid2;

                        width: 160
                        height: 30
                        text: model.last_heartbeat_at
                    }
                    Rec_data{
                        id: header_start_time2;

                        width:160
                        height: 30
                        text: model.screen_name
                    }
                    Rec_data{
                        id: header_end_time2;

                        width:155
                        height: 30
                        text: model.updated_at
                    }
                }

            } // delegate
        } // root_rec_lView
    } // root_rec
}
