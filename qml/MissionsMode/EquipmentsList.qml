import QtQuick 2.9

import "qrc:/qml/MissionsMode/EquipmentsListScripts.js" as Scripts
import "../.."
import ".."
import Game 1.0

Item {
    id: rootEquipmentsList

    property bool armors

    function showArmors()
    {
        armors=true;
        Scripts.setupList(Math.round((271/1080)*width), GameApi.base.amountOfAvailableArmors()+1, width, height);
        Scripts.createItem("","","","","",["","","","","",""],[0,0,0,0,0,0]);
        for (var i=0;i<GameApi.base.amountOfAvailableEquipment();++i)
        {
            GameApi.base.prepareAvailableEquipment(i);

            if (GameApi.base.preparedAvailableEquipment.typeString() != "Armor")
                continue;

            var n=["","","","","",""],v=[0,0,0,0,0,0];
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 1)
            {
                n[0]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(0);
                v[0]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(0);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 2)
            {
                n[1]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(1);
                v[1]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(1);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 3)
            {
                n[2]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(2);
                v[2]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(2);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 4)
            {
                n[3]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(3);
                v[3]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(3);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 5)
            {
                n[4]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(4);
                v[4]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(4);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 6)
            {
                n[5]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(5);
                v[5]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(5);
            }

            for (var j=0;j<6;++j)
                if (n[j]=="Luck" || n[j]=="Stress Border")
                {
                    for (var k=j+1;k<6;++k)
                    {
                        n[k-1]=n[k];
                        v[k-1]=v[k];
                    }
                    n[5]="";
                    v[5]="";
                }

            Scripts.createItem(GameApi.base.preparedAvailableEquipment.name(), GameApi.base.preparedAvailableEquipment.name(), GameApi.base.preparedAvailableEquipment.typeString(), GameApi.base.preparedAvailableEquipment.tier(),
                    n,v);
        }
    }
    function showWeaponsTools(bannedName)
    {
        armors=false;
        var totalAmount=GameApi.base.amountOfAvailableWeaponsTools()+1;
        for (var i=0;i<GameApi.base.amountOfAvailableEquipment();++i)
        {
            GameApi.base.prepareAvailableEquipment(i);

            if (GameApi.base.preparedAvailableEquipment.name() == bannedName)
                --totalAmount;
        }

        Scripts.setupList(Math.round((271/1080)*width), totalAmount, width, height);
        Scripts.createItem("","","","","",["","","","","",""],[0,0,0,0,0,0]);
        for (i=0;i<GameApi.base.amountOfAvailableEquipment();++i)
        {
            GameApi.base.prepareAvailableEquipment(i);

            if (GameApi.base.preparedAvailableEquipment.typeString() != "Weapon/Tool" || GameApi.base.preparedAvailableEquipment.name() == bannedName)
                continue;

            var n=["","","","","",""],v=[0,0,0,0,0,0];
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 1)
            {
                n[0]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(0);
                v[0]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(0);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 2)
            {
                n[1]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(1);
                v[1]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(1);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 3)
            {
                n[2]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(2);
                v[2]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(2);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 4)
            {
                n[3]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(3);
                v[3]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(3);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 5)
            {
                n[4]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(4);
                v[4]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(4);
            }
            if (GameApi.base.preparedAvailableEquipment.amountOfBonuses() >= 6)
            {
                n[5]=GameApi.base.preparedAvailableEquipment.bonusAtPosName(5);
                v[5]=GameApi.base.preparedAvailableEquipment.bonusAtPosValue(5);
            }

            for (var j=0;j<6;++j)
                if (n[j]=="Luck" || n[j]=="Stress Border")
                {
                    for (var k=j+1;k<6;++k)
                    {
                        n[k-1]=n[k];
                        v[k-1]=v[k];
                    }
                    n[5]="";
                    v[5]="";
                }

            Scripts.createItem(GameApi.base.preparedAvailableEquipment.name(), GameApi.base.preparedAvailableEquipment.name(), GameApi.base.preparedAvailableEquipment.typeString(), GameApi.base.preparedAvailableEquipment.tier(), n, v);
        }
    }

    function returnToDefault()
    {
        Scripts.scrollList(3000);
    }

    property int startY

    clip: true

    signal selected(string name, string artSource)

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
                var n = Scripts.getClickedItemName(y0);
                if (n != "nothing")
                    selected(n, Scripts.getClickedItemArt(y0));
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
