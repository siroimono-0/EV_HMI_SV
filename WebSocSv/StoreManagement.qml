import QtQuick
import QtQuick.Controls
import WebSocSv 1.0

Item {
    id: root

    property real bashW: 1920;
    property real bashH: 1080;
    property real uiScale: Math.min(root.width / root.bashW, root.height / root.bashH);

    function cnv (val)
    {
        return val * root.uiScale;
    }

    RecBtn{
        id: root_createStore
        width: root.cnv(200); height: root.cnv(80);
        anchors.centerIn: parent
        // cppSv.
        onSig_Clicked: function()
        {
            popup.open();
        }
    }

    PopUp_CreateStore_DB{
        id: popup
        onSig_Clicked: function(id, name, location) {
            // cppSv.
        }
    }


}
