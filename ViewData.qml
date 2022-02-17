import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtQuick.Controls 1.4 as OldControls
import QtQml 2.12
import com.aviacominfo.datapreparationtools.datamodel 0.1

Page {
    title: qsTr("View data")
    property string nameQuery: ""

    TableView {
        id: viewData
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        leftMargin: 10
        rightMargin: 10
        clip: true

        model: dataManagement.dataModel()

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            Text {
                text: display
                padding: 5
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Component.onCompleted: {

            dataManagement.getData(configConnectToDB)
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
    }
}
