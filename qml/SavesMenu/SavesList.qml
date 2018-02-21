import QtQuick 2.9

import "qrc:/qml/BuildingsMode/BuildingsListScripts.js" as Scripts
import ".."
import Game 1.0

Item {
    id: rootBuildingsList

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        Scripts.setItem(0,GameApi.tr("CentralUnit"),"CentralUnit",GameApi.base.buildings.centralUnit.currentLevel(), GameApi.base.buildings.centralUnit.description());
        Scripts.setItem(1,GameApi.tr("DockingStation"),"DockingStation",GameApi.base.buildings.dockingStation.currentLevel(), GameApi.base.buildings.dockingStation.description());
        Scripts.setItem(2,GameApi.tr("Hospital"),"Hospital",GameApi.base.buildings.hospital.currentLevel(), GameApi.base.buildings.hospital.description());
        Scripts.setItem(3,GameApi.tr("TrainingGround"),"TrainingGround",GameApi.base.buildings.trainingGround.currentLevel(), GameApi.base.buildings.trainingGround.description());
        Scripts.setItem(4,GameApi.tr("Gym"),"Gym",GameApi.base.buildings.gym.currentLevel(), GameApi.base.buildings.gym.description());
        Scripts.setItem(5,GameApi.tr("Laboratory"),"Laboratory",GameApi.base.buildings.laboratory.currentLevel(), GameApi.base.buildings.laboratory.description());
        Scripts.setItem(6,GameApi.tr("PlayingField"),"PlayingField",GameApi.base.buildings.playingField.currentLevel(), GameApi.base.buildings.playingField.description());
        Scripts.setItem(7,GameApi.tr("Bar"),"Bar",GameApi.base.buildings.bar.currentLevel(), GameApi.base.buildings.bar.description());
        Scripts.setItem(8,GameApi.tr("Shrine"),"Shrine",GameApi.base.buildings.shrine.currentLevel(), GameApi.base.buildings.shrine.description());
        Scripts.setItem(9,GameApi.tr("Seclusion"),"Seclusion",GameApi.base.buildings.seclusion.currentLevel(), GameApi.base.buildings.seclusion.description());
        Scripts.setItem(10,GameApi.tr("Powerplant"),"Powerplant",GameApi.base.buildings.powerplant.currentLevel(), GameApi.base.buildings.powerplant.description());
        Scripts.setItem(11,GameApi.tr("Factory"),"Factory",GameApi.base.buildings.factory.currentLevel(), GameApi.base.buildings.factory.description());
        Scripts.setItem(12,GameApi.tr("CoolRoom"),"CoolRoom",GameApi.base.buildings.coolRoom.currentLevel(), GameApi.base.buildings.coolRoom.description());
        Scripts.setItem(13,GameApi.tr("StorageRoom"),"StorageRoom",GameApi.base.buildings.storageRoom.currentLevel(), GameApi.base.buildings.storageRoom.description());
        Scripts.setItem(14,GameApi.tr("AetheriteSilo"),"AetheriteSilo",GameApi.base.buildings.aetheriteSilo.currentLevel(), GameApi.base.buildings.aetheriteSilo.description());
        Scripts.setItem(15,GameApi.tr("Barracks"),"Barracks",GameApi.base.buildings.barracks.currentLevel(), GameApi.base.buildings.barracks.description());

        Scripts.setUpgradedStatus(GameApi.tr("Central Unit"),GameApi.base.buildings.centralUnit.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Docking Station"),GameApi.base.buildings.dockingStation.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Hospital"),GameApi.base.buildings.hospital.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Training Ground"),GameApi.base.buildings.trainingGround.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Gym"),GameApi.base.buildings.gym.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Laboratory"),GameApi.base.buildings.laboratory.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Playing Field"),GameApi.base.buildings.playingField.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Bar"),GameApi.base.buildings.bar.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Shrine"),GameApi.base.buildings.shrine.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Seclusion"),GameApi.base.buildings.seclusion.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Powerplant"),GameApi.base.buildings.powerplant.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Factory"),GameApi.base.buildings.factory.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Cool Room"),GameApi.base.buildings.coolRoom.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Storage Room"),GameApi.base.buildings.storageRoom.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Aetherite Silo"),GameApi.base.buildings.aetheriteSilo.isBeingUpgraded());
        Scripts.setUpgradedStatus(GameApi.tr("Barracks"),GameApi.base.buildings.barracks.isBeingUpgraded());
    }

    function returnToDefault()
    {
        Scripts.scrollList(3000);
    }

    function markAsUpgraded(buildingName, isUpgraded)
    {
        Scripts.setUpgradedStatus(buildingName,isUpgraded);
    }

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
            movementCheckTimer.start();
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else if (rootBuildingsList.state == "")
                buildingClicked(Scripts.getClickedItemName(y0));
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

    Component.onCompleted: {
        Scripts.setupList(Math.round((271/1080)*width), 16, width, height);
        Scripts.createItem(GameApi.tr("CentralUnit"),"CentralUnit",GameApi.base.buildings.centralUnit.currentLevel(), GameApi.base.buildings.centralUnit.description());
        Scripts.createItem(GameApi.tr("DockingStation"),"DockingStation",GameApi.base.buildings.dockingStation.currentLevel(), GameApi.base.buildings.dockingStation.description());
        Scripts.createItem(GameApi.tr("Hospital"),"Hospital",GameApi.base.buildings.hospital.currentLevel(), GameApi.base.buildings.hospital.description());
        Scripts.createItem(GameApi.tr("TrainingGround"),"TrainingGround",GameApi.base.buildings.trainingGround.currentLevel(), GameApi.base.buildings.trainingGround.description());
        Scripts.createItem(GameApi.tr("Gym"),"Gym",GameApi.base.buildings.gym.currentLevel(), GameApi.base.buildings.gym.description());
        Scripts.createItem(GameApi.tr("Laboratory"),"Laboratory",GameApi.base.buildings.laboratory.currentLevel(), GameApi.base.buildings.laboratory.description());
        Scripts.createItem(GameApi.tr("PlayingField"),"PlayingField",GameApi.base.buildings.playingField.currentLevel(), GameApi.base.buildings.playingField.description());
        Scripts.createItem(GameApi.tr("Bar"),"Bar",GameApi.base.buildings.bar.currentLevel(), GameApi.base.buildings.bar.description());
        Scripts.createItem(GameApi.tr("Shrine"),"Shrine",GameApi.base.buildings.shrine.currentLevel(), GameApi.base.buildings.shrine.description());
        Scripts.createItem(GameApi.tr("Seclusion"),"Seclusion",GameApi.base.buildings.seclusion.currentLevel(), GameApi.base.buildings.seclusion.description());
        Scripts.createItem(GameApi.tr("Powerplant"),"Powerplant",GameApi.base.buildings.powerplant.currentLevel(), GameApi.base.buildings.powerplant.description());
        Scripts.createItem(GameApi.tr("Factory"),"Factory",GameApi.base.buildings.factory.currentLevel(), GameApi.base.buildings.factory.description());
        Scripts.createItem(GameApi.tr("CoolRoom"),"CoolRoom",GameApi.base.buildings.coolRoom.currentLevel(), GameApi.base.buildings.coolRoom.description());
        Scripts.createItem(GameApi.tr("StorageRoom"),"StorageRoom",GameApi.base.buildings.storageRoom.currentLevel(), GameApi.base.buildings.storageRoom.description());
        Scripts.createItem(GameApi.tr("Aetherite Silo"),"AetheriteSilo",GameApi.base.buildings.aetheriteSilo.currentLevel(), GameApi.base.buildings.aetheriteSilo.description());
        Scripts.createItem(GameApi.tr("Barracks"),"Barracks",GameApi.base.buildings.barracks.currentLevel(), GameApi.base.buildings.barracks.description());
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: rootBuildingsList; y: -1 * height }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }
}
