import QtQuick 2.5

import "qrc:/qml/BuildingsMode/BuildingsMenus/DockingStationSubmenus/EquipmentsListScripts.js" as Scripts
import "../../.."
import "../.."
import Game 1.0

Item {
    id: rootHeroesList

    function update()
    {
        Scripts.setupList(Math.round((271/1080)*width), GameApi.base.dockingStation.equipmentsAmount(), width, height);
        for (var i=0;i<GameApi.base.dockingStation.equipmentsAmount();++i)
        {
            GameApi.base.dockingStation.prepareEquipmentForQML(i);
            var n1,v1,n2,v2,n3,v3,n4,v4,n5,v5,n6,v6;
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 1)
            {
                n1=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(0);
                v1=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(0);
            }
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 2)
            {
                n2=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(1);
                v2=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(1);
            }
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 3)
            {
                n3=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(2);
                v3=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(2);
            }
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 4)
            {
                n4=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(3);
                v4=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(3);
            }
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 5)
            {
                n5=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(4);
                v5=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(4);
            }
            if (GameApi.base.dockingStation.equipmentPreparedForQML.amountOfBonuses() >= 6)
            {
                n6=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosName(5);
                v6=GameApi.base.dockingStation.equipmentPreparedForQML.bonusAtPosValue(5);
            }

            Scripts.createItem(GameApi.base.dockingStation.equipmentPreparedForQML.name(), GameApi.base.dockingStation.equipmentPreparedForQML.name(), GameApi.base.dockingStation.equipmentPreparedForQML.typeString(), GameApi.base.dockingStation.equipmentPreparedForQML.tier(), GameApi.base.dockingStation.equipmentPreparedForQML.buyingAetheriteCost(),
                    n1,v1,n2,v2,n3,v3,n4,v4,n5,v5,n6,v6);
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

    signal buyClicked(int index)

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
                var index = Scripts.getClickedItemIndex(mouseX,y0);
                if (index != -1)
                    buyClicked(index);
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
