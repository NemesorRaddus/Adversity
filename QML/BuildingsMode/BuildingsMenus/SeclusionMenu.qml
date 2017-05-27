import QtQuick 2.5

import Game 1.0
import ".."
import "./HeroesList"

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.seclusion.description());
        topBar.setLevel("Level: "+GameApi.base.seclusion.currentLevel());
        table.update();
        upgradeInfo.update();
//        var amountOfSlotsAvailable = GameApi.base.seclusion.amountOfSlots();
//        if (amountOfSlotsAvailable>=1)
//        {
//            slotView1.visible=true;
//            if (amountOfSlotsAvailable>=2)
//            {
//                slotView2.visible=true;
//                if (amountOfSlotsAvailable>=3)
//                {
//                    slotView3.visible=true;
//                    if (amountOfSlotsAvailable>=4)
//                    {
//                        slotView4.visible=true;
//                        if (amountOfSlotsAvailable>=5)
//                        {
//                            slotView5.visible=true;
//                            if (amountOfSlotsAvailable==6)
//                                slotView6.visible=true;
//                            else
//                                slotView6.visible=false;
//                        }
//                        else
//                        {
//                            slotView5.visible=false;
//                            slotView6.visible=false;
//                        }
//                    }
//                    else
//                    {
//                        slotView4.visible=false;
//                        slotView5.visible=false;
//                        slotView6.visible=false;
//                    }
//                }
//                else
//                {
//                    slotView3.visible=false;
//                    slotView4.visible=false;
//                    slotView5.visible=false;
//                    slotView6.visible=false;
//                }
//            }
//            else
//            {
//                slotView2.visible=false;
//                slotView3.visible=false;
//                slotView4.visible=false;
//                slotView5.visible=false;
//                slotView6.visible=false;
//            }
//        }
//        else
//        {
//            slotView1.visible=false;
//            slotView2.visible=false;
//            slotView3.visible=false;
//            slotView4.visible=false;
//            slotView5.visible=false;
//            slotView6.visible=false;
//        }
    }

    function reactToBackOnToolbar()
    {
        if (heroSelectionList.state == "")
        {
            heroSelectionList.state = "hidden";
            return true;
        }
        else
        {
            if (!slotView1.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView1.heroName);
                slotView1.removeHero();
            }
            if (!slotView2.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView2.heroName);
                slotView2.removeHero();
            }
            if (!slotView3.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView3.heroName);
                slotView3.removeHero();
            }
            if (!slotView4.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView4.heroName);
                slotView4.removeHero();
            }
            if (!slotView5.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView5.heroName);
                slotView5.removeHero();
            }
            if (!slotView6.isConfirmed)
            {
                heroSelectionList.unbanHero(slotView6.heroName);
                slotView6.removeHero();
            }
            return false;
        }
    }

    function returnToDefault()
    {
        if (!slotView1.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView1.heroName);
            slotView1.removeHero();
        }
        if (!slotView2.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView2.heroName);
            slotView2.removeHero();
        }
        if (!slotView3.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView3.heroName);
            slotView3.removeHero();
        }
        if (!slotView4.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView4.heroName);
            slotView4.removeHero();
        }
        if (!slotView5.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView5.heroName);
            slotView5.removeHero();
        }
        if (!slotView6.isConfirmed)
        {
            heroSelectionList.unbanHero(slotView6.heroName);
            slotView6.removeHero();
        }
        heroSelectionList.state = "hidden";
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
            setArtSource("qrc:/graphics/Buildings/Seclusion.png");
            setName("Seclusion");
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
            energyDrainAmount1.text = GameApi.base.seclusion.basicCostInEnergy()+"/Day";
            slotsAmount1.text = GameApi.base.seclusion.amountOfSlots();
            activeStressReliefAmount1.text = GameApi.base.seclusion.activeStressRelief()+"/Day";
            convivialStressReliefAmount1.text = GameApi.base.seclusion.convivialStressRelief()+"/Day";
            recluseStressReliefAmount1.text = GameApi.base.seclusion.recluseStressRelief()+"/Day";
            religiousStressReliefAmount1.text = GameApi.base.seclusion.religiousStressRelief()+"/Day";

            if (GameApi.base.seclusion.maxLevelReached())
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
                energyDrainAmount2.text = GameApi.base.seclusion.basicCostInEnergyAfterUpgrade()+"/Day";
                slotsAmount2.text = GameApi.base.seclusion.amountOfSlotsAfterUpgrade();
                activeStressReliefAmount2.text = GameApi.base.seclusion.activeStressReliefAfterUpgrade()+"/Day";
                convivialStressReliefAmount2.text = GameApi.base.seclusion.convivialStressReliefAfterUpgrade()+"/Day";
                recluseStressReliefAmount2.text = GameApi.base.seclusion.recluseStressReliefAfterUpgrade()+"/Day";
                religiousStressReliefAmount2.text = GameApi.base.seclusion.religiousStressReliefAfterUpgrade()+"/Day";
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

            source: "qrc:/graphics/GUI/Energy.png"
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

            source: "qrc:/graphics/GUI/StressRelief.png"
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

            source: "qrc:/graphics/GUI/StressRelief.png"
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

            source: "qrc:/graphics/GUI/StressRelief.png"
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

            source: "qrc:/graphics/GUI/StressRelief.png"
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
            if (GameApi.base.seclusion.maxLevelReached())
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
                energyAmount.text = GameApi.base.seclusion.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.seclusion.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.seclusion.requirementsForNextLevelTime();
                if (GameApi.base.seclusion.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.seclusion.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.seclusion.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.seclusion.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.seclusion.requirementsForNextLevelTime();
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

            source: "qrc:/graphics/GUI/Energy.png"
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

            source: "qrc:/graphics/GUI/Buildingmaterials.png"
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

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 0;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(0,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(0);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }
        BuildingSlotView {
            id: slotView2

            x: 180
            y: slotView1.y

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 1;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(1,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(1);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }
        BuildingSlotView {
            id: slotView3

            x: 360
            y: slotView1.y

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 2;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(2,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(2);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }
        BuildingSlotView {
            id: slotView4

            x: 540
            y: slotView1.y

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 3;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(3,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(3);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }
        BuildingSlotView {
            id: slotView5

            x: 720
            y: slotView1.y

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 4;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(4,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(4);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }
        BuildingSlotView {
            id: slotView6

            x: 900
            y: slotView1.y

            property string heroName

            mode: 0

            onArtClicked: {
                heroSelectionList.updateEverything();
                parent.indexOfChangingSlot = 5;
                heroSelectionList.state = "";
            }

            onStartClicked: {
                GameApi.base.seclusion.placeHeroInSlot(5,heroName);
            }

            onAbortClicked: {
                GameApi.base.seclusion.emptySlot(5);
                heroSelectionList.unbanHero(heroName);
            }

            onRequestUnban: {
                heroSelectionList.unbanHero(heroName);
            }
        }

        HeroesList {
            id: heroSelectionList

            x: 0
            y: 0
            width: parent.width
            height: parent.height - back.height

            state: "hidden"

            onHeroClicked: {
                if (parent.indexOfChangingSlot==0)//COULDDO that's nasty
                {
                    slotView1.heroName=heroName;
                    slotView1.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                else if (parent.indexOfChangingSlot==1)
                {
                    slotView2.heroName=heroName;
                    slotView2.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                else if (parent.indexOfChangingSlot==2)
                {
                    slotView3.heroName=heroName;
                    slotView3.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                else if (parent.indexOfChangingSlot==3)
                {
                    slotView4.heroName=heroName;
                    slotView4.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                else if (parent.indexOfChangingSlot==4)
                {
                    slotView5.heroName=heroName;
                    slotView5.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                else if (parent.indexOfChangingSlot==5)
                {
                    slotView6.heroName=heroName;
                    slotView6.setHeroOneVal("qrc:/graphics/Mercs/"+heroProfession+"/"+heroName,GameApi.base.seclusion.useCostInEnergySingle());
                    state = "hidden";
                }
                heroSelectionList.banHero(heroName);
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
                if (heroSelectionList.state == "hidden")
                {
                    if (!slotView1.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView1.heroName);
                        slotView1.removeHero();
                    }
                    if (!slotView2.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView2.heroName);
                        slotView2.removeHero();
                    }
                    if (!slotView3.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView3.heroName);
                        slotView3.removeHero();
                    }
                    if (!slotView4.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView4.heroName);
                        slotView4.removeHero();
                    }
                    if (!slotView5.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView5.heroName);
                        slotView5.removeHero();
                    }
                    if (!slotView6.isConfirmed)
                    {
                        heroSelectionList.unbanHero(slotView6.heroName);
                        slotView6.removeHero();
                    }
                    backClicked();
                }
                else
                {
                    if (slotsView.indexOfChangingSlot==0)
                        heroSelectionList.banHero(slotView1.heroName);
                    else if (slotsView.indexOfChangingSlot==1)
                        heroSelectionList.banHero(slotView2.heroName);
                    else if (slotsView.indexOfChangingSlot==2)
                        heroSelectionList.banHero(slotView3.heroName);
                    else if (slotsView.indexOfChangingSlot==3)
                        heroSelectionList.banHero(slotView4.heroName);
                    else if (slotsView.indexOfChangingSlot==4)
                        heroSelectionList.banHero(slotView5.heroName);
                    else if (slotsView.indexOfChangingSlot==5)
                        heroSelectionList.banHero(slotView6.heroName);
                    heroSelectionList.state = "hidden";
                }
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
