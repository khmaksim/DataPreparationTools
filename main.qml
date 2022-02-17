import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Stack")

    property var configConnectToDB: ({})

    Settings {
        id: settingsConnectDatabase
        property string host: "localhost"
        property int port: 5432
        property string nameDatabase: "postgres"
        property string user: "postgres"
        property string password: ""
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("View data")
                width: parent.width
                onClicked: {
                    stackView.push("ViewData.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    stackView.push("SettingsView.qml")
//                    stackView.currentItem.readSettings()
                    drawer.close()
                }
            }
//            ItemDelegate {
//                text: qsTr("Page 2")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page2Form.ui.qml")
//                    drawer.close()
//                }
//            }
            ItemDelegate {
                text: qsTr("Quit")
                width: parent.width
                onClicked: {
                    drawer.close()
                    window.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }

    function readSettings() {
        configConnectToDB["host"] = settingsConnectDatabase.host
        configConnectToDB["port"] = settingsConnectDatabase.port
        configConnectToDB["nameDatabase"] = settingsConnectDatabase.nameDatabase
        configConnectToDB["user"] = settingsConnectDatabase.user
        configConnectToDB["password"] = settingsConnectDatabase.password

        console.log('-ReadSettings[main]-')
        console.log(configConnectToDB["host"])
        console.log(configConnectToDB["port"])
        console.log(configConnectToDB["nameDatabase"])
        console.log(configConnectToDB["user"])
        console.log(configConnectToDB["password"])
        console.log('---')
    }

    Component.onCompleted: {
        readSettings();
        dataManagement.createShp();
    }
}
