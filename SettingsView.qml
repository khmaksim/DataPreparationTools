import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.3

Page {
    title: qsTr("Settings")

    Row {
        anchors.fill: parent
        rightPadding: 8
        bottomPadding: 8
        leftPadding: 8
        topPadding: 8

        Column {
            id: column
            width: implicitWidth
            height: implicitHeight
            spacing: 0

            Label {
                id: hostLabel
                text: qsTr("Host")
                font.pixelSize: 14
            }
            TextField {
                id: hostInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                placeholderText: "localhost"
                text: settingsConnectDatabase.host
            }
            Label {
                id: portLabel
                text: qsTr("Port")
                font.pixelSize: 14
            }
            TextField {
                id: portInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                placeholderText: "5432"
                text: settingsConnectDatabase.port
            }
            Label {
                id: nameDatabaseLabel
                text: qsTr("Database name")
                font.pixelSize: 14
            }
            TextField {
                id: nameDatabaseInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                placeholderText: "postgres"
                text: settingsConnectDatabase.nameDatabase
            }
            Label {
                id: userNameLabel
                text: qsTr("User name")
                font.pixelSize: 14
            }
            TextField {
                id: userNameInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                placeholderText: "postgres"
                text: settingsConnectDatabase.user
            }
            Label {
                id: passwordLabel
                text: qsTr("Password")
                font.pixelSize: 14
            }
            TextField {
                id: passwordInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                echoMode: TextInput.Password
                text: settingsConnectDatabase.password
            }

            Button {
                id: button
                height: 36
                text: qsTr("Accept")
                anchors.right: parent.right
                font.pixelSize: 14
                //                anchors.rightMargin: 220
                rightPadding: 16
                leftPadding: 16
                autoExclusive: false
                checked: false
                checkable: false
                highlighted: false
                flat: false

                onClicked: writeSettings()
            }
            Rectangle { width: parent.width; height: 1; color: "black"; }

            Label {
                text: qsTr("Path to ArcGIS Python")
                font.pixelSize: 14
            }
            Row {
                spacing: 0

                TextField {
                    id: pathToPython
                    width: 480
                    height: 48
                    font.pixelSize: 16
                    rightPadding: 12
                    leftPadding: 16
                    readOnly: true
                    text: settingsConnectDatabase.pathToPython.replace(new RegExp('/','g'), '\\')/*.replace('/', '\\')*/
                    //                    text: settingsConnectDatabase.password
                }
                ToolButton {
                    id: showPathDialogButton
                    icon.source: "qrc:/icons/res/icons/1x/outline_folder_white_24dp.png"
                    onClicked: selectPathDialog.open()
                }
            }
        }
    }

    FileDialog {
        id: selectPathDialog
        title: "Please choose a path to ArcGIS Python"
        folder: shortcuts.home
        nameFilters: ["Python (*.exe)"]
        onAccepted: {
            if (!fileUrl.toString().includes("python")) {
                messageDialog.open()
                return
            }

            var path = folder.toString();
            // remove prefixed "file:///"
            path = path.replace(/^(file:\/{3})/,"");
            // unescape html codes like '%23' for '#'
            var cleanPath = decodeURIComponent(path);
            settingsConnectDatabase.pathToPython = cleanPath
            dataManagement.pathToPython = cleanPath
        }
    }

    MessageDialog {
         id: messageDialog
         text: qsTr("Incorrect directory selected!")
         icon: StandardIcon.Warning
         standardButtons: StandardButton.Close
         onButtonClicked: close()
     }

    function writeSettings() {
        settingsConnectDatabase.host = hostInput.text
        settingsConnectDatabase.port = Number(portInput.text)
        settingsConnectDatabase.nameDatabase= nameDatabaseInput.text
        settingsConnectDatabase.user = userNameInput.text
        settingsConnectDatabase.password = passwordInput.text
    }

    //    function readSettings() {
    //        hostInput.text = settingsConnectDatabase.host
    //        portInput.text = settingsConnectDatabase.port
    //        nameDatabaseInput.text = settingsConnectDatabase.nameDatabase
    //        userNameInput.text = settingsConnectDatabase.user
    //        passwordInput.text = settingsConnectDatabase.password
    //    }
}
