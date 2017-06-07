import QtQuick 2.5

import "qrc:/qml/BuildingsMode/BuildingsMenus/DockingStationSubmenus/HeroesListScripts.js" as Scripts
import "../../.."
import "../.."
import Game 1.0

Item {
    id: rootHeroesList

    function update()
    {
        Scripts.setupList(Math.round((271/1080)*width), GameApi.base.dockingStation.recruitsAmount(), width, height);
        for (var i=0;i<GameApi.base.dockingStation.recruitsAmount();++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);
            Scripts.createItem(GameApi.base.heroes.recruitPreparedForQML.name(), GameApi.base.heroes.recruitPreparedForQML.name(), GameApi.base.heroes.recruitPreparedForQML.professionString(), GameApi.base.heroes.recruitPreparedForQML.combatEffectiveness(), GameApi.base.heroes.recruitPreparedForQML.proficiency(), GameApi.base.heroes.recruitPreparedForQML.cleverness(),  GameApi.base.heroes.recruitPreparedForQML.health(), GameApi.base.heroes.recruitPreparedForQML.healthLimit(), GameApi.base.heroes.recruitPreparedForQML.stress(), GameApi.base.heroes.recruitPreparedForQML.stressLimit(), GameApi.base.heroes.recruitPreparedForQML.stressResistance(), GameApi.base.heroes.recruitPreparedForQML.salary(), GameApi.base.heroes.recruitPreparedForQML.dailyFoodConsumption());
        }
    }

    function returnToDefault()
    {
        Scripts.scrollList(1000);
        for (var i=0;i<10;++i)
            Scripts.scrollList(100);
        for (i=0;i<10;++i)
            Scripts.scrollList(10);
        for (i=0;i<10;++i)
            Scripts.scrollList(1);
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
        height: parent.height - taskBorder.height

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
                        if (mouseArea.y0 > mouseArea.mouseY)
                        {
                            Scripts.scrollList(1);
                        }
                        else
                        {
                            Scripts.scrollList(-1);
                        }
                        mouseArea.y0 = mouseArea.mouseY;
                    }
                }
            }
        }
    }
}
