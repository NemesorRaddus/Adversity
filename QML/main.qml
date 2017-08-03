import QtQuick 2.7
import QtQuick.Window 2.2

import Game 1.0
import "."

Window {
    id: win

    property int currentMode: 0
    property bool updateEverythingInAMoment: true

    function changeMode(mode)
    {
        if (currentMode == 0)
        {

        }
        else if (currentMode == 1)
        {
            mainGUI.buildingsGUI.returnToDefault();
        }
        else if (currentMode == 2)
        {
            mainGUI.mercenariesGUI.returnToDefault();
        }

        currentMode = mode;

        if (mode == 0)
        {
            mainGUI.buildingsGUI.state = "hiddenRight";
            mainGUI.mercenariesGUI.state = "hiddenRight2";
        }
        else if (mode == 1)
        {
            mainGUI.buildingsGUI.state = "";
            mainGUI.mercenariesGUI.state = "hiddenRight";
        }
        else if (mode == 2)
        {
            mainGUI.buildingsGUI.state = "hiddenLeft";
            mainGUI.mercenariesGUI.state = "";
        }
    }

    function updateEveryting()
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

        function updateResources()
        {
            energyValue.text = GameApi.base.currentEnergyAmount() + '/' + GameApi.base.powerplant.energyLimit();
            if (GameApi.base.currentEnergyAmount() === 0)
            {
                energyValue.color = "#b30000";
            }
            else if (GameApi.base.currentEnergyAmount() === GameApi.base.powerplant.energyLimit())
            {
                energyValue.color = "#ffd480";
            }
            else
            {
                energyValue.color = "#c0efc0";
            }

            foodSuppliesValue.text = GameApi.base.currentFoodSuppliesAmount() + '/' + GameApi.base.coolRoom.foodSuppliesLimit();
            if (GameApi.base.currentFoodSuppliesAmount() === 0)
            {
                foodSuppliesValue.color = "#b30000";
            }
            else if (GameApi.base.currentFoodSuppliesAmount() === GameApi.base.coolRoom.foodSuppliesLimit())
            {
                foodSuppliesValue.color = "#ffd480";
            }
            else
            {
                foodSuppliesValue.color = "#c0efc0";
            }

            buildingMaterialsValue.text = GameApi.base.currentBuildingMaterialsAmount() + '/' + GameApi.base.storageRoom.buildingMaterialsLimit();
            if (GameApi.base.currentBuildingMaterialsAmount() === 0)
            {
                buildingMaterialsValue.color = "#b30000";
            }
            else if (GameApi.base.currentBuildingMaterialsAmount() === GameApi.base.storageRoom.buildingMaterialsLimit())
            {
                buildingMaterialsValue.color = "#ffd480";
            }
            else
            {
                buildingMaterialsValue.color = "#c0efc0";
            }

            aetheriteValue.text = GameApi.base.currentAetheriteAmount() + '/' + GameApi.base.aetheriteSilo.aetheriteLimit();
            if (GameApi.base.currentAetheriteAmount() === 0)
            {
                aetheriteValue.color = "#b30000";
            }
            else if (GameApi.base.currentAetheriteAmount() === GameApi.base.aetheriteSilo.aetheriteLimit())
            {
                aetheriteValue.color = "#ffd480";
            }
            else
            {
                aetheriteValue.color = "#c0efc0";
            }

            energyValue2.text = GameApi.base.currentEnergyIncome() + '/' + "day";
            foodSuppliesValue2.text = GameApi.base.currentFoodSuppliesIncome() + '/' + "day";
            buildingMaterialsValue2.text = GameApi.base.currentBuildingMaterialsIncome() + '/' + "day";
            aetheriteValue2.text = GameApi.base.currentAetheriteIncome() + '/' + "day";
        }

        function updateClock()
        {
            dayValue.text = "Day " + GameApi.base.gameClock.currentDay();

            hourValue.text = (GameApi.base.gameClock.currentHour() < 10 ?
                                  '0' + GameApi.base.gameClock.currentHour() :
                                  GameApi.base.gameClock.currentHour())
                    + ':' +
                    (GameApi.base.gameClock.currentMin() < 10 ?
                         '0' + GameApi.base.gameClock.currentMin() :
                         GameApi.base.gameClock.currentMin());
        }

        function updateMainContent()
        {
            mainGUI.buildingsGUI.updateEverything();
            mainGUI.mercenariesGUI.updateEverything();//TODO more
        }

        function updateEverything()
        {
            updateResources();
            updateClock();
            updateMainContent();
            splash.canClose = true;//only for first gui loading,but it's inexpensive so it can stay
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

        missionsButton.onClicked: changeMode(0);
        baseButton.onClicked: changeMode(1);
        heroesButton.onClicked: changeMode(2);

        buildingsGUI.onUpdateRequestedFromBuildingsModeGUI: updateEverything();
        mercenariesGUI.onUpdateRequestedFromMercenariesModeGUI: updateEverything();

        buildingsGUI.onShowSpecial: h4xScreen.visible = true;

        mercenariesGUI.onBuildingMenuRequested: {
            changeMode(1);
            buildingsGUI.changeBuilding(buildingName);
        }

        mercenariesGUI.onDismissClickedFwd: mercenaryDismissConfirmDialog.show()
        mercenariesGUI.onDismissDialogHidingRequested: mercenaryDismissConfirmDialog.hide()
        mercenaryDismissConfirmDialog.onAccepted: mercenariesGUI.dismissMercenaryFwd()
        mercenaryDismissConfirmDialog.onDeclined: mercenariesGUI.acknowledgeConfirmDialogClosing()

        mercenariesGUI.onArtPreviewRequested: heroArtPreview.show(artSource)
        mercenariesGUI.onArtPreviewHidingRequested: heroArtPreview.hide()
        heroArtPreview.onClosing: mercenariesGUI.acknowledgeArtPreviewClosing()
    }

    Timer {
        id: gameTimer

        interval: 1250 // 1000/48*60
        running: true
        repeat: true
        onTriggered: {
            GameApi.base.gameClock.updateClock();
            mainGUI.updateClock();
            if (updateEverythingInAMoment)
            {
                mainGUI.updateEverything();
                updateEverythingInAMoment=false;
                console.info("[",Math.floor(GameApi.startupTimerElapsed()/1000),'.',('00' + GameApi.startupTimerElapsed()%1000).substr(-3),"] QML part is ready");
            }
            else if (GameApi.base.gameClock.hasDayChangedLately())
            {
                mainGUI.updateEverything();//TODO more
            }
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
            mainGUI.visible = true;
            console.info("[",Math.floor(GameApi.startupTimerElapsed()/1000),'.',('00' + GameApi.startupTimerElapsed()%1000).substr(-3),"] Splash screen has started hiding");
            console.info("[",Math.floor((GameApi.startupTimerElapsed()+splashDisappearAnimationDuration)/1000),'.',('00' + (GameApi.startupTimerElapsed()+splashDisappearAnimationDuration)%1000).substr(-3),"] Splash screen has hidden");
        }
    }

    Component.onCompleted: {
        splash.show();
        Globals.windowWidth = width;
        Globals.windowHeight = height;
        changeMode(0);
        GameApi.loadExistingBase(":/data/");
        console.info("[",Math.floor(GameApi.startupTimerElapsed()/1000),'.',('00' + GameApi.startupTimerElapsed()%1000).substr(-3),"] Main QML component has been built");
    }
    onClosing: {
        if (mainGUI.h4xScreen.visible)
        {
            mainGUI.h4xScreen.visible = false;
            mainGUI.h4xScreen.cursorLoseFocus();
            close.accepted = false;
        }
        else
        {
            if (currentMode == 0)
            {
                GameApi.saveBase();
            }
            else if (currentMode == 1)
            {
                if (mainGUI.buildingsGUI.reactToBackOnToolbar())
                    close.accepted = false;
                else
                {
                    GameApi.saveBase();
                }
            }
            else if (currentMode == 2)
            {
                if (mainGUI.mercenariesGUI.reactToBackOnToolbar())
                    close.accepted = false;
                else
                {
                    GameApi.saveBase();
                }
            }
        }
    }
}
