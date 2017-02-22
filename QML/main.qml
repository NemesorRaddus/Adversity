import QtQuick 2.7
import QtQuick.Window 2.2

import Game 1.0
import "."

Window {
    id: win

    property int currentMode: 0

    function changeMode(mode)
    {
        if (mode == 0)
        {
            currentMode = 0;
            mainGUI.buildingsList.state = "hiddenRight"
        }
        else if (mode == 1)
        {
            currentMode = 1;
            mainGUI.buildingsList.state = "";
        }
        else if (mode == 2)
        {
            currentMode = 2;
            mainGUI.buildingsList.state = "hiddenLeft";
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

        function updateEverything()
        {
            energyValue.text = GameApi.base.currentEnergyAmount() + '/' + GameApi.base.powerPlant.energyLimit();
            foodSuppliesValue.text = GameApi.base.currentFoodSuppliesAmount() + '/' + GameApi.base.coolRoom.foodSuppliesLimit();
            buildingMaterialsValue.text = GameApi.base.currentBuildingMaterialsAmount() + '/' + GameApi.base.storageRoom.buildingMaterialsLimit();
            aetheriteValue.text = GameApi.base.currentAetheriteAmount() + '/' + GameApi.base.aetheriteSilo.aetheriteLimit();

            energyValue2.text = GameApi.base.currentEnergyIncome() + '/' + "day";
            foodSuppliesValue2.text = GameApi.base.currentFoodSuppliesIncome() + '/' + "day";
            buildingMaterialsValue2.text = GameApi.base.currentBuildingMaterialsIncome() + '/' + "day";
            aetheriteValue2.text = GameApi.base.currentAetheriteIncome() + '/' + "day";

            dayValue.text = "Day " + GameApi.base.gameClock.currentDay();

            hourValue.text = (GameApi.base.gameClock.currentHour() < 10 ?
                                  '0' + GameApi.base.gameClock.currentHour() :
                                  GameApi.base.gameClock.currentHour())
                    + ':' +
                    (GameApi.base.gameClock.currentMin() < 10 ?
                         '0' + GameApi.base.gameClock.currentMin() :
                         GameApi.base.gameClock.currentMin());
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
    }

    Timer {
        id: gameTimer

        interval: 1250 // 1000/48*60
        running: true
        repeat: true
        onTriggered: {
            GameApi.base.gameClock.updateClock(1);
            mainGUI.updateClock();
            if (GameApi.base.gameClock.hasDayChangedLately())
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
        mainGUI.updateEverything();
    }
}
