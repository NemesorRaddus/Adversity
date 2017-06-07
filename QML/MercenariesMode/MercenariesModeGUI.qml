import QtQuick 2.0

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 1464

    width: 1080
    height: 1464

    clip: false

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

    signal updateRequestedFromMercenariesModeGUI()

    function returnToDefault()
    {
        list.state = "";
//        menu.state = "hidden";
        list.returnToDefault();
//        menu.returnToDefault();
    }

    function updateEverything()
    {
        list.updateEverything();
//        menu.updateEverything();
        heroesAmountItem.update();
    }

    function reactToBackOnToolbar()//returns true if intervention was successful and nothing else is needed to be done
    {
//        if (menu.state == "")
//        {
//            if (!menu.reactToBackOnToolbar())
//            {
//                list.state = "";
//                menu.state = "hidden";
//            }
//            return true;
//        }
//        else
//        {
            return false;
//        }
    }

    Item {
        id: heroesAmountItem

        x: 0
        y: 0
        width: parent.theoreticalWidth
        height: heroesAmountTaskBorder.y + heroesAmountTaskBorder.height + 4

        function update()
        {
            heroesAmountAmount.text = GameApi.base.heroes.amountOfHeroes() + '/' + GameApi.base.heroes.amountOfSlots();
        }

        Text {
            id: heroesAmountText

            x: 240
            y: -6

            text: "Mercenaries:"
            color: "#94ef94"
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: heroesAmountAmount

            x: 740
            y: heroesAmountText.y

            color: "#94ef94"
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Image {
            id: heroesAmountTaskBorder

            x: 17
            y: 68
            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    HeroesList {
        id: list

        x: 0
        y: heroesAmountItem.height
        width: root.theoreticalWidth
        height: root.theoreticalHeight - heroesAmountItem.height

        onHeroClicked: {
//            if (buildingName == "Central Unit")
//                menu.changeToCentralUnit();
//            else if (buildingName == "Hospital")
//                menu.changeToHospital();
//            else if (buildingName == "Training Ground")
//                menu.changeToTrainingGround();
//            else if (buildingName == "Gym")
//                menu.changeToGym();
//            else if (buildingName == "Laboratory")
//                menu.changeToLaboratory();
//            else if (buildingName == "Playing Field")
//                menu.changeToPlayingField();
//            else if (buildingName == "Bar")
//                menu.changeToBar();
//            else if (buildingName == "Shrine")
//                menu.changeToShrine();
//            else if (buildingName == "Seclusion")
//                menu.changeToSeclusion();
//            else if (buildingName == "Powerplant")
//                menu.changeToPowerplant();
//            else if (buildingName == "Factory")
//                menu.changeToFactory();
//            else if (buildingName == "Cool Room")
//                menu.changeToCoolRoom();
//            else if (buildingName == "Storage Room")
//                menu.changeToStorageRoom();
//            else if (buildingName == "Aetherite Silo")
//                menu.changeToAetheriteSilo();
//            else if (buildingName == "Barracks")
//                menu.changeToBarracks();
//            else if (buildingName == "Docking Station")
//                menu.changeToDockingStation();

//            state = "hidden";
//            menu.state = "";
        }
    }

//    BuildingMenu {
//        id: menu

//        x: 0
//        y: 0
//        width: root.width
//        height: root.height

//        onBackClickedFwd: {
//            list.state = "";
//            state = "hidden";
//        }

//        onUpdateRequestedFromBuildingMenu: {
//            updateRequestedFromBuildingsModeGUI();
//        }
//        onMarkAsUpgradedSignal: list.markAsUpgraded(buildingName,true);

//        Component.onCompleted: state = "hidden";
//    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        },
        State {
            name: "hiddenRight2"
            PropertyChanges { target: root; x: width * 2 }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}
