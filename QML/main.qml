import QtQuick 2.9
import QtQuick.Window 2.3

import Game 1.0
import "."

Window {
    id: win

    property int currentMode: 0

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

    function showReportNotification()
    {
        mainGUI.mainContent.reportsNotification.setAmount(GameApi.base.reports.amountOfNewReports());
        mainGUI.mainContent.reportsNotification.show();
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
            mainContent.energyValue.text = GameApi.base.resources.currentEnergyAmount() + '/' + GameApi.base.buildings.powerplant.energyLimit();
            if (GameApi.base.resources.currentEnergyAmount() === 0)
                mainContent.energyValue.color = "#b30000";
            else if (GameApi.base.resources.currentEnergyAmount() === GameApi.base.buildings.powerplant.energyLimit())
                mainContent.energyValue.color = "#ffd480";
            else
                mainContent.energyValue.color = "#c0efc0";

            mainContent.foodSuppliesValue.text = GameApi.base.resources.currentFoodSuppliesAmount() + '/' + GameApi.base.buildings.coolRoom.foodSuppliesLimit();
            if (GameApi.base.resources.currentFoodSuppliesAmount() === 0)
                mainContent.foodSuppliesValue.color = "#b30000";
            else if (GameApi.base.resources.currentFoodSuppliesAmount() === GameApi.base.buildings.coolRoom.foodSuppliesLimit())
                mainContent.foodSuppliesValue.color = "#ffd480";
            else
                mainContent.foodSuppliesValue.color = "#c0efc0";

            mainContent.buildingMaterialsValue.text = GameApi.base.resources.currentBuildingMaterialsAmount() + '/' + GameApi.base.buildings.storageRoom.buildingMaterialsLimit();
            if (GameApi.base.resources.currentBuildingMaterialsAmount() === 0)
                mainContent.buildingMaterialsValue.color = "#b30000";
            else if (GameApi.base.resources.currentBuildingMaterialsAmount() === GameApi.base.buildings.storageRoom.buildingMaterialsLimit())
                mainContent.buildingMaterialsValue.color = "#ffd480";
            else
                mainContent.buildingMaterialsValue.color = "#c0efc0";

            mainContent.aetheriteValue.text = GameApi.base.resources.currentAetheriteAmount() + '/' + GameApi.base.buildings.aetheriteSilo.aetheriteLimit();
            if (GameApi.base.resources.currentAetheriteAmount() === 0)
                mainContent.aetheriteValue.color = "#b30000";
            else if (GameApi.base.resources.currentAetheriteAmount() === GameApi.base.buildings.aetheriteSilo.aetheriteLimit())
                mainContent.aetheriteValue.color = "#ffd480";
            else
                mainContent.aetheriteValue.color = "#c0efc0";

            mainContent.energyValue2.text = GameApi.base.resources.currentEnergyIncome() + '/' + "day";
            mainContent.foodSuppliesValue2.text = GameApi.base.resources.currentFoodSuppliesIncome() + '/' + "day";
            mainContent.buildingMaterialsValue2.text = GameApi.base.resources.currentBuildingMaterialsIncome() + '/' + "day";
            mainContent.aetheriteValue2.text = GameApi.base.resources.currentAetheriteIncome() + '/' + "day";
        }

        function updateClock()
        {
            mainContent.dayValue.text = "Day " + GameApi.base.gameClock.currentDay();

            mainContent.hourValue.text = (GameApi.base.gameClock.currentHour() < 10 ?
                                  '0' + GameApi.base.gameClock.currentHour() :
                                  GameApi.base.gameClock.currentHour())
                    + ':' +
                    (GameApi.base.gameClock.currentMin() < 10 ?
                         '0' + GameApi.base.gameClock.currentMin() :
                         GameApi.base.gameClock.currentMin());
        }

        function updateMainContent()
        {
            mainGUI.mainContent.buildingsGUI.updateEverything();
            mainGUI.mainContent.mercenariesGUI.updateEverything();
            mainGUI.mainContent.missionsGUI.updateEverything();
        }

        function updateEverything()
        {
            updateResources();
            updateClock();
            updateMainContent();
            mainContent.reportsList.updateEverything();
            mainContent.settings.update();
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

        mainContent.missionsButton.onClicked: changeMode(0);
        mainContent.baseButton.onClicked: changeMode(1);
        mainContent.mercenariesButton.onClicked: changeMode(2);

        mainContent.buildingsGUI.onUpdateRequestedFromBuildingsModeGUI: updateEverything();
        mainContent.mercenariesGUI.onUpdateRequestedFromMercenariesModeGUI: updateEverything();

        mainContent.buildingsGUI.onMercenariesModeUpdateRequested: mainContent.mercenariesGUI.updateEverything();
        mainContent.missionsGUI.onMercenariesModeUpdateRequested: mainContent.mercenariesGUI.updateEverything();

        mainContent.missionsGUI.onResourcesUpdateRequested: updateResources();

        mainContent.buildingsGUI.onShowSpecial: mainContent.h4xScreen.visible = true;
        mainContent.h4xScreen.onHiding: mainContent.buildingsGUI.acknowledgeConsoleHiding();

        mainContent.mercenariesGUI.onBuildingMenuRequested: {
            changeMode(1);
            mainContent.buildingsGUI.changeBuilding(buildingName);
        }

        mainContent.mercenariesGUI.onDismissClickedFwd: mainContent.mercenaryDismissConfirmDialog.show()
        mainContent.mercenariesGUI.onDismissDialogHidingRequested: mainContent.mercenaryDismissConfirmDialog.hide()
        mainContent.mercenaryDismissConfirmDialog.onAccepted: mainContent.mercenariesGUI.dismissMercenaryFwd()
        mainContent.mercenaryDismissConfirmDialog.onDeclined: mainContent.mercenariesGUI.acknowledgeConfirmDialogClosing()
        mainContent.mercenariesGUI.onUnbanRequested: mainContent.buildingsGUI.requestUnban(mercenaryName, buildingName)

        mainContent.mercenariesGUI.onArtPreviewRequested: mainContent.mercenaryArtPreview.show(artSource)
        mainContent.mercenariesGUI.onArtPreviewHidingRequested: mainContent.mercenaryArtPreview.hide()
        mainContent.mercenaryArtPreview.onClosing: mainContent.mercenariesGUI.acknowledgeArtPreviewClosing()

        mainContent.settingsButton.onClicked: mainContent.settings.show();
        mainContent.settings.onBackClicked: mainContent.settings.hide();

        onEnableFPSCounterChanged: mainContent.settings.acknowledgeFPSToggle(enableFPSCounter);

        mainContent.reportsNotification.onClicked: {
            mainContent.reportsList.updateEverything();
            mainContent.reportsList.state = "";
        }
        mainContent.reportsOpener.onClicked: {
            mainContent.reportsList.updateEverything();
            mainContent.reportsList.state = "";
        }
        mainContent.reportsList.onBackClicked: {
            mainContent.reportsList.state = "hidden";
        }
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
            {
                mainGUI.updateEverything();
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
//        GameApi.savesManager.loadSave("A",""); // doesn't create new saves, needs to be soon replaced
//        changeMode(1);
//        splash.canClose = true;
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
