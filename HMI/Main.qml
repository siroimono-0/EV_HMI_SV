import QtQuick
import QtQuick.Controls
import HMI 1.0

Window {
    id: root
    width: 1280
    height: 800
    visible: true
    title: qsTr("Hello World")
    flags: Qt.FramelessWindowHint

    property var ld_select_amount_item;
    property var ld_select_card_item;
    property var ld_Input_Time_item;
    property var ld_Input_Won_item;
    property var ld_Input_Kwh_item;
    property int cnt: 0;
    property bool indicator_run: cpp_module.statStore.soc_connect_stat ? cpp_module.statStore.soc_connect_stat : false;

    function stk_pop()
    {
        root_stkView.pop();
    }

    function stk_home()
    {
        cnt = root_stkView.currentItem.stk_depth;
        while(cnt > 2)
        {
            root_stkView.pop();
            cnt--;
        }
    }

    function stk_push_emsPage()
    {
        root_stkView.push("Ems_Charging.qml", {"mainWin": root});
    }

    function timer_reset(debug)
    {
        // root_stkView.currentItem.pageName;
        console.log(debug);
        timer_clear.restart();
    }
    function netErr_charging_monitoring()
    {
        root.stk_home();
        root_stkView.currentItem.screen_stop();
        root_stkView.push("Disconnect_nomal.qml", {"mainWin": root});
    }

    Component.onCompleted: {
        // root.indicator_run = ;
    }

    Connections{
        target: cpp_module

        function onSig_Re_connect_Success_ToQml()
        {
            let page_name = root_stkView.currentItem.pageName;
            if(page_name === "Disconnect_Nomal" || page_name === "Disconnect_Unique")
            {
                root_stkView.pop();
            }
        }

        function onSig_Re_connect_UpTo_5_ToQml()
        {
            let page_name = root_stkView.currentItem.pageName;
            console.log(page_name);

            if(page_name === "Maintenance")
            {
                return;
            }

            if(page_name === "Charging_Ready")
            {
                // 선승인 금액 처리해야댐 강제로 0원
                // 차징로그 ems 하나 남겨놓음

                /*
                typedef enum NET_ERR_CHARGING_TYPE {
                    CHARGING_READY = 0,
                    CHARGING_FINISHED = 1
                } NET_ERR_CHARGING_TYPE;*/

                cpp_module.netErr_Card_save_To_StatStore(0);
                // cpp_module.ems_Charging_Ready_To_StatStore();

                // 정지 사유 초기화
                cpp_module.set_stop_reason("Network Err");
                // 충전 바로 마무리 한걸로 DB 업데이트
                // cpp_module.charging_finished_To_statStore();
                cpp_module.netErr_Charging_ready_save_To_StatStore();


                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("Disconnect_nomal.qml", {"mainWin": root});
            }
            else if(page_name === "Charging_Monitoring")
            {
                // 정지 사유 초기화
                // cpp_module.set_stop_reason("EMS");
                // root_stkView.currentItem.ems_btn();

                cpp_module.netErr_Card_save_To_StatStore(1);
                // cpp_module.ems_Charging_Ready_To_StatStore();

                // 정지 사유 초기화
                cpp_module.set_stop_reason("Network Err");
                // 충전 바로 마무리 한걸로 DB 업데이트
                // cpp_module.charging_finished_To_statStore();
                cpp_module.netErr_Charging_monitoring_save_To_StatStore();

                cpp_module.charging_stop_To_serial();

                //
            }
            else
            {
                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("Disconnect_nomal.qml", {"mainWin": root});
            }
        }

        function onSig_ems_ToQml()
        {
            let page_name = root_stkView.currentItem.pageName;
            console.log(page_name);

            if(page_name === "Maintenance")
            {
                return;
            }

            if(page_name === "Charging_Ready")
            {
                // 선승인 금액 처리해야댐 강제로 0원
                // 차징로그 ems 하나 남겨놓음
                cpp_module.ems_Charging_Ready_To_StatStore();

                // 정지 사유 초기화
                cpp_module.set_stop_reason("EMS");
                // 충전 바로 마무리 한걸로 DB 업데이트
                cpp_module.charging_finished_To_statStore();

                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("Ems_Nomal.qml", {"mainWin": root});
            }
            else if(page_name === "Charging_Monitoring")
            {
                // 정지 사유 초기화
                cpp_module.set_stop_reason("EMS");
                root_stkView.currentItem.ems_btn();
            }
            else
            {
                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("Ems_Nomal.qml", {"mainWin": root});
            }
        }

        function onSig_screen_move_maintenance_ToQml()
        {
            let page_name = root_stkView.currentItem.pageName;
            console.log(page_name);
            if(page_name !== "Charging_Ready" &&
                page_name !== "Charging_Monitoring")
            {
                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("Maintenance.qml", {"mainWin": root});
            }
        }

        function onSig_screen_move_home_ToQml()
        {
            let page_name = root_stkView.currentItem.pageName;
            console.log(page_name);

            if(page_name === "Charging_Ready")
            {
                // 선승인 금액 처리해야댐 강제로 0원
                // 차징로그 ems 하나 남겨놓음
                cpp_module.ems_Charging_Ready_To_StatStore();

                // 정지 사유 초기화
                cpp_module.set_stop_reason("Admin");
                // 충전 바로 마무리 한걸로 DB 업데이트
                cpp_module.charging_finished_To_statStore();

                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("HMI_main.qml", {"mainWin": root});
            }
            else if(page_name === "Charging_Monitoring")
            {
                // 정지 사유 초기화
                cpp_module.set_stop_reason("Admin");
                root_stkView.currentItem.admin_stop();
            }
            else
            {
                root.stk_home();
                root_stkView.currentItem.screen_stop();
                root_stkView.push("HMI_main.qml", {"mainWin": root});
            }
        }
    }

    Loader{
        id: ld_select_amount
        source: "Select_amount.qml"
        active: true

        onLoaded: {
            item.mainWin = root;
            item.stk_depth = 3
            root.ld_select_amount_item = item;
            console.log("Load __ Select_amount.qml");
        }
    }

    Loader{
        id: ld_select_card
        source: "Select_card.qml"
        active: true

        onLoaded: {
            item.mainWin = root;
            ld_select_card_item = item;
            console.log("Load __ Select_card.qml");
        }
    }

    Loader{
        id: ld_Input_Time
        source: "Input_Time.qml"
        active: true

        onLoaded: {
            item.mainWin = root;
            item.stk_depth = 4
            ld_Input_Time_item = item;
            console.log("Load __ ld_Input_Time.qml");
        }
    }

    Loader{
        id: ld_Input_Won
        source: "Input_Won.qml"
        active: true

        onLoaded: {
            item.mainWin = root;
            item.stk_depth = 4
            ld_Input_Won_item = item;
            console.log("Load __ ld_Input_Won.qml");
        }
    }

    Loader{
        id: ld_Input_Kwh
        source: "Input_Kwh.qml"
        active: true

        onLoaded: {
            item.mainWin = root;
            item.stk_depth = 4
            ld_Input_Kwh_item = item;
            console.log("Load __ ld_Input_Kwh.qml");
        }
    }

    Timer{
        id: timer_clear
        interval: 5 * 60 * 1000
        repeat: false;
        running: true

        onTriggered: {
            let page_name = root_stkView.currentItem.pageName;
            if(page_name === "Charging_Ready" ||
                    page_name === "Charging_Monitoring" ||
                    page_name === "Start_page" ||
                    page_name === "HMI_main" ||
                    page_name === "Maintenance")
            {
                return;
            }
            else
            {
                root.stk_home();
            }
        }
    }

    Rectangle{
        id: indi
        anchors.fill: parent
        z: -999;
        color: "transparent"
        visible: false

        state: root.indicator_run ? "hide" : "nomal";

        states: [
            State {
                name:"hide"
                PropertyChanges {
                    target: indi
                    visible: false
                    z: -999
                }
            },
            State {
                name:"nomal"
                PropertyChanges {
                    target: indi
                    visible: true
                    z: 999
                }
            }

        ]


        BusyIndicator{
            id: common_indicator

            anchors.centerIn: parent
            width: 500; height: 500;
            visible: indi.visible
            running: indi.visible
        }

        MouseArea{
            anchors.fill: parent
            visible: indi.visible
            onPressed: function(o_ev) {
                o_ev.accepted = true;
            }

            onClicked: function(o_ev) {
                o_ev.accepted = true;
            }

            onReleased: function(o_ev) {
                o_ev.accepted = true;
            }
        }

    }

    StackView{
        id: root_stkView
        // initialItem: "Start_page.qml"
        // initialItem: "Input_Time.qml"
        // initialItem: "Charging_Monitoring.qml"
        // initialItem: "./Qml_Module/BackGround_Amount.qml"
        // initialItem: "Charging_Complet.qml"

        anchors.fill: parent
        // any 넣어서 duration 조금씩 추가해서
        // pop하고나서 stk에서 view depth 확인할 시간 줘야댐
        pushEnter: Transition {

        }
        popEnter: Transition {

        }
        pushExit: Transition {

        }
        popExit: Transition {

        }
        replaceEnter: Transition {

        }
        replaceExit: Transition {

        }


        Component.onCompleted: {
            root_stkView.push("Start_page.qml", {"mainWin": root});
            // root_stkView.push(ld_select_amount.item , {"mainWin": root});
            // root_stkView.push("Test.qml", {"mainWin": root});
            // root_stkView.push("Ems_Nomal.qml", {"mainWin": root});
            // root_stkView.push("Ems_Charging.qml", {"mainWin": root});
        }
    }
    /*
Card_Failed
Card_Ready
Card_Socket
Charging_Complet
Input_Kwh
Input_Time
Input_Won
Select_amount
Select_card
Select_charge
                  */
}
