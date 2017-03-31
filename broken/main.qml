import QtQuick 2.7
import QtQuick.Window 2.2

import Game 1.0
import "."

Item {
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

    anchors.fill: parent

    MainGUI {
        id: mainGUI

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
            Globals.appGUIReady = true;//this is only for first gui loading,but it's inexpensive so it can stay
        }

        transform: [
            Scale {
                id: objectScale

                xScale: win.width/mainGUI.width
                yScale: win.height/mainGUI.height
            },
            Translate {
                x: (win.width-mainGUI.width*objectScale.xScale)/2
                y: (win.height-mainGUI.height*objectScale.yScale)/2
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

    Component.onCompleted: {
        Globals.windowWidth = width;
        Globals.windowHeight = height;
        Globals.dpcm = Screen.pixelDensity*10;
        changeMode(0);
        GameApi.loadExistingBase("E:/Programowanie/gamesave.dat",":/data/");
    }

    function emulatorOfOnClosing()
    {
        GameApi.saveBase("E:/Programowanie/gamesave.dat");
    }
}
