import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtMultimedia 5.12
import "Page5Form.js" as Fonction

Page{
    id: page
    visible: true
    width: 640
    height: 480
    property alias toolButton: toolButton
    property alias visu: visu
    property alias page: page
    property alias video: video
    title: qsTr("Hello World")
    Camera {
        id: appareil
        exposure{
            exposureMode: Camera.ExposureAction
            manualIso: 800
        }
        focus{
            focusMode: CameraFocus.FocusContinuous
            focusPointMode: Camera.FocusPointAuto
        }
        imageProcessing{
            saturation: -1
            contrast: 1
        }
        flash.mode: Camera.FlashAuto
        imageCapture.onImageCaptured: visu.source = preview
        captureMode: Camera.CaptureStillImage
    }
    VideoOutput{
        id: video
        source: appareil
        anchors.fill: parent
        orientation: appareil.orientation
    }
    Image{
        id: visu
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
    }
    ToolButton{
        id: toolButton
        anchors{
            bottom: parent.bottom
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        icon{
            color: "black"
            width: 100
            height: 100
        }
        }
        background: Rectangle { color:  "green" }
}

