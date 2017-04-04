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
        if (mode == 0)
        {
            currentMode = 0;
            mainGUI.buildingsGUI.returnToDefault();
            mainGUI.buildingsGUI.state = "hiddenRight";
        }
        else if (mode == 1)
        {
            currentMode = 1;
            mainGUI.buildingsGUI.returnToDefault();
            mainGUI.buildingsGUI.state = "";
        }
        else if (mode == 2)
        {
            currentMode = 2;
            mainGUI.buildingsGUI.returnToDefault();
            mainGUI.buildingsGUI.state = "hiddenLeft";
        }
    }

    visible: true
    width: 450
    height: 800
    title: "Game"

    onWidthChanged: Globals.windowWidth = width;
    onHeightChanged: Globals.windowHeight = height;

    MainGUI {
        id: mainGUI

        visible: false

        function updateResources()
        {
            energyValue.text = GameApi.base.currentEnergyAmount() + '/' + GameApi.base.powerplant.energyLimit();
            foodSuppliesValue.text = GameApi.base.currentFoodSuppliesAmount() + '/' + GameApi.base.coolRoom.foodSuppliesLimit();
            buildingMaterialsValue.text = GameApi.base.currentBuildingMaterialsAmount() + '/' + GameApi.base.storageRoom.buildingMaterialsLimit();
            aetheriteValue.text = GameApi.base.currentAetheriteAmount() + '/' + GameApi.base.aetheriteSilo.aetheriteLimit();

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
            mainGUI.buildingsGUI.updateEverything();//TODO more
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
    }

    Timer {
        id: gameTimer

        interval: 2500 // 1000/48*60
        running: true
        repeat: true
        onTriggered: {
            GameApi.base.gameClock.updateClock(1);
            mainGUI.updateClock();
            if (updateEverythingInAMoment)
            {
                mainGUI.updateEverything();
                updateEverythingInAMoment=false;
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

        minDurationInMs: 2500
        splashDisappearAnimationDuration: 500
        canCloseRefreshingRateInMs: 100
        canClose: false
        splashImageSource: "qrc:/graphics/splash.png"

        onShowing: mainGUI.visible = false;
        onHiding: mainGUI.visible = true;
    }

    Component.onCompleted: {
        splash.show();
        Globals.windowWidth = width;
        Globals.windowHeight = height;
        changeMode(0);
        GameApi.loadExistingBase(":/data/");
    }
    onClosing: {
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
            GameApi.saveBase();
        }
    }
}
