import QtQuick 2.5

import "qrc:/qml/BuildingsMode/BuildingsMenus/HeroesList/HeroesListScripts.js" as Scripts
import "../../.."
import "../.."
import Game 1.0

Item {
    id: rootHeroesList

    function updateEverything()
    {
        var heroesAmount=0;
        var availableHeroes = new Array(GameApi.base.heroes.amountOfHeroes());
        for (var i=0;i<GameApi.base.heroes.amountOfHeroes();++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);
            if (GameApi.base.heroes.preparedHero.currentActivityString() == "Idle" && bannedHeroes.indexOf(GameApi.base.heroes.preparedHero.name())==-1)
            {
                ++heroesAmount;
                availableHeroes[i]=true;
            }
        }

        Scripts.setupList(Math.round((271/1080)*width), heroesAmount, width, height);
        var j=0;
        for (i=0;i<GameApi.base.heroes.amountOfHeroes() && j<heroesAmount;++i)
        {
            if (availableHeroes[i] == true)
            {
                GameApi.base.heroes.prepareHeroAt(i);
                Scripts.createItem(GameApi.base.heroes.preparedHero.name(), GameApi.base.heroes.preparedHero.name(), GameApi.base.heroes.preparedHero.professionString(),GameApi.base.heroes.preparedHero.combatEffectiveness(),GameApi.base.heroes.preparedHero.proficiency(),GameApi.base.heroes.preparedHero.cleverness());
                ++j;
            }
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

    property var bannedHeroes: []

    function banHero(name) {
        if (bannedHeroes.indexOf(name)==-1)
            bannedHeroes.push(name);
    }

    function unbanHero(name) {
        if (bannedHeroes.indexOf(name)!=-1)
            bannedHeroes.splice(bannedHeroes.indexOf(name),1);
    }

    property int startY

    clip: true

    signal heroClicked(string heroName, string heroProfession)

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
                heroClicked(Scripts.getClickedItemName(y0), Scripts.getClickedItemName2(y0));
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

    Image {
        id: taskBorder

        x: 0
        y: parent.height - height
        width: parent.width
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: rootHeroesList; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 500 }
    }
}
