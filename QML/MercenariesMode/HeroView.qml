import QtQuick 2.5

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    property string heroName
    property string currentActivity_

    signal backClicked()
    signal upgradeRequested()
    signal buildingMenuRequested(string buildingName)

    function setMercenary(name)
    {
        if (name != "" && name != undefined)
        {
            for (var i=0;i<GameApi.base.heroes.amountOfHeroes();++i)
            {
                GameApi.base.heroes.prepareHeroAt(i);
                if (GameApi.base.heroes.preparedHero.name() == name)
                {
                    heroName=name;
                    topBar.setArtSource("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.heroes.preparedHero.professionString())+'/'+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.heroes.preparedHero.name())+".png");
                    topBar.setName(GameApi.base.heroes.preparedHero.name());
                    topBar.setProfession(GameApi.base.heroes.preparedHero.professionString());
                    topBar.setCE(GameApi.base.heroes.preparedHero.combatEffectiveness());
                    topBar.setPR(GameApi.base.heroes.preparedHero.proficiency());
                    topBar.setCL(GameApi.base.heroes.preparedHero.cleverness());
                    topBar.setHP(GameApi.base.heroes.preparedHero.health(), GameApi.base.heroes.preparedHero.healthLimit());
                    topBar.setST(GameApi.base.heroes.preparedHero.stress());
                    topBar.setSR(GameApi.base.heroes.preparedHero.stressResistance());
                    topBar.setSL(GameApi.base.heroes.preparedHero.stressLimit());
                    topBar.setSA(GameApi.base.heroes.preparedHero.salary());
                    topBar.setFC(GameApi.base.heroes.preparedHero.dailyFoodConsumption());
                    currentActivity_=GameApi.base.heroes.preparedHero.currentActivityString();
                    topBar.setCurrentActivity(currentActivity_);
                    currentActivity.setCurrentActivity(currentActivity_);
                    break;
                }
            }
        }
    }

    function updateEverything()
    {
        setMercenary(heroName);
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    function returnToDefault()
    {

    }

    width: 1080
    height: 1464

    transform: [
        Scale {
            id: someScale

            xScale: width/theoreticalWidth
            yScale: height/theoreticalHeight
        },
        Translate {
            x: (width-theoreticalWidth*someScale.xScale)/2
            y: (height-theoreticalHeight*someScale.yScale)/2
        }
    ]

    HeroesListDelegate {
        id: topBar

        x: 0
        y: 0
        width: 1080
        height: 271
    }

    Item {
        id: currentActivity

        x: 0
        y: topBar.height
        width: 1080
        height: currentActivityTaskBorder.y + currentActivityTaskBorder.height

        function setCurrentActivity(ca)
        {
            currentActivityValue.text = ca;

            if (ca == "Idle")
            {
                currentActivityDescription.text = "This mercenary is awaiting orders in the barracks.";
                currentActivityGoToText.visible = false;
                currentActivityGoToMA.visible = false;
            }
            else if (ca == "On Mission")
            {
                currentActivityDescription.text = "Mission name and amount of remaining days go here";//TODO mission
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Hospital")
            {
                currentActivityDescription.text = "The mercenary is being healed. Days to full recovery: "+GameApi.base.hospital.daysToFullRecovery(GameApi.globalsCpp.alterNormalTextToInternal(heroName));
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "On Training Ground")
            {
                currentActivityDescription.text = "Useful text";//TODO
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Gym")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Laboratory")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Playing Field")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Bar")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Shrine")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Seclusion")
            {
                currentActivityDescription.text = "Useful text";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "Arriving")
            {
                currentActivityDescription.text = "The mercenary is on his/her way to our base.\nETA: "+GameApi.base.dockingStation.remainingDaysUntilHeroArrival(GameApi.globalsCpp.alterNormalTextToInternal(heroName));
                currentActivityGoToText.visible = false;
                currentActivityGoToMA.visible = false;
            }
        }

        Text {
            id: currentActivityText

            x: 17
            y: 5
            width: 420
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Current Activity:"
            font.pixelSize: 52
            font.family: fontStencil.name
        }

        Text {
            id: currentActivityValue

            x: currentActivityText.x + currentActivityText.width
            y: currentActivityText.y
            width: 1060-x
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "On Training Ground"
            font.pixelSize: 52
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignRight
        }

        Text {
            id: currentActivityDescription

            x: currentActivityText.x
            y: currentActivityText.y + currentActivityText.height + 10
            width: currentActivityGoToText.x - x - 10
            height: (font.pixelSize+4)*3

            color: "#94ef94"
            text: "This mercenary is awaiting orders in the barracks"
            wrapMode: Text.WordWrap
            maximumLineCount: 3
            font.pixelSize: 35
            font.family: fontStencil.name
        }

        Text {
            id: currentActivityGoToText

            x: 900
            y: currentActivityDescription.y + 10
            width: 150
            height: (font.pixelSize+4)*3

            color: "#94ef94"
            text: "Go to"
            font.pixelSize: 65
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: currentActivityGoToMA

            anchors.fill: currentActivityGoToText

            onClicked: {
                if (currentActivity_ == "On Mission")
                    ;//TODO mission
                else if (currentActivity_ == "In Hospital")
                    buildingMenuRequested("Hospital");
                else if (currentActivity_ == "On Training Ground")
                    buildingMenuRequested("Training Ground");
                else if (currentActivity_ == "In Gym")
                    buildingMenuRequested("Gym");
                else if (currentActivity_ == "In Laboratory")
                    buildingMenuRequested("Laboratory");
                else if (currentActivity_ == "In Playing Field")
                    buildingMenuRequested("Playing Field");
                else if (currentActivity_ == "In Bar")
                    buildingMenuRequested("Bar");
                else if (currentActivity_ == "In Shrine")
                    buildingMenuRequested("Shrine");
                else if (currentActivity_ == "In Seclusion")
                    buildingMenuRequested("Seclusion");
            }
        }

        Image {
            id: currentActivityTaskBorder

            x: 17
            y: currentActivityDescription.y + currentActivityDescription.height + 8
            width: 1048
            height: 3
            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Item {
        id: stressBorderEffect

        x: 0
        y: currentActivity.y + currentActivity.height
        width: 1080
        height: stressBorderEffectTaskBorder.y + stressBorderEffect.height + 4

        Text {
            //id:
        }

        Image {
            id: stressBorderEffectTaskBorder

            x: 17

            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Item {
        id: back

        x: 400
        y: 1344
        width: 260
        height: 120

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            anchors.fill: parent

            onClicked: backClicked()
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
