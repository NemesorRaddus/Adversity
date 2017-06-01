import QtQuick 2.0

Item {
    id: root

    clip: true

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

    HeroesList {
        id: list

        x: 0
        y: 0
        width: root.width
        height: root.height

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

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}
