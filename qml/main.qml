import QtQuick 2.9
import QtQuick.Window 2.3

import Game 1.0
import "."

Window {
    id: win

    color: "black"

    function changeMode(mode)
    {
        mainGUI.mainContent.changeMode(mode);
    }

    function updateEverything()
    {
        mainGUI.updateEverything();
    }

    //for h4x
    property alias gameTimerInterval: gameTimer.interval
    property alias gameTimerRunning: gameTimer.running

    property alias enableFPSCounter: mainGUI.enableFPSCounter

    visible: true
    width: 450
    height: 800
    title: "Adversity"

    onWidthChanged: Globals.windowWidth = width;
    onHeightChanged: Globals.windowHeight = height;

    MainGUI {
        id: mainGUI

        visible: false

        function updateContent(minimal)
        {
            if (minimal)
                mainContent.updateClock();
            else
                mainContent.updateEverything();
        }

        transform: [
            Scale {
                id: scale

                xScale: win.width/mainGUI.width
                yScale: win.height/mainGUI.height
            },
            Translate {
                x: (win.width-mainGUI.width*scale.xScale)/2
                y: (win.height-mainGUI.height*scale.yScale)/2
            }
        ]
    }

    Timer {
        id: gameTimer

        interval: 625
        running: false
        repeat: true
        onTriggered: {
            GameApi.base.gameClock.updateClock();
            mainGUI.updateClock();
            if (GameApi.base.gameClock.hasDayChangedLately())
                mainGUI.updateContent(0);
        }
    }

    SplashScreen {
        id: splash

        anchors.fill: parent

        minDurationInMs: 1500
        splashDisappearAnimationDuration: 500
        canCloseRefreshingRateInMs: 100
        canClose: false
        splashImageSource: "qrc:/graphics/splash.png"

        onShowing: mainGUI.visible = false;
        onHiding: {
            gameTimer.running = true;
            mainGUI.updateEverything();
            mainGUI.visible = true;
            console.info("[",Math.floor(GameApi.startupTimerElapsed()/1000),'.',('00' + GameApi.startupTimerElapsed()%1000).substr(-3),"] Splash screen has started hiding");
            console.info("[",Math.floor((GameApi.startupTimerElapsed()+splashDisappearAnimationDuration)/1000),'.',('00' + (GameApi.startupTimerElapsed()+splashDisappearAnimationDuration)%1000).substr(-3),"] Splash screen has hidden");
        }
    }

    Component.onCompleted: {
//        splash.show();
        Globals.windowWidth = width;
        Globals.windowHeight = height;mainGUI.visible=true;
        GameApi.savesManager.createNewSave("A",""); // doesn't create new saves, needs to be soon replaced
//        changeMode(1);
        splash.canClose = true;
        console.info("[",Math.floor(GameApi.startupTimerElapsed()/1000),'.',('00' + GameApi.startupTimerElapsed()%1000).substr(-3),"] Main QML component has been built");
    }
    onClosing: close.accepted = mainGUI.mainContent.reactToExit();
}
