import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    title: qsTr("Home")

    GridView {
        id: gridView
        x: 176
        y: 162
        width: 374
        height: 260
        transformOrigin: Item.Center
        delegate: Item {
            x: 5
            height: 50
            Column {
                spacing: 5
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        cellWidth: 70
        model: ListModel {
            ListElement {}

            ListElement {}
        }
        cellHeight: 70

        Button {
            id: airwaysButton
            x: -73
            y: -111
            text: qsTr("AIRWAYS")
        }

        Button {
            id: button
            x: 80
            y: -109
            text: qsTr("Button")
        }
    }
}
