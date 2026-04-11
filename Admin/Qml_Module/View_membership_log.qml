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
            height: 45
            spacing: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            Rec_header{
                id: header_store_id;

                width: 120
                height: 30
                text: "card_uid"
            }
            Rec_header{
                id: header_hmi_id;

                width: 100
                height: 30
                text: "transaction_id";
            }
            Rec_header{
                id: header_ocpp_tx_id;

                width: 100
                height: 30
                text: "event_type"
            }
            Rec_header{
                id: header_card_uid;

                width: 100
                height: 30
                text: "amount"
            }
            Rec_header_2{
                id: tmp0

                width: 150;
                height: 45;
                text: "balance_available"
                text_2: "_before"
            }
            Rec_header_2{
                id: tmp1

                width: 150;
                height: 45;
                text: "balance_available"
                text_2: "_after"
            }
            Rec_header_2{
                id: tmp2

                width: 100;
                height: 45;
                text: "hold_amount"
                text_2: "_before"
            }
            Rec_header_2{
                id: tmp3

                width: 100;
                height: 45;
                text: "hold_amount"
                text_2: "_after"
            }
            Rec_header_2{
                id: tmp4

                width: 130;
                height: 45;
                text: "transaction"
                text_2: "_state_before"
            }
            Rec_header_2{
                id: tmp5

                width: 120;
                height: 45;
                text: "transaction"
                text_2: "_state_after"
            }
            Rec_header{
                id: header_actual_payment;

                width:170
                height: 30
                text: "created_at"
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

                        width: 125
                        height: 30
                        text: model.card_uid
                    }
                    Rec_data{
                        id: header_hmi_id2;

                        width: 110
                        height: 30
                        text: model.transaction_id;

                    }
                    Rec_data{
                        id: header_ocpp_tx_id2;

                        width: 110
                        height: 30
                        text: model.event_type
                    }
                    Rec_data{
                        id: header_card_uid2;

                        width: 110
                        height: 30
                        text: model.amount
                    }
                    Rec_data{
                        id: header_start_time2;

                        width:160
                        height: 30
                        text: model.balance_available_before
                    }
                    Rec_data{
                        id: header_end_time2;

                        width:160
                        height: 30
                        text: model.balance_available_after
                    }
                    Rec_data{
                        id: header_soc_start2;

                        width:110
                        height: 30
                        text: model.hold_amount_before
                    }
                    Rec_data{
                        id: header_soc_end2;

                        width:110
                        height: 30
                        text: model.hold_amount_after
                    }
                    Rec_data{
                        id: header_advance_payment2;

                        width:140
                        height: 30
                        text: model.transaction_state_before
                    }
                    Rec_data{
                        id: header_cancel_payment2;

                        width:130
                        height: 30
                        text: model.transaction_state_after
                    }
                    Rec_data{
                        id: header_actual_payment2;

                        width:175
                        height: 30
                        text: model.created_at
                    }
                }

            } // delegate
        } // root_rec_lView
    } // root_rec
}
