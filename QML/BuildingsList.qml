import QtQuick 2.5

import "qrc:/qml/BuildingsListScripts.js" as Scripts
import "."
import Game 1.0

Item {
    id: rootBuildingsList

    function updateEverything()
    {
        Scripts.setItem(0,"Central Unit","CentralUnit",GameApi.base.centralUnit.currentLevel(), GameApi.base.centralUnit.description());
        Scripts.setItem(1,"Hospital","Hospital",GameApi.base.hospital.currentLevel(), GameApi.base.hospital.description());
        Scripts.setItem(2,"Training Ground","TrainingGround",GameApi.base.trainingGround.currentLevel(), GameApi.base.trainingGround.description());
        Scripts.setItem(3,"Gym","Gym",GameApi.base.gym.currentLevel(), GameApi.base.gym.description());
        Scripts.setItem(4,"Laboratory","Laboratory",GameApi.base.laboratory.currentLevel(), GameApi.base.laboratory.description());
        Scripts.setItem(5,"Playing Field","PlayingField",GameApi.base.playingField.currentLevel(), GameApi.base.playingField.description());
        Scripts.setItem(6,"Bar","Bar",GameApi.base.bar.currentLevel(), GameApi.base.bar.description());
        Scripts.setItem(7,"Shrine","Shrine",GameApi.base.shrine.currentLevel(), GameApi.base.shrine.description());
        Scripts.setItem(8,"Seclusion","Seclusion",GameApi.base.seclusion.currentLevel(), GameApi.base.seclusion.description());
        Scripts.setItem(9,"Powerplant","Powerplant",GameApi.base.powerplant.currentLevel(), GameApi.base.powerplant.description());
        Scripts.setItem(10,"Factory","Factory",GameApi.base.factory.currentLevel(), GameApi.base.factory.description());
        Scripts.setItem(11,"Cool Room","CoolRoom",GameApi.base.coolRoom.currentLevel(), GameApi.base.coolRoom.description());
        Scripts.setItem(12,"Storage Room","StorageRoom",GameApi.base.storageRoom.currentLevel(), GameApi.base.storageRoom.description());
        Scripts.setItem(13,"Aetherite Silo","AetheriteSilo",GameApi.base.aetheriteSilo.currentLevel(), GameApi.base.aetheriteSilo.description());
        Scripts.setItem(14,"Barracks","Barracks",GameApi.base.barracks.currentLevel(), GameApi.base.barracks.description());
        Scripts.setItem(15,"Docking Station","DockingStation",GameApi.base.dockingStation.currentLevel(), GameApi.base.dockingStation.description());
    }

    function returnToDefault()
    {
        for (var i=0;i<1000;++i)
            Scripts.scrollList(1);
    }

    property double maxAmountOfItems: (height / Globals.dpcm) / (1.5 * Globals.dpcm)
    property int startY

    clip: true

    signal buildingClicked(string buildingName)

    MouseArea {
        id: mouseArea

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

        anchors.fill: parent

        onPressed: {
            y0 = mouseY;
        }

        onMouseYChanged: {
            if (isScrollingActive == true)
            {
                Scripts.scrollList(Math.ceil(mouseY) - y0);

                y0 = Math.ceil(mouseY);
            }
            else
            {
                if (Math.abs(mouseY - y0) >= Globals.windowHeight * yChangedThresholdForScrolling / 100)
                {
                    isScrollingActive = true;
                    if (y0 > mouseY)
                    {
                        Scripts.scrollList(1);
                    }
                    else
                    {
                        Scripts.scrollList(-1);
                    }
                    y0 = mouseY;
                }
            }
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else
                buildingClicked(Scripts.getClickedItemName(y0));
            y0 = -1;
        }
    }

    Component.onCompleted: {
        Scripts.setupList(4, Globals.dpcm, 16, width, height);
        Scripts.createItem("Central Unit","CentralUnit",GameApi.base.centralUnit.currentLevel(), GameApi.base.centralUnit.description());
        Scripts.createItem("Hospital","Hospital",GameApi.base.hospital.currentLevel(), GameApi.base.hospital.description());
        Scripts.createItem("Training Ground","TrainingGround",GameApi.base.trainingGround.currentLevel(), GameApi.base.trainingGround.description());
        Scripts.createItem("Gym","Gym",GameApi.base.gym.currentLevel(), GameApi.base.gym.description());
        Scripts.createItem("Laboratory","Laboratory",GameApi.base.laboratory.currentLevel(), GameApi.base.laboratory.description());
        Scripts.createItem("Playing Field","PlayingField",GameApi.base.playingField.currentLevel(), GameApi.base.playingField.description());
        Scripts.createItem("Bar","Bar",GameApi.base.bar.currentLevel(), GameApi.base.bar.description());
        Scripts.createItem("Shrine","Shrine",GameApi.base.shrine.currentLevel(), GameApi.base.shrine.description());
        Scripts.createItem("Seclusion","Seclusion",GameApi.base.seclusion.currentLevel(), GameApi.base.seclusion.description());
        Scripts.createItem("Powerplant","Powerplant",GameApi.base.powerplant.currentLevel(), GameApi.base.powerplant.description());
        Scripts.createItem("Factory","Factory",GameApi.base.factory.currentLevel(), GameApi.base.factory.description());
        Scripts.createItem("Cool Room","CoolRoom",GameApi.base.coolRoom.currentLevel(), GameApi.base.coolRoom.description());
        Scripts.createItem("Storage Room","StorageRoom",GameApi.base.storageRoom.currentLevel(), GameApi.base.storageRoom.description());
        Scripts.createItem("Aetherite Silo","AetheriteSilo",GameApi.base.aetheriteSilo.currentLevel(), GameApi.base.aetheriteSilo.description());
        Scripts.createItem("Barracks","Barracks",GameApi.base.barracks.currentLevel(), GameApi.base.barracks.description());
        Scripts.createItem("Docking Station","DockingStation",GameApi.base.dockingStation.currentLevel(), GameApi.base.dockingStation.description());
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: rootBuildingsList; y: -1 * height }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 500 }
    }
}
