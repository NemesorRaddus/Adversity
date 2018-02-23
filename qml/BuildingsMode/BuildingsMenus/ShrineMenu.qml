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
        topBar.setDescription(GameApi.base.buildings.shrine.description());
        topBar.setLevel("Level: "+GameApi.base.buildings.shrine.currentLevel());
        table.update();
        upgradeInfo.update();
        mercenarySelectionList.updateEverything("");
        var amountOfSlotsAvailable = GameApi.base.buildings.shrine.amountOfSlots();
        if (amountOfSlotsAvailable>=1)
        {
            if (GameApi.base.buildings.shrine.mercenaryNameInSlot(0)!="")
            {
                slotView1.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(0);
                slotView1.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(0))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(0)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                slotView1.forceAbortIcon();
            }
            else
                slotView1.removeMercenary();
            slotView1.visible=true;
            if (amountOfSlotsAvailable>=2)
            {
                if (GameApi.base.buildings.shrine.mercenaryNameInSlot(1)!="")
                {
                    slotView2.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(1);
                    slotView2.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(1))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(1)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    slotView2.forceAbortIcon();
                }
                else
                    slotView2.removeMercenary();
                slotView2.visible=true;
                if (amountOfSlotsAvailable>=3)
                {
                    if (GameApi.base.buildings.shrine.mercenaryNameInSlot(2)!="")
                    {
                        slotView3.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(2);
                        slotView3.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(2))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(2)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                        slotView3.forceAbortIcon();
                    }
                    else
                        slotView3.removeMercenary();
                    slotView3.visible=true;
                    if (amountOfSlotsAvailable>=4)
                    {
                        if (GameApi.base.buildings.shrine.mercenaryNameInSlot(3)!="")
                        {
                            slotView4.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(3);
                            slotView4.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(3))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(3)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                            slotView4.forceAbortIcon();
                        }
                        else
                            slotView4.removeMercenary();
                        slotView4.visible=true;
                        if (amountOfSlotsAvailable>=5)
                        {
                            if (GameApi.base.buildings.shrine.mercenaryNameInSlot(4)!="")
                            {
                                slotView5.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(4);
                                slotView5.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(4))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(4)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                                slotView5.forceAbortIcon();
                            }
                            else
                                slotView5.removeMercenary();
                            slotView5.visible=true;
                            if (amountOfSlotsAvailable==6)
                            {
                                if (GameApi.base.buildings.shrine.mercenaryNameInSlot(5)!="")
                                {
                                    slotView6.mercenaryName=GameApi.base.buildings.shrine.mercenaryNameInSlot(5);
                                    slotView6.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.shrine.mercenaryProfessionInSlot(5))+"/"+GameApi.base.buildings.shrine.mercenaryNameInSlot(5)+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                                    slotView6.forceAbortIcon();
                                }
                                else
                                    slotView6.removeMercenary();
                                slotView6.visible=true;
                            }
                            else
                                slotView6.visible=false;
                        }
                        else
                        {
                            slotView5.visible=false;
                            slotView6.visible=false;
                        }
                    }
                    else
                    {
                        slotView4.visible=false;
                        slotView5.visible=false;
                        slotView6.visible=false;
                    }
                }
                else
                {
                    slotView3.visible=false;
                    slotView4.visible=false;
                    slotView5.visible=false;
                    slotView6.visible=false;
                }
            }
            else
            {
                slotView2.visible=false;
                slotView3.visible=false;
                slotView4.visible=false;
                slotView5.visible=false;
                slotView6.visible=false;
            }
        }
        else
        {
            slotView1.visible=false;
            slotView2.visible=false;
            slotView3.visible=false;
            slotView4.visible=false;
            slotView5.visible=false;
            slotView6.visible=false;
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
            if (!slotView4.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView4.mercenaryName);
                slotView4.removeMercenary();
            }
            if (!slotView5.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView5.mercenaryName);
                slotView5.removeMercenary();
            }
            if (!slotView6.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView6.mercenaryName);
                slotView6.removeMercenary();
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
        if (!slotView4.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView4.mercenaryName);
            slotView4.removeMercenary();
        }
        if (!slotView5.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView5.mercenaryName);
            slotView5.removeMercenary();
        }
        if (!slotView6.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView6.mercenaryName);
            slotView6.removeMercenary();
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
            setArtSource("qrc:/graphics/Buildings/Shrine.png");
            setName(GameApi.tr("Shrine"));
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
            energyDrainAmount1.text = GameApi.base.buildings.shrine.basicCostInEnergy()+"/Day";
            slotsAmount1.text = GameApi.base.buildings.shrine.amountOfSlots();
            activeStressReliefAmount1.text = GameApi.base.buildings.shrine.activeStressRelief()+"/Day";
            convivialStressReliefAmount1.text = GameApi.base.buildings.shrine.convivialStressRelief()+"/Day";
            recluseStressReliefAmount1.text = GameApi.base.buildings.shrine.recluseStressRelief()+"/Day";
            religiousStressReliefAmount1.text = GameApi.base.buildings.shrine.religiousStressRelief()+"/Day";

            if (GameApi.base.buildings.shrine.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                slotsAmount2.visible = false;
                activeStressReliefAmount2.visible = false;
                convivialStressReliefAmount2.visible = false;
                recluseStressReliefAmount2.visible = false;
                religiousStressReliefAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.buildings.shrine.basicCostInEnergyAfterUpgrade()+"/Day";
                slotsAmount2.text = GameApi.base.buildings.shrine.amountOfSlotsAfterUpgrade();
                activeStressReliefAmount2.text = GameApi.base.buildings.shrine.activeStressReliefAfterUpgrade()+"/Day";
                convivialStressReliefAmount2.text = GameApi.base.buildings.shrine.convivialStressReliefAfterUpgrade()+"/Day";
                recluseStressReliefAmount2.text = GameApi.base.buildings.shrine.recluseStressReliefAfterUpgrade()+"/Day";
                religiousStressReliefAmount2.text = GameApi.base.buildings.shrine.religiousStressReliefAfterUpgrade()+"/Day";
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
            id: activeStressReliefText

            x: 15
            y: 192

            color: "#94ef94"
            text: "Relief (ACT)"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: activeStressReliefIcon

            x: 430
            y: 192
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
        }
        Text {
            id: activeStressReliefAmount1

            x: 560
            y: 192
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: activeStressReliefAmount2

            x: 860
            y: 192
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: convivialStressReliefText

            x: 15
            y: 256

            color: "#94ef94"
            text: "Relief (CON)"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: convivialStressReliefIcon

            x: 430
            y: 256
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
        }
        Text {
            id: convivialStressReliefAmount1

            x: 560
            y: 256
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: convivialStressReliefAmount2

            x: 860
            y: 256
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: recluseStressReliefText

            x: 15
            y: 320

            color: "#94ef94"
            text: "Relief (REC)"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: recluseStressReliefIcon

            x: 430
            y: 320
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
        }
        Text {
            id: recluseStressReliefAmount1

            x: 560
            y: 320
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: recluseStressReliefAmount2

            x: 860
            y: 320
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: religiousStressReliefText

            x: 15
            y: 384

            color: "#94ef94"
            text: "Relief (REL)"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: religiousStressReliefIcon

            x: 430
            y: 384
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
        }
        Text {
            id: religiousStressReliefAmount1

            x: 560
            y: 384
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: religiousStressReliefAmount2

            x: 860
            y: 384
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Image {
            id: taskBorderBottom

            x: 17
            y: 464

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
            if (GameApi.base.buildings.shrine.maxLevelReached())
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
                energyAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelTime();
                if (GameApi.base.buildings.shrine.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.buildings.shrine.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.buildings.shrine.requirementsForNextLevelTime();
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

            x: 0
            y: upgradeInfo.y + upgradeInfo.height + 2

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 0;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(0,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(0);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView2

            x: 180
            y: slotView1.y

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 1;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(1,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(1);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView3

            x: 360
            y: slotView1.y

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 2;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(2,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(2);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView4

            x: 540
            y: slotView1.y

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 3;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(3,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(3);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView5

            x: 720
            y: slotView1.y

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 4;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(4,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(4);
                mercenarySelectionList.unbanMercenary(mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onRequestUnban: {
                mercenarySelectionList.unbanMercenary(mercenaryName);
            }
        }
        BuildingSlotView {
            id: slotView6

            x: 900
            y: slotView1.y

            property string mercenaryName

            mode: 0

            onArtClicked: {
                mercenarySelectionList.updateEverything("");
                parent.indexOfChangingSlot = 5;
                mercenarySelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.buildings.shrine.placeMercenaryInSlot(5,mercenaryName);
                mercenariesModeUpdateRequested();
            }

            onAbortClicked: {
                GameApi.base.buildings.shrine.emptySlot(5);
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
                    slotView1.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    state = "hidden";
                    break;
                case 1:
                    slotView2.mercenaryName=mercenaryName;
                    slotView2.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    state = "hidden";
                    break;
                case 2:
                    slotView3.mercenaryName=mercenaryName;
                    slotView3.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    state = "hidden";
                    break;
                case 3:
                    slotView4.mercenaryName=mercenaryName;
                    slotView4.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    state = "hidden";
                    break;
                case 4:
                    slotView5.mercenaryName=mercenaryName;
                    slotView5.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
                    state = "hidden";
                    break;
                case 5:
                    slotView6.mercenaryName=mercenaryName;
                    slotView6.setMercenaryOneVal("qrc:/graphics/Mercenaries/"+GameApi.globalsCpp.alterNormalTextToInternal(mercenaryProfession)+"/"+mercenaryName+".png",GameApi.base.buildings.shrine.useCostInEnergySingle());
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
                    if (!slotView4.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView4.mercenaryName);
                        slotView4.removeMercenary();
                    }
                    if (!slotView5.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView5.mercenaryName);
                        slotView5.removeMercenary();
                    }
                    if (!slotView6.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView6.mercenaryName);
                        slotView6.removeMercenary();
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
                    else if (slotsView.indexOfChangingSlot==3)
                        mercenarySelectionList.banMercenary(slotView4.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==4)
                        mercenarySelectionList.banMercenary(slotView5.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==5)
                        mercenarySelectionList.banMercenary(slotView6.mercenaryName);
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
