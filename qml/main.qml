import QtQuick 2.9
import QtQuick.Window 2.3

import Game 1.0
import "."

Window {
    id: win

    color: "black"

    function changeMode(mode)
    {
        mainGUI.mainContent.reportsList.state = "hidden";
        mainGUI.mainContent.settings.hide();

        if (currentMode == 0)
        {
            mainGUI.mainContent.missionsGUI.returnToDefault();
        }
        else if (currentMode == 1)
        {
            mainGUI.mainContent.buildingsGUI.returnToDefault();
        }
        else if (currentMode == 2)
        {
            mainGUI.mainContent.mercenariesGUI.returnToDefault();
        }

        currentMode = mode;

        if (mode == 0)
        {
            mainGUI.mainContent.missionsGUI.state = "";
            mainGUI.mainContent.buildingsGUI.state = "hiddenRight";
            mainGUI.mainContent.mercenariesGUI.state = "hiddenRight2";
        }
        else if (mode == 1)
        {
            mainGUI.mainContent.missionsGUI.state = "hiddenLeft";
            mainGUI.mainContent.buildingsGUI.state = "";
            mainGUI.mainContent.mercenariesGUI.state = "hiddenRight";
        }
        else if (mode == 2)
        {
            mainGUI.mainContent.missionsGUI.state = "hiddenLeft2";
            mainGUI.mainContent.buildingsGUI.state = "hiddenLeft";
            mainGUI.mainContent.mercenariesGUI.state = "";
        }
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

        onEnableFPSCounterChanged: mainContent.settings.acknowledgeFPSToggle(enableFPSCounter);
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
    onClosing: {
        if (mainGUI.mainContent.h4xScreen.visible)
        {
            mainGUI.mainContent.h4xScreen.visible = false;
            mainGUI.mainContent.h4xScreen.cursorLoseFocus();
            close.accepted = false;
        }
        else
        {
            if (mainGUI.mainContent.settings.state == "")
            {
                if (!mainGUI.mainContent.settings.reactToBackOnToolbar())
                    mainGUI.mainContent.settings.state = "hidden";
                close.accepted = false;
            }
            else if (mainGUI.mainContent.reportsList.state == "")
            {
                if (!mainGUI.mainContent.reportsList.reactToBackOnToolbar())
                    mainGUI.mainContent.reportsList.state = "hidden";
                close.accepted = false;
            }
            else if (currentMode == 0)
            {
                if (mainGUI.mainContent.missionsGUI.reactToBackOnToolbar())
                    close.accepted = false;
                else
                {
                    GameApi.saveBase();
                }
            }
            else if (currentMode == 1)
            {
                if (mainGUI.mainContent.buildingsGUI.reactToBackOnToolbar())
                    close.accepted = false;
                else
                {
                    GameApi.saveBase();
                }
            }
            else if (currentMode == 2)
            {
                if (mainGUI.mainContent.mercenariesGUI.reactToBackOnToolbar())
                    close.accepted = false;
                else
                {
                    GameApi.saveBase();
                }
            }
        }
    }
}
