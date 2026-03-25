import QtQuick
import QtQuick.Controls
import HMI 1.0

Window {
    id: root
    width: 1280
    height: 800
    visible: true
    title: qsTr("Hello World")

    function stk_home()
    {
        while(StackView.depth > 2)
        {
            StackView.pop();
        }
    }

    function timer_reset(debug)
    {
        // root_stkView.currentItem.pageName;
        console.log(debug);
        timer_clear.restart();
    }

    Timer{
        id: timer_clear
        interval: 5 * 60 * 1000
        repeat: false;
        running: true

        onTriggered: {
            if(root_stkView.currentItem.pageNmae === "Charging_Ready" ||
                    root_stkView.currentItem.pageNmae === "Charging_Monitoring" || root_stkView.currentItem.pageNmae === "Start_page" ||  root_stkView.currentItem.pageNmae === "HMI_main")
            {
                // return;
            }
            else
            {
                root.stk_home();
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
    }

    Component.onCompleted: {
        root_stkView.push("Start_page.qml", {"mainWin": root});
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
