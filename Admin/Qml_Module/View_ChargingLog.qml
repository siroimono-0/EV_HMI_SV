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

                width: 100
                height: 30
                text: "ocpp_tx_id"
            }
            Rec_header{
                id: header_card_uid;

                width: 150
                height: 30
                text: "card_uid"
            }
            Rec_header{
                id: header_start_time;

                width:100
                height: 30
                text: "start_time"
            }
            Rec_header{
                id: header_end_time;

                width:100
                height: 30
                text: "end_time"
            }
            Rec_header{
                id: header_soc_start;

                width:100
                height: 30
                text: "soc_start"
            }
            Rec_header{
                id: header_soc_end;

                width:100
                height: 30
                text: "soc_end"
            }
            Rec_header{
                id: header_advance_payment;

                width:100
                height: 30
                text: "advance_pay"
            }
            Rec_header{
                id: header_cancel_payment;

                width:100
                height: 30
                text: "cancel_pay"
            }
            Rec_header{
                id: header_actual_payment;

                width:100
                height: 30
                text: "actual_pay"
            }
            Rec_header{
                id: header_session_status;

                width:150
                height: 30
                text: "status"
            }
            Rec_header{
                id: header_stop_reason;

                width:100
                height: 30
                text: "stop_reason"
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

                        width: 110
                        height: 30
                        text: model.ocpp_tx_id
                    }
                    Rec_data{
                        id: header_card_uid2;

                        width: 160
                        height: 30
                        text: model.card_uid
                    }
                    Rec_data{
                        id: header_start_time2;

                        width:110
                        height: 30
                        text: model.start_time
                    }
                    Rec_data{
                        id: header_end_time2;

                        width:110
                        height: 30
                        text: model.end_time
                    }
                    Rec_data{
                        id: header_soc_start2;

                        width:110
                        height: 30
                        text: model.soc_start
                    }
                    Rec_data{
                        id: header_soc_end2;

                        width:110
                        height: 30
                        text: model.soc_end
                    }
                    Rec_data{
                        id: header_advance_payment2;

                        width:110
                        height: 30
                        text: model.advance_payment
                    }
                    Rec_data{
                        id: header_cancel_payment2;

                        width:110
                        height: 30
                        text: model.cancel_payment
                    }
                    Rec_data{
                        id: header_actual_payment2;

                        width:110
                        height: 30
                        text: model.actual_payment
                    }
                    Rec_data{
                        id: header_session_status2;

                        width:160
                        height: 30
                        text: model.session_status
                    }
                    Rec_data{
                        id: header_stop_reason2;

                        width:105
                        height: 30
                        text: model.stop_reason
                    }

                }

            } // delegate
        } // root_rec_lView
    } // root_rec
}
