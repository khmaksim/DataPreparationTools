import QtQuick 2.12
import QtQuick.Controls 2.5
import com.aviacominfo.datapreparationtools.datamodel 0.1

Page {
    title: qsTr("View data")

    TableView {
        id: viewData
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
//        clip: true

        model: dataManagement.dataModel() //DataModel {}

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            Text {
                text: display
            }
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
    }
    Component.onCompleted: {
        dataManagement.getData()
    }
}
