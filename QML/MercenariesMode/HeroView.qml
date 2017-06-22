import QtQuick 2.5

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    property string heroName
    property string currentActivity_
    property bool dismissConfirmDialogVisible: false

    signal backClicked()
    signal upgradeRequested()
    signal buildingMenuRequested(string buildingName)
    signal dismissClicked()
    signal guiUpdateRequested()

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

                    salaryDismissSalaryValue.text = GameApi.base.heroes.preparedHero.salary()+"/Week";
                    salaryDismissFoodConsumptionValue.text = GameApi.base.heroes.preparedHero.dailyFoodConsumption()+"/Day";

                    stressBorderEffect.resetSBEChances();
                    if (GameApi.base.heroes.preparedHero.isImmuneToStress())
                    {
                        stressBorderEffect.setImmunity();
                    }
                    else
                    {
                        for (var j=0; j<GameApi.base.heroes.preparedHero.amountOfDiverseSBEs(); ++j)
                            stressBorderEffect.addSBEChance(GameApi.base.heroes.preparedHero.nameOfSBESummed(j), GameApi.globalsCpp.roundDouble(GameApi.base.heroes.preparedHero.chanceOfSBESummed(j) * 100, 2));
                        if (GameApi.base.heroes.preparedHero.isStressBorderEffectActive())
                            stressBorderEffect.setCurrentSBE(GameApi.base.heroes.preparedHero.currentStressBorderEffectNameString());
                        else
                            stressBorderEffect.setNoCurrentSBE();
                    }
                    break;
                }
            }
        }
    }
    function dismissMercenary()
    {
        dismissConfirmDialogVisible = false;
        GameApi.base.heroes.dismissHero(heroName);
        guiUpdateRequested();
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

//    transform: [
//        Scale {
//            id: someScale

//            xScale: width/theoreticalWidth
//            yScale: height/theoreticalHeight
//        },
//        Translate {
//            x: (width-theoreticalWidth*someScale.xScale)/2
//            y: (height-theoreticalHeight*someScale.yScale)/2
//        }
//    ]

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
            height: font.pixelSize

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
        id: salaryDismiss

        x: 17
        y: currentActivity.y + currentActivity.height
        width: 1048
        height: salaryDismissTaskBorder.y + salaryDismissTaskBorder.height + 4

        Text {
            id: salaryDismissSalaryText

            x: 0
            y: 0
            width: 220
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Salary"
            font.pixelSize: 65
            font.family: fontStencil.name
        }
        Image {
            id: salaryDismissSalaryIcon

            x: 266
            y: 0
            width: height
            height: salaryDismissSalaryText.height

            source: "qrc:/graphics/GUI/Aetherite.png"
        }
        Text {
            id: salaryDismissSalaryValue

            x: 359
            y: salaryDismissSalaryText.y
            width: 250
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "9/week"
            font.pixelSize: 65
            font.family: fontStencil.name
        }

        Text {
            id: salaryDismissFoodConsumptionText

            x: 0
            y: salaryDismissSalaryText.y + salaryDismissSalaryText.height
            width: 220
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Food"
            font.pixelSize: 65
            font.family: fontStencil.name
        }
        Image {
            id: salaryDismissFoodConsumptionIcon

            x: salaryDismissSalaryIcon.x
            y: 69
            width: height
            height: salaryDismissFoodConsumptionText.height

            source: "qrc:/graphics/GUI/Foodsupplies.png"
        }
        Text {
            id: salaryDismissFoodConsumptionValue

            x: salaryDismissSalaryValue.x
            y: salaryDismissFoodConsumptionText.y
            width: 250
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "9/day"
            font.pixelSize: 65
            font.family: fontStencil.name
        }

        Text {
            id: salaryDismissButtonText

            x: 747
            y: 33
            width: 280
            height: font.pixelSize + 4

            color: "#b30000"
            text: "Dismiss"
            font.pixelSize: 75
            font.family: fontStencil.name
        }
        MouseArea {
            id: salaryDismissButtonMA

            anchors.fill: salaryDismissButtonText

            onClicked: {
                dismissConfirmDialogVisible = true;
                dismissClicked();
            }
        }

        Image {
            id: salaryDismissTaskBorder

            x: 0
            y: salaryDismissFoodConsumptionText.y + salaryDismissFoodConsumptionText.height + 4
            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Item {
        id: stressBorderEffect

        x: 17
        y: salaryDismiss.y + salaryDismiss.height
        width: 1048
        height: stressBorderEffectTaskBorder.y + stressBorderEffectTaskBorder.height + 4

        function setNoCurrentSBE()
        {
            stressBorderEffectValue.text = "-";
            stressBorderEffectDescription.text = "This mercenary isn't currently affected by any effect.";
        }

        function setCurrentSBE(sbeName)
        {
            stressBorderEffectValue.text = sbeName;
            stressBorderEffectDescription.text = "{Enter the description here}"
        }

        function setImmunity()
        {
            stressBorderEffectValue.text = "N/A";
            stressBorderEffectDescription.text = "This mercenary is immune to stress. Thus, he/she is never affected by any stress border effect.";
        }

        function addSBEChance(sbeName, percChance)
        {
            stressBorderEffectChances.text = stressBorderEffectChances.text+"\n"+percChance+"% "+sbeName;
        }

        function resetSBEChances()
        {
            stressBorderEffectChances.text = "";
        }

        Text {
            id: stressBorderEffectText

            x: 0
            y: 0
            width: 220
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Effect:"
            font.pixelSize: 65
            font.family: fontStencil.name
        }

        Text {
            id: stressBorderEffectValue

            x: 350
            y: stressBorderEffectText.y
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "N/A"
            font.pixelSize: 65
            font.family: fontStencil.name
        }

        Text {
            id: stressBorderEffectDescription

            x: 0
            y: stressBorderEffectText.y + stressBorderEffectText.height
            width: parent.width - x
            height: (font.pixelSize + 4)*lineCount

            color: "#94ef94"
            text: "This mercenary is immune to stress. Thus, he/she is never affected by any stress border effect."
            wrapMode: Text.WordWrap
            font.pixelSize: 45
            font.family: fontStencil.name
        }

        Text {
            id: stressBorderEffectChances

            x: 0
            y: stressBorderEffectDescription.y + stressBorderEffectDescription.height
            width: parent.width
            height: (font.pixelSize+8)*lineCount

            color: "#94ef94"
            text: "50% None\n30% Paranoia\n20% Bravery"
            wrapMode: Text.WordWrap
            font.pixelSize: 45
            font.family: fontStencil.name
        }

        Image {
            id: stressBorderEffectTaskBorder

            x: 0
            y: stressBorderEffectChances.y + stressBorderEffectChances.height
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
