import QtQuick 2.5

import "qrc:/qml/BuildingsMode/BuildingsMenus/DockingStationSubmenus/HeroesListScripts.js" as Scripts
import "../../.."
import "../.."
import Game 1.0

Item {
    id: rootHeroesList

    function update()
    {
        Scripts.setupList(Math.round((271/1080)*width), GameApi.base.dockingStation.readyRecruitsAmount(), width, height);
        for (var i=0;i<GameApi.base.dockingStation.readyRecruitsAmount();++i)
        {
            GameApi.base.dockingStation.prepareRecruitForQML(i);
            Scripts.createItem(GameApi.base.dockingStation.recruitPreparedForQML.name(), GameApi.base.dockingStation.recruitPreparedForQML.name(), GameApi.base.dockingStation.recruitPreparedForQML.professionString(), GameApi.base.dockingStation.recruitPreparedForQML.combatEffectiveness(), GameApi.base.dockingStation.recruitPreparedForQML.proficiency(), GameApi.base.dockingStation.recruitPreparedForQML.cleverness(),  GameApi.base.dockingStation.recruitPreparedForQML.health(), GameApi.base.dockingStation.recruitPreparedForQML.healthLimit(), GameApi.base.dockingStation.recruitPreparedForQML.stress(), GameApi.base.dockingStation.recruitPreparedForQML.stressLimit(), GameApi.base.dockingStation.recruitPreparedForQML.stressResistance(), GameApi.base.dockingStation.recruitPreparedForQML.salary(), GameApi.base.dockingStation.recruitPreparedForQML.dailyFoodConsumption(), GameApi.base.dockingStation.recruitPreparedForQML.baseCombatEffectiveness(), GameApi.base.dockingStation.recruitPreparedForQML.baseProficiency(), GameApi.base.dockingStation.recruitPreparedForQML.baseCleverness(), GameApi.base.dockingStation.recruitPreparedForQML.baseHealthLimit(), GameApi.base.dockingStation.recruitPreparedForQML.baseStressLimit(), GameApi.base.dockingStation.recruitPreparedForQML.baseStressResistance(), GameApi.base.dockingStation.recruitPreparedForQML.baseSalary(), GameApi.base.dockingStation.recruitPreparedForQML.baseDailyFoodConsumption());
        }
    }

    function returnToDefault()
    {
        Scripts.scrollList(3000);
    }

    function deleteObjects()
    {
        Scripts.clearList();
    }

    property int startY

    clip: true

    signal heroClicked(string heroName)

    Image {
        id: additionalBackground

        anchors.fill: parent

        source: "qrc:/graphics/GUI/Background.png"
    }

    MouseArea {
        id: mouseArea

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

        x: 0
        y: 0
        width: parent.width
        height: parent.height

        onPressed: {
            y0 = mouseY;
            movementCheckTimer.start();
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else
            {
                var hN = Scripts.getClickedItemName(mouseX,y0);
                if (hN != "")
                    heroClicked(hN);
            }
            y0 = -1;
            movementCheckTimer.stop();
        }

        Timer {
            id: movementCheckTimer

            interval: 16
            repeat: true
            running: false

            onTriggered: {
                if (mouseArea.isScrollingActive == true)
                {
                    Scripts.scrollList(Math.ceil(mouseArea.mouseY) - mouseArea.y0);

                    mouseArea.y0 = Math.ceil(mouseArea.mouseY);
                }
                else
                {
                    if (Math.abs(mouseArea.mouseY - mouseArea.y0) >= Globals.windowHeight * mouseArea.yChangedThresholdForScrolling / 100)
                    {
                        mouseArea.isScrollingActive = true;
                        Scripts.scrollList(mouseArea.mouseY - mouseArea.y0);
                        mouseArea.y0 = mouseArea.mouseY;
                    }
                }
            }
        }
    }
}
