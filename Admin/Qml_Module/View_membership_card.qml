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

                width: 150
                height: 30
                text: "card_uid"
            }
            Rec_header{
                id: header_hmi_id;

                width: 150
                height: 30
                text: "balance_total";

            }
            Rec_header{
                id: header_ocpp_tx_id;

                width: 150
                height: 30
                text: "balance_available"
            }
            Rec_header{
                id: header_card_uid;

                width: 150
                height: 30
                text: "hold_amount"
            }
            Rec_header{
                id: header_start_time;

                width: 150
                height: 30
                text: "transaction_state"
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

                        width: 155
                        height: 30
                        text: model.card_uid
                    }
                    Rec_data{
                        id: header_hmi_id2;

                        width: 160
                        height: 30
                        text: model.balance_total

                    }
                    Rec_data{
                        id: header_ocpp_tx_id2;

                        width: 160
                        height: 30
                        text: model.balance_available
                    }
                    Rec_data{
                        id: header_card_uid2;

                        width: 160
                        height: 30
                        text: model.hold_amount
                    }
                    Rec_data{
                        id: header_start_time2;

                        width:155
                        height: 30
                        text: model.transaction_state
                    }
                }

            } // delegate
        } // root_rec_lView
    } // root_rec
}
