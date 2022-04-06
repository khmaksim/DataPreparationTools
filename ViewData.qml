import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtQuick.Controls 1.4 as OldControls
import QtQml 2.12
import QtQuick.Dialogs 1.3
import com.aviacominfo.datapreparationtools.datamodel 0.1

Page {
    title: qsTr("View data")
    objectName: "ViewData"

    TableView {
        id: viewData
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
//        leftMargin: 10
//        topMargin: columnsHeader.implicitHeight
        clip: true
        columnWidthProvider: function (column) { return 120; }

        model: dataManagement.dataModel()
        ScrollBar.vertical: ScrollBar{}

//        Rectangle {
//            z: 3
//            color: "#222222"
//            y: viewData.contentY
//            x: viewData.contentX
//            width: viewData.leftMargin
//            height: viewData.topMargin
//        }

//        Row {
//            id: columnsHeader
//            y: viewData.contentY
//            z: 2
//            spacing: 1

//            Repeater {
//                model: viewData.columns > 0 ? viewData.columns : 1
//                Label {
//                    width: viewData.columnWidthProvider(modelData)
//                    height: 35
//                    text: dataManagement.dataModel().headerData(modelData, Qt.Horizontal)
//                    color: "#aaaaaa"
//                    font.pixelSize: 12
//                    padding: 10
//                    verticalAlignment: Text.AlignVCenter
//                    background: Rectangle { color: "#d5d5d5" }
//                }
//            }
//        }

        delegate: Rectangle {
            implicitWidth: 120
            implicitHeight: 25
            Text {
                text: display
                padding: 5
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Component.onCompleted: {
            if (stackView.titleViewData.length === 0)
                title = qsTr("View data")
            else
                title = qsTr("View data") + ' - ' + stackView.titleViewData
//            dataManagement.getData()
        }
//        sortIndicatorVisible: true

//        OldControls.TableViewColumn {title: "#"; role: "order"; width: 70 }
//        OldControls.TableViewColumn {title: "markId"; role: "markId"; width: 70 }
//        OldControls.TableViewColumn {title: "trackId"; role: "trackId"; width: 70   }
//        OldControls.TableViewColumn {title: "rlsId"; role: "rlsId"; width: 70 }
//        OldControls.TableViewColumn {title: "time"; role: "time"; width: 70 }
//        OldControls.TableViewColumn {title: "position"; role: "position"; width: 70 }
//        OldControls.TableViewColumn {title: "velocity"; role: "velocity"; width: 70 }
//        OldControls.TableViewColumn {title: "acceleration"; role: "acceleration"; width: 70 }
//        OldControls.TableViewColumn {title: "sigmasRBetaEps"; role: "sigmasRBetaEps"; width: 70 }
//        OldControls.TableViewColumn {title: "sigmasdRdBetadEps"; role: "sigmasdRdBetadEps"; width: 70 }

//        onSortIndicatorColumnChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)
//        onSortIndicatorOrderChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)
        ScrollIndicator.vertical: ScrollIndicator{}
    }
}
