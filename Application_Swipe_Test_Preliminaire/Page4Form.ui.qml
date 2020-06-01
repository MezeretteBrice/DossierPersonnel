import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: anomalie
    width: 600
    height: 400
    property alias buttonValiderPhoto: buttonValiderPhoto
    property alias buttonPhoto: buttonPhoto
    property alias page4: anomalie
    property alias textFieldAnomalie: textFieldAnomalie

    header: Label {
        text: qsTr("Anomalie")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        id: labelCommentaireAnomalie
        x: 6
        y: 50
        width: 100
        height: 16
        text: qsTr("Description")
    }

    Label {
        id: labelPrendrePhoto
        x: 6
        y: 212
        width: 100
        height: 16
        text: qsTr("Prendre photo")
    }

    TextField {
        id: textFieldAnomalie
        x: 123
        y: 8
        width: 200
        height: 100
        placeholderText: qsTr("Text Field")
    }

    Button {
        id: buttonPhoto
        x: 123
        y: 200
        width: 200
        text: qsTr("Photo")

    }

    Button {
        id: buttonValiderPhoto
        x: 123
        y: 294
        width: 200
        height: 40
        text: qsTr("Valider anomalie")
    }
}
