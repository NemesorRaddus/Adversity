import QtQuick 2.0
import QtQuick.Window 2.2

import Game 1.0
import "."

Window {
    id: root

    visible: false
    width: 450
    height: 800
    title: "Game"

    onWidthChanged: Globals.windowWidth = width;
    onHeightChanged: Globals.windowHeight = height;

    Loader {
        id: mainLoader

        anchors.fill: parent

        Timer {
            id: turnoffTimer

            interval: splash.canCloseRefreshingRateInMs
            running: false
            repeat: true

            onTriggered: {
                if (Globals.appGUIReady)
                {
                    running = false;
                    splash.canClose = true;
                }
            }
        }

        onStatusChanged: turnoffTimer.start();
    }

    SplashScreen {
        id: splash

        minDurationInMs: 2500
        canCloseRefreshingRateInMs: 100
        splashImageSource: "qrc:/graphics/splash.jpg"
        canClose: false
        splashDisappearAnimationDuration: 500

        anchors.fill: parent

        Component.onCompleted: show()
    }

    Component.onCompleted:  {
        visible = true;
        Globals.appGUIReady=false;
        mainLoader.source = "qrc:/qml/main.qml"
    }
    onClosing: {
        mainLoader.item.emulatorOfOnClosing()
    }
}
