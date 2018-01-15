import QtQuick 2.9

import Game 1.0
import ".."
import "./MercenariesList"

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()
    signal mercenariesModeUpdateRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.buildings.gym.description());
        topBar.setLevel("Level: "+GameApi.base.buildings.gym.currentLevel());
        table.update();
        upgradeInfo.update();
        mercenarySelectionList.updateEverything("pr");
        var amountOfSlotsAvailable = GameApi.base.buildings.gym.amountOfSlots();
        if (amountOfSlotsAvailable>=1)
        {
            if (GameApi.base.buildings.gym.mercenaryNameInSlot(0)!="")
            {
                slotView1.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(0);
                slotView1.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(0))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(0)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(0))+1);
                slotView1.forceAbortIcon();
            }
            else
                slotView1.removeMercenary();
            slotView1.visible=true;
            if (amountOfSlotsAvailable>=2)
            {
                if (GameApi.base.buildings.gym.mercenaryNameInSlot(1)!="")
                {
                    slotView2.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(1);
                    slotView2.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(1))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(1)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(1))+1);
                    slotView2.forceAbortIcon();
                }
                else
                    slotView2.removeMercenary();
                slotView2.visible=true;
                if (amountOfSlotsAvailable>=3)
                {
                    if (GameApi.base.buildings.gym.mercenaryNameInSlot(2)!="")
                    {
                        slotView3.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(2);
                        slotView3.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(2))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(2)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(2))+1);
                        slotView3.forceAbortIcon();
                    }
                    else
                        slotView3.removeMercenary();
                    slotView3.visible=true;
                }
                else
                    slotView3.visible=false;
            }
            else
            {
                slotView2.visible=false;
                slotView3.visible=false;
            }
        }
        else
        {
            slotView1.visible=false;
            slotView2.visible=false;
            slotView3.visible=false;
        }
    }

    function reactToBackOnToolbar()
    {
        if (mercenarySelectionList.state == "")
        {
            mercenarySelectionList.state = "hidden";
            return true;
        }
        else
        {
            if (!slotView1.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
                slotView1.removeMercenary();
            }
            if (!slotView2.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
                slotView2.removeMercenary();
            }
            if (!slotView3.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
                slotView3.removeMercenary();
            }
            return false;
        }
    }

    function returnToDefault()
    {
        if (!slotView1.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
            slotView1.removeMercenary();
        }
        if (!slotView2.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
            slotView2.removeMercenary();
        }
        if (!slotView3.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
            slotView3.removeMercenary();
        }
        mercenarySelectionList.state = "hidden";
    }

    function requestUnban(mercenaryName)
    {
        mercenarySelectionList.unbanMercenary(mercenaryName);
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

    BuildingsListDelegate {
        id: topBar

        x: 0
        y: 0
        width: 1080
        height: 271

        Component.onCompleted: {
            setArtSource("qrc:/graphics/Buildings/Gym.png");
            setName(GameApi.tr("Gym"));
        }
    }

    Item {
        id: upgrade

        x: 17
        y: 268
        width: 1048
        height: 118

        Image{
            id: background

            x: 312
            y:0
            width: 734
            height: 115

            source: "qrc:/graphics/GUI/Upgrade_Background.png"
        }

        Image{
            id: overlay

            x: 312
            y:0
            width: 734
            height: 115

            source: "qrc:/graphics/GUI/MercenarySlot/Opacity_Mask.png"
        }

        Image{
            id: taskBorder

            x: 0
            y: 115
            width: parent
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Text{

            x: 5
            y: 0
            height: upgrade.height
            verticalAlignment: Text.AlignVCenter
            color: "#94ef94"
            text: "info & upgrades"
            font.pixelSize: 90
            font.family: fontStencil.name
        }

        MouseArea{
            anchors.fill: parent
        }
    }

    // Tutaj maja byc delegaty slotow bez zadnych odstepow czyli kazdy delegat ma miec y o 118 wiekszy, a ich x maja byc rowne 17

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
            text: qsTr("Back")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            anchors.fill: parent

            onClicked: {
                if (mercenarySelectionList.state == "hidden")
                {
                    if (!slotView1.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
                        slotView1.removeMercenary();
                    }
                    if (!slotView2.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
                        slotView2.removeMercenary();
                    }
                    if (!slotView3.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
                        slotView3.removeMercenary();
                    }
                    backClicked();
                }
                else
                {
                    if (slotsView.indexOfChangingSlot==0)
                        mercenarySelectionList.banMercenary(slotView1.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==1)
                        mercenarySelectionList.banMercenary(slotView2.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==2)
                        mercenarySelectionList.banMercenary(slotView3.mercenaryName);
                    mercenarySelectionList.state = "hidden";
                }
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
