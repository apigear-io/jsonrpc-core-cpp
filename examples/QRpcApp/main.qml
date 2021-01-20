import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import net.rpc 1.0


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    GridLayout {
        columns: 6
        anchors.fill: parent
        Button {
            text: "Call"
            onClicked: jsonRpc.doCall("echo", { message: "world" })
        }
        Button {
            text:  "Trigger Shutdown"
            onClicked: jsonRpc.doCall("triggerShutdown", { timeout: 5 })
        }
        Button {
            text:  "Notify Shutdown"
            onClicked: jsonRpc.doNotify("shutdown", { timeout: 5 })
        }
    }


    JsonRpc {
        id: jsonRpc
        onNotify: {
            console.log(method, params)
        }
    }

    Component.onCompleted: {
        jsonRpc.open("ws://127.0.0.1:8080")
    }
}
