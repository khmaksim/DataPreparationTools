import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.settings 1.0

Page {
    width: 600
    height: 400
    title: qsTr("Settings")

    //        title: qsTr("Connect to database")
    Row {
        id: row
        anchors.fill: parent
        rightPadding: 8
        bottomPadding: 8
        leftPadding: 8
        topPadding: 8

        Column {
            id: column
            width: 300
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
            }
            Label {
                id: databaseLabel
                text: qsTr("Database name")
                font.pixelSize: 14
            }
            TextField {
                id: databaseInput
                width: 280
                height: 48
                font.pixelSize: 16
                rightPadding: 12
                leftPadding: 16
                placeholderText: "postgres"
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
            }

            Button {
                id: button
                height: 36
                text: qsTr("Accept")
                anchors.right: parent.right
                font.pixelSize: 14
                anchors.rightMargin: 220
                rightPadding: 16
                leftPadding: 16
                autoExclusive: false
                checked: false
                checkable: false
                highlighted: false
                flat: false

                onClicked:  {
                    settingsConnectDatabase.host = hostInput.text
                    settingsConnectDatabase.port = Number(portInput.text)
                    settingsConnectDatabase.databaseName = databaseInput.text
                    settingsConnectDatabase.userName = userNameInput.text
                    settingsConnectDatabase.password = passwordInput.text
                }
            }
        }
    }

    function readSettings() {
        console.log("qweqwe")
        hostInput.text = settingsConnectDatabase.host
        portInput.text = settingsConnectDatabase.port
        databaseInput.text = settingsConnectDatabase.databaseName
        userNameInput.text = settingsConnectDatabase.userName
        passwordInput.text = settingsConnectDatabase.password
    }
}
