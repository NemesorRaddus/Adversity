import QtQuick 2.5

import "qrc:/qml/BuildingsListScripts.js" as Scripts
import "."
import Game 1.0

Item {
    id: rootBuildingsList

    property double maxAmountOfItems: (height / Globals.dpcm) / (1.5 * Globals.dpcm)
    property int startY

    clip: true

    Item {
        id: scrollBar

        property int fullHeight
        property int yTop
        property int yBottom

        function scroll(y)
        {
            state = "";
            //timer.restart();
            if (y > 0)
            {
                if (yBottom < fullHeight - 1)
                {
                    ++yTop;
                    ++yBottom;//TODO visual part
                }
            }
            else if (y < 0)
            {
                if (yTop > 0)
                {
                    --yTop;
                    --yBottom;
                }
            }
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges {
                    target: scrollBar
                    visible: false
                }
            }
        ]

        Timer {
            id: timer

            interval: 1000; running: false; repeat: false

            onTriggered: scrollBar.state = "hidden";
        }
    }

    MouseArea {
        id: mouseArea

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

        anchors.fill: parent

        signal buildingClicked(string buildingName)

        onPressed: {
            y0 = mouseY;
        }

        onMouseYChanged: {
            if (isScrollingActive == true)
            {
                Scripts.scrollList(Math.ceil(mouseY) - y0);
                scrollBar.scroll(Math.ceil(mouseY) - y0);

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
                        scrollBar.scroll(1);
                    }
                    else
                    {
                        Scripts.scrollList(-1);
                        scrollBar.scroll(-1);
                    }
                    y0 = mouseY;
                }
            }
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else
            {console.log("kliknięto ",Scripts.getClickedItemName(y0));buildingClicked(Scripts.getClickedItemName(y0));}
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
        Scripts.createItem("Power Plant","PowerPlant",GameApi.base.powerPlant.currentLevel(), GameApi.base.powerPlant.description());
        Scripts.createItem("Factory","Factory",GameApi.base.factory.currentLevel(), GameApi.base.factory.description());
        Scripts.createItem("Cool Room","CoolRoom",GameApi.base.coolRoom.currentLevel(), GameApi.base.coolRoom.description());
        Scripts.createItem("Storage Room","StorageRoom",GameApi.base.storageRoom.currentLevel(), GameApi.base.storageRoom.description());
        Scripts.createItem("Aetherite Silo","AetheriteSilo",GameApi.base.aetheriteSilo.currentLevel(), GameApi.base.aetheriteSilo.description());
        Scripts.createItem("Barracks","Barracks",GameApi.base.barracks.currentLevel(), GameApi.base.barracks.description());
        Scripts.createItem("Docking Station","DockingStation",GameApi.base.dockingStation.currentLevel(), GameApi.base.dockingStation.description());
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: rootBuildingsList; x: -1 * width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: rootBuildingsList; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}
