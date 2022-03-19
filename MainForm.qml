import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

Page {
    id: page
    title: qsTr("Main")

    Grid {
        id: grid
        anchors.fill: parent
        spacing: 5
        verticalItemAlignment: Grid.AlignVCenter
        horizontalItemAlignment: Grid.AlignHCenter
        padding: 10
        rows: 3
        columns: 4

        Button {
            id: airwaysButton
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("AIRWAYS")
            property string name: "airways"

            onClicked: {
                stackView.pop()
                stackView.push("ViewData.qml")
                dataManagement.fillDataModel(name, configConnectToDB)
            }
        }

        Button {
            id: button
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("POINTS")
//            enabled: false
            property string name: "points"

            onClicked: {
                stackView.pop()
                stackView.push("ViewData.qml")
                dataManagement.fillDataModel(name, configConnectToDB)
            }
        }

        Button {
            id: button1
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }

        Button {
            id: button2
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }
        Button {
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
        }

        function onClickedButton() {

        }

        function getWidthItem() {
            return ((width - (columns - 1) * spacing - padding * 2) / columns)
        }

        function getHeightItem() {
            return ((height - (rows - 1) * spacing - padding * 2) / rows)
        }
    }

    Connections {
        target: dataManagement

        function onComplitedCreateShape() {
            messageDialog.title = qsTr("Information")
            messageDialog.text = qsTr("File creation completed.")
            messageDialog.icon = StandardIcon.Information
            messageDialog.open()
        }

        function onRejectedDataSource() {
            messageDialog.title = qsTr("Warning")
            messageDialog.text = qsTr("Failed to connect to the data source.")
            messageDialog.icon = StandardIcon.Warning
            messageDialog.open()
        }
    }

    MessageDialog {
         id: messageDialog
//         text: qsTr("File creation completed.")
         standardButtons: StandardButton.Close
         onButtonClicked: close()
     }
}
