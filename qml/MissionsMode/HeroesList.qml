import QtQuick 2.5

import "qrc:/qml/MissionsMode/HeroesListScripts.js" as Scripts
import "../.."
import ".."
import Game 1.0

Item {
    id: rootHeroesList

    function update()
    {
        var amount=GameApi.base.heroes.amountOfHeroes()+1;
        for (var i=0;i<GameApi.base.heroes.amountOfHeroes();++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);

            if (GameApi.base.heroes.preparedHero.currentActivityString() != "Idle")
                --amount;
        }
        Scripts.setupList(Math.round((271/1080)*width), amount, width, height);
        Scripts.createItem("","","",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        for (var i=0;i<GameApi.base.heroes.amountOfHeroes();++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);

            if (GameApi.base.heroes.preparedHero.currentActivityString() != "Idle")
                continue;
            Scripts.createItem(GameApi.base.heroes.preparedHero.name(), GameApi.base.heroes.preparedHero.name(), GameApi.base.heroes.preparedHero.professionString(), GameApi.base.heroes.preparedHero.combatEffectiveness(), GameApi.base.heroes.preparedHero.proficiency(), GameApi.base.heroes.preparedHero.cleverness(),  GameApi.base.heroes.preparedHero.health(), GameApi.base.heroes.preparedHero.healthLimit(), GameApi.base.heroes.preparedHero.stress(), GameApi.base.heroes.preparedHero.stressLimit(), GameApi.base.heroes.preparedHero.stressResistance(), GameApi.base.heroes.preparedHero.salary(), GameApi.base.heroes.preparedHero.dailyFoodConsumption(), GameApi.base.heroes.preparedHero.baseCombatEffectiveness(), GameApi.base.heroes.preparedHero.baseProficiency(), GameApi.base.heroes.preparedHero.baseCleverness(), GameApi.base.heroes.preparedHero.baseHealthLimit(), GameApi.base.heroes.preparedHero.baseStressLimit(), GameApi.base.heroes.preparedHero.baseStressResistance(), GameApi.base.heroes.preparedHero.baseSalary(), GameApi.base.heroes.preparedHero.baseDailyFoodConsumption());
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

    signal heroClicked(string heroName, string artSource)

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
                var hN = Scripts.getClickedItemName(y0);
                if (hN != "nothing")
                    heroClicked(hN, Scripts.getClickedItemArt(y0));
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
