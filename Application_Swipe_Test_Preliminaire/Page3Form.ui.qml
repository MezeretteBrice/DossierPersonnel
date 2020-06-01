import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.12
import QtNfc 5.11

Page {
    id: deroulementRonde
    width: 600
    height: 600
    property alias buttonAfficherRonde: buttonAfficherRonde
    property alias textFieldPointeaux: textFieldPointeaux
    property alias textFieldErreur: textFieldErreur
    property alias comboBoxPointeau: comboBoxPointeau
    property alias buttonScannerPointeau: buttonScannerPointeau
    property alias deroulementRonde: deroulementRonde
    property alias buttonIgnorer: buttonIgnorer
    property alias buttonAnomalie: buttonAnomalie

    Connections {
        target: BaseBDD
    }

    header: Label {
        text: qsTr("Déroulement de la ronde")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    NearField {
        filter: [
            NdefFilter {
                type: "U"
                typeNameFormat: NdefRecord.NfcRtd
                minimum: 1
                maximum: 1
            }
        ]
        orderMatch: false
    }

    Button {
        id: buttonAnomalie
        x: 146
        y: 223
        width: 150
        text: qsTr("Anomalie")
    }

    Button {
        id: buttonIgnorer
        x: 146
        y: 269
        width: 150
        text: qsTr("Ignorer le pointeau")
    }

    TextField {
        id: textFieldErreur
        x: 146
        y: 85
        width: 150
        height: 40
        text: "Aucune Erreur"
    }

    Button {
        id: buttonRapport
        x: 23
        y: 328
        width: 256
        text: qsTr("Envoyer rapport")
    }
    Button {
        id: buttonScannerPointeau
        x: 146
        y: 177
        width: 150
        height: 40
        text: qsTr("Scanner Pointeau")
    }
    ComboBox {
        id: comboBoxPointeau
        x: 0
        y: 33
    }

    TextField {
        id: textFieldPointeaux
        x: 146
        y: 131
        width: 150
        height: 40
    }

    Button {
        id: buttonAfficherRonde
        x: 146
        y: 33
        width: 150
        height: 40
        text: qsTr("Afficher la ronde")
    }
}
