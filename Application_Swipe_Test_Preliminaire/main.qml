import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtMultimedia 5.12
import QtNfc 5.12
import "main.js" as Fonction

ApplicationWindow {
    visible: true
    title: qsTr("Application_Swipe")
    width: 640
    height: 480
    property bool erreur: BaseBDD.erreurConnexion

    onErreurChanged: {
        if (BaseBDD.erreurConnexion)
        {
            messageErreur.text = qsTr("Problème d'ouverture de la base de données !")
            erreurDialog.open()
        }
    }

    SwipeView{
        id: leRondier
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            id: identification
        }

        Page2Form {
            id: choixRonde
            buttonRonde.onClicked: {
                Fonction.changerPage();
                BaseBDD.choisirRonde(comboBoxSelectionnerRonde.currentText)
            }
        }

        Page3Form{
            id : deroulementRonde
            buttonAfficherRonde.onClicked: {
                    comboBoxPointeau.model = BaseBDD.listePointeaux
            }
            buttonAnomalie.onClicked: {
                Fonction.changerPage();
                BaseBDD.enregistrerPointeaux(comboBoxPointeau.currentText)
                comboBoxPointeau.currentIndex = comboBoxPointeau.currentIndex + 1;
            }

            buttonIgnorer.onClicked: {
                Fonction.changerPage();

                if(anomalie.textFieldAnomalie.text == "Description de l'anomalie"){
                    anomalie.textFieldAnomalie.text = "Pointeau ignoré";
                }
                comboBoxPointeau.currentIndex = comboBoxPointeau.currentIndex + 1;
            }

            buttonScannerPointeau.onClicked: {
                if(textFieldPointeaux.text === comboBoxPointeau.currentText){
                    textFieldErreur.text === "Aucune Erreur";
                    BaseBDD.enregistrer(comboBoxPointeau.currentText);
                    comboBoxPointeau.currentIndex = comboBoxPointeau.currentIndex + 1;
                }else {
                    if(textFieldErreur.text === "Aucune Erreur"){
                        textFieldErreur.text = "Erreur Parcours"
                    }
                }
            }
        }
        Page4Form{
            id: anomalie
            buttonPhoto.onClicked: {
                Fonction.changerPage();
            }
            buttonValiderPhoto.onClicked: {
                BaseBDD.enregistrerAnomalie(textFieldAnomalie.text)
                leRondier.currentIndex = leRondier.currentIndex-1;
                anomalie.textFieldAnomalie.text = "Description de l'anomalie"

            }
        }
        Page5Form{
            id: appareil
            toolButton.onClicked: {
                Fonction.prendrePhoto()
            }
        }
        Dialog {
            id: erreurDialog
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            standardButtons: Dialog.Close
            title: "Erreur"
            Label {
                id: messageErreur
                text: ""
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: leRondier.currentIndex

        TabButton {
            text: qsTr("Identification")
        }
        TabButton {
            text: qsTr("Selection")
        }
        TabButton {
            text: qsTr("Déroulement")
        }
        TabButton {
            text: qsTr("Anomalie")
        }
        TabButton {
            text: qsTr("Photo")
        }
    }
}
