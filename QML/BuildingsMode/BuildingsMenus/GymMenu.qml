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
        id: table

        x: 0
        y: topBar.height
        width: parent.width
        height: taskBorderBottom.y + taskBorderBottom.height

        function update()
        {
            energyDrainAmount1.text = GameApi.base.buildings.gym.basicCostInEnergy()+"/Day";
            slotsAmount1.text = GameApi.base.buildings.gym.amountOfSlots();
            energyCostAmount1.text = GameApi.base.buildings.gym.useCostInEnergySingle()+"/Day";
            proficiencyBonusAmount1.text = GameApi.base.buildings.gym.proficiencyBonus();

            if (GameApi.base.buildings.gym.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                slotsAmount2.visible = false;
                energyCostAmount2.visible = false;
                proficiencyBonusAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.buildings.gym.basicCostInEnergyAfterUpgrade()+"/Day";
                slotsAmount2.text = GameApi.base.buildings.gym.amountOfSlotsAfterUpgrade();
                energyCostAmount2.text = GameApi.base.buildings.gym.useCostInEnergySingleAfterUpgrade()+"/Day";
                proficiencyBonusAmount2.text = GameApi.base.buildings.gym.proficiencyBonusAfterUpgrade();
            }
        }

        Text {
            id: levelText1

            x: 15
            y: 0

            color: "#94ef94"
            text: "Level: "
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: levelText2

            x: 490
            y: 0

            color: "#94ef94"
            text: "Current"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: levelText3

            x: 860
            y: 0

            color: "#94ef94"
            text: "Next"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Text {
            id: energyDrainText

            x: 15
            y: 64

            color: "#94ef94"
            text: "Energy Drain"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: energyDrainIcon

            x: 430
            y: 64
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }
        Text {
            id: energyDrainAmount1

            x: 530
            y: 64
            width: 230

            color: "#94ef94"
            text: "100/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: energyDrainAmount2

            x: 830
            y: 64
            width: 230

            color: "#94ef94"
            text: "100/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: slotsText

            x: 15
            y: 128

            color: "#94ef94"
            text: "Slots"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: slotsIcon

            x: 430
            y: 128
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Slots.png"
        }
        Text {
            id: slotsAmount1

            x: 620
            y: 128
            width: 77

            color: "#94ef94"
            text: "10"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: slotsAmount2

            x: 920
            y: 128
            width: 77

            color: "#94ef94"
            text: "10"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: energyCostText

            x: 15
            y: 192

            color: "#94ef94"
            text: "Energy cost"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: energyCostIcon

            x: 430
            y: 192
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }
        Text {
            id: energyCostAmount1

            x: 560
            y: 192
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: energyCostAmount2

            x: 860
            y: 192
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: combatEfficiencyBonusText

            x: 15
            y: 256

            color: "#94ef94"
            text: "PR bonus"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: proficiencyBonusIcon

            x: 430
            y: 256
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Attributes/PR.png"
        }
        Text {
            id: proficiencyBonusAmount1

            x: 560
            y: 256
            width: 200

            color: "#94ef94"
            text: "1"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: proficiencyBonusAmount2

            x: 860
            y: 256
            width: 200

            color: "#94ef94"
            text: "1"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Image {
            id: taskBorderBottom

            x: 17
            y: 336

            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Item {
        id: upgradeInfo

        x: 0
        y: table.y + table.height
        width: 1080
        height: taskBorderUpgradeBottom.y + taskBorderUpgradeBottom.height

        function update()
        {
            if (GameApi.base.buildings.gym.maxLevelReached())
            {
                energyAmount.text = "-";
                bmAmount.text = "-";
                timeAmount.text = "-";
                upgradeButton.markAsUpgraded(false);
                upgradeButton.visible = false;
                timeRemaining.visible = true;
                timeRemaining.text = "Max Level Reached";
                timeRemainingIcon.visible = false;
            }
            else
            {
                energyAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelTime();
                if (GameApi.base.buildings.gym.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.buildings.gym.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.buildings.gym.requirementsForNextLevelTime();
            }
        }

        Text {
            id: upgradeText

            x: 15
            y: 0

            color: "#94ef94"
            text: "Upgrade: "
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Text {
            id: energyAmount

            x: 360
            y: 5
            width: 100

            color: "#94ef94"
            text: "100"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: energyIcon

            x: 450
            y: 5

            width: 70
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }

        Text {
            id: bmAmount

            x: 520
            y: 5
            width: 100

            color: "#94ef94"
            text: "100"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: bmIcon

            x: 620
            y: 0

            width: 80
            height: width

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"
        }

        Text {
            id: timeAmount

            x: 700
            y: 5
            width: 100

            color: "#94ef94"
            text: "100"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: timeIcon

            x: 810
            y: 5

            width: 70
            height: width

            source: "qrc:/graphics/GUI/Time.png"
        }

        Text {
            id: timeRemaining

            property int time: 100

            x: 15
            y: 95

            color: "#94ef94"
            text: "Upgrade will be finished in "+time
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
            font.family: fontStencil.name
        }
        Image {
            id: timeRemainingIcon

            x: 820
            y: 95

            width: 60
            height: width

            source: "qrc:/graphics/GUI/Time.png"
        }

        Image {
            id: taskBorderUpgradeBottom

            x: 17
            y: 165

            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Item {
            id: upgradeButton

            x: 920
            y: 0
            width: 160
            height: width

            function markAsUpgraded(isUpgraded)
            {
                if (isUpgraded)
                    anim.restart();
                else
                    anim.stop();
            }

            Image {
                id: upgradeButtonIcon

                property alias anim: anim

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Settings.png"

                RotationAnimator on rotation {
                    id: anim

                    from: 0
                    to: 360
                    duration: 2500
                    loops: RotationAnimation.Infinite
                    running: false
                }
            }

            MouseArea {
                id: upgradeButtonMA

                anchors.fill: parent

                onClicked: upgradeRequested()
            }
        }
    }

    Item {
        id: slotsView

        x: 0
        y: 0
        width: parent.theoreticalWidth
        height: parent.theoreticalHeight

        property int indexOfChangingSlot: 0

        BuildingSlotView {
            id: slotView1

            x: 90
            y: upgradeInfo.y + upgradeInfo.height + 2

            property string mercenaryName

            mode: 1

            onArtClicked: {
                mercenarySelectionList.updateEverything("pr");
                parent.indexOfChangingSlot = 0;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.gym.placeMercenaryInSlot(0,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.gym.emptySlot(0);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView2

            x: 450
            y: slotView1.y

            property string mercenaryName

            mode: 1

            onArtClicked: {
                mercenarySelectionList.updateEverything("pr");
                parent.indexOfChangingSlot = 1;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.gym.placeMercenaryInSlot(1,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.gym.emptySlot(1);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView3

            x: 810
            y: slotView1.y

            property string mercenaryName

            mode: 1

            onArtClicked: {
                mercenarySelectionList.updateEverything("pr");
                parent.indexOfChangingSlot = 2;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.gym.placeMercenaryInSlot(2,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.gym.emptySlot(2);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }

        MercenariesList {
            id: mercenarySelectionList

            x: 0
            y: 0
            width: parent.width
            height: parent.height - back.height

            state: "hidden"

            onMercenaryClicked: {
                switch (parent.indexOfChangingSlot)
                {
                case 0:
                    slotView1.mercenaryName=mercenaryName;
                    slotView1.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.gym.useCostInEnergySingle(),GameApi.base.buildings.gym.duration()+1);
                    state = "hidden";
                    break;
                case 1:
                    slotView2.mercenaryName=mercenaryName;
                    slotView2.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.gym.useCostInEnergySingle(),GameApi.base.buildings.gym.duration()+1);
                    state = "hidden";
                    break;
                case 2:
                    slotView3.mercenaryName=mercenaryName;
                    slotView3.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.gym.useCostInEnergySingle(),GameApi.base.buildings.gym.duration()+1);
                    state = "hidden";
                    break;
                }
                mercenarySelectionList.banMercenary(mercenaryName);
            }
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
