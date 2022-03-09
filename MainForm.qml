import QtQuick 2.12
import QtQuick.Controls 2.5

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

            onClicked: {
                stackView.pop()
                stackView.push("ViewData.qml", {"nameQuery": "airways"})
//                dataManagement.getData(configConnectToDB)
            }
        }

        Button {
            id: button
            width: grid.getWidthItem()
            height: grid.getHeightItem()
            text: qsTr("Reserve")
            enabled: false
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

        function getWidthItem() {
            return ((width - (columns - 1) * spacing - padding * 2) / columns)
        }

        function getHeightItem() {
            return ((height - (rows - 1) * spacing - padding * 2) / rows)
        }
    }
}
