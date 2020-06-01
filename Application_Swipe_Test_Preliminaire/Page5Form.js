function prendrePhoto() {
    visu.visible = true
    //temps.start()
    appareil.imageCapture.capture()
    appareil.imageCapture.imageSaved("/sdcard")
    appareil.imageCapture.captureToLocation("/sdcard")
    //captureToLocalisation("/Catégories/DCIM/Camera")
}
