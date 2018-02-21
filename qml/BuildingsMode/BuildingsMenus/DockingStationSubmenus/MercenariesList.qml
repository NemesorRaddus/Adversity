import QtQuick 2.9

import "qrc:/qml/BuildingsMode/BuildingsMenus/DockingStationSubmenus/MercenariesListScripts.js" as Scripts
import "../../.."
import "../.."
import Game 1.0

Item {
    id: rootMercenariesList

    function update()
    {
        Scripts.setupList(Math.round((271/1080)*width), GameApi.base.buildings.dockingStation.readyRecruitsAmount(), width, height);
        for (var i=0;i<GameApi.base.buildings.dockingStation.readyRecruitsAmount();++i)
        {
            GameApi.base.buildings.dockingStation.prepareRecruitForQML(i);
            Scripts.createItem(GameApi.base.buildings.dockingStation.recruitPreparedForQML.name(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.name(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.professionString(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.combatEffectiveness(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.proficiency(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.cleverness(),  GameApi.base.buildings.dockingStation.recruitPreparedForQML.health(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.healthLimit(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.stress(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.stressLimit(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.stressResistance(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.salary(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.dailyFoodConsumption(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseCombatEffectiveness(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseProficiency(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseCleverness(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseHealthLimit(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseStressLimit(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseStressResistance(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseSalary(), GameApi.base.buildings.dockingStation.recruitPreparedForQML.baseDailyFoodConsumption());
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

    signal mercenaryClicked(string mercenaryName)

    Rectangle {
        anchors.fill: parent

        color: "#171717"
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
                    mercenaryClicked(hN);
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
