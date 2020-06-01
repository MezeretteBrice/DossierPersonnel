import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.10
import QtQuick.Templates 2.5
import QtMultimedia 5.12

Page {
    id: identification
    width: 600
    height: 600
    property alias button: button
    property alias textField: textField

    header: Label {
        text: qsTr("IDENTIFICATION")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }
    Image {
        id: image
        x: 164
        y: 100
        width: 200
        height: 200
        source: "Logo_NFC.jpg"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image1
        x: 15
        y: 100
        width: 200
        height: 200
        rotation: 180
        source: "Logo_NFC.jpg"
        fillMode: Image.PreserveAspectFit

        RoundButton {
            id: roundButton
            x: 9
            y: 80
            text: "+"
        }
    }

    TextField {
        id: textField
        x: 95
        y: 317
        text: qsTr("id de l'agent")
    }

    Button {
        id: button
        x: 152
        y: 376
        text: qsTr("Identification")
    }
}
