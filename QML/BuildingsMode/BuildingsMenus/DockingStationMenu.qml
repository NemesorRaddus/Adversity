import QtQuick 2.5

import Game 1.0
import ".."
import "./DockingStationSubmenus"

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()
    signal resourcesUpdateRequested()
    signal heroesModeUpdateRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.dockingStation.description());
        topBar.setLevel("Level: "+GameApi.base.dockingStation.currentLevel());
        table.update();
        upgradeInfo.update();
        tabs.update();
    }

    function reactToBackOnToolbar()
    {
        returnToDefault();
        return false;
    }

    function returnToDefault()
    {
        tabs.returnToDefault();
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
            setArtSource("qrc:/graphics/Buildings/DockingStation.png");
            setName(GameApi.tr("DockingStation"));
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
            energyDrainAmount1.text = GameApi.base.dockingStation.basicCostInEnergy()+"/Day";
            waitingTimeAmount1.text = GameApi.base.dockingStation.waitingTime();
            recruitsAmount1.text = GameApi.base.dockingStation.recruitsAmount()+"/Week";
            profitabilityAmount1.text = GameApi.base.dockingStation.profitability();
            equipmentAmount1.text = GameApi.base.dockingStation.equipmentsAmount()+"/Day";
            maxTierAmount1.text = GameApi.base.dockingStation.maxTier();

            if (GameApi.base.dockingStation.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                waitingTimeAmount2.visible = false;
                recruitsAmount2.visible = false;
                profitabilityAmount2.visible = false;
                equipmentAmount2.visible = false;
                maxTierAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.dockingStation.basicCostInEnergyAfterUpgrade()+"/Day";
                waitingTimeAmount2.text = GameApi.base.dockingStation.waitingTimeAfterUpgrade();
                recruitsAmount2.text = GameApi.base.dockingStation.recruitsAmountAfterUpgrade()+"/Day";
                profitabilityAmount2.text = GameApi.base.dockingStation.profitabilityAfterUpgrade();
                equipmentAmount2.text = GameApi.base.dockingStation.equipmentsAmountAfterUpgrade()+"/Day";
                maxTierAmount2.text = GameApi.base.dockingStation.maxTierAfterUpgrade();
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

        Item {
            id: energyDrain

            anchors.fill: parent

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
        }

        Item {
            id: waitingTime

            anchors.fill: parent

            Text {
                id: waitingTimeText

                x: 15
                y: 128

                color: "#94ef94"
                text: "Delivery"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Image {
                id: waitingTimeIcon

                x: 430
                y: 128
                width: 66
                height: width

                source: "qrc:/graphics/GUI/Time.png"
            }
            Text {
                id: waitingTimeAmount1

                x: 560
                y: 128
                width: 200

                color: "#94ef94"
                text: "10"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Text {
                id: waitingTimeAmount2

                x: 860
                y: 128
                width: 200

                color: "#94ef94"
                text: "10"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
        }

        Item {
            id: recruits

            anchors.fill: parent

            Text {
                id: recruitsText

                x: 15
                y: 192

                color: "#94ef94"
                text: "Recruits"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Image {
                id: recruitsIcon

                x: 430
                y: 192
                width: 66
                height: width

                source: "qrc:/graphics/GUI/Slots.png"
            }
            Text {
                id: recruitsAmount1

                x: 560
                y: 192
                width: 200

                color: "#94ef94"
                text: "1/Week"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Text {
                id: recruitsAmount2

                x: 860
                y: 192
                width: 200

                color: "#94ef94"
                text: "1/Day"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
        }

        Item {
            id: profitability

            anchors.fill: parent

            visible: false

            Text {
                id: profitabilityText

                x: 15
                y: 192

                color: "#94ef94"
                text: "Trade level"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Image {
                id: profitabilityIcon

                x: 430
                y: 192
                width: 66
                height: width

                source: "qrc:/graphics/GUI/Profitability.png"
            }
            Text {
                id: profitabilityAmount1

                x: 560
                y: 192
                width: 200

                color: "#94ef94"
                text: "1"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Text {
                id: profitabilityAmount2

                x: 860
                y: 192
                width: 200

                color: "#94ef94"
                text: "1"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
        }

        Item {
            id: equipment

            anchors.fill: parent

            visible: false

            Text {
                id: equipmentText

                x: 15
                y: 192

                color: "#94ef94"
                text: "Equipments"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Image {
                id: equipmentIcon

                x: 430
                y: 192
                width: 66
                height: width

                source: "qrc:/graphics/GUI/EquipmentAmount.png"
            }
            Text {
                id: equipmentAmount1

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
                id: equipmentAmount2

                x: 860
                y: 192
                width: 200

                color: "#94ef94"
                text: "1/Day"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
        }

        Item {
            id: maxTier

            anchors.fill: parent

            visible: false

            Text {
                id: maxTierText

                x: 15
                y: 256

                color: "#94ef94"
                text: "Max tier"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Image {
                id: maxTierIcon

                x: 430
                y: 256
                width: 66
                height: width

                source: "qrc:/graphics/GUI/Profitability.png"
            }
            Text {
                id: maxTierAmount1

                x: 560
                y: 256
                width: 200

                color: "#94ef94"
                text: "1"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
            Text {
                id: maxTierAmount2

                x: 860
                y: 256
                width: 200

                color: "#94ef94"
                text: "1"
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 60
                font.family: fontStencil.name
            }
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
            if (GameApi.base.dockingStation.maxLevelReached())
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
                energyAmount.text = GameApi.base.dockingStation.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.dockingStation.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.dockingStation.requirementsForNextLevelTime();
                if (GameApi.base.dockingStation.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.dockingStation.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.dockingStation.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.dockingStation.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.dockingStation.requirementsForNextLevelTime();
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
        id: tabs

        x: 0
        y: upgradeInfo.y + upgradeInfo.height
        width: parent.theoreticalWidth
        height: back.y - y

        function update()
        {
            heroesTab.update();
            resourcesTab.update();
            equipmentsTab.update();
        }

        function returnToDefault()
        {
            heroesTab.returnToDefault();
            resourcesTab.returnToDefault();
            equipmentsTab.returnToDefault();

            heroesTab.state = "";
            resourcesTab.state = "hiddenRight";
            equipmentsTab.state = "hiddenRight2";

            recruits.visible = true;
            profitability.visible = false;
            equipment.visible = false;
            maxTier.visible = false;
        }

        HeroesTab {
            id: heroesTab

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            onRequestSwitchingToResourcesTab: {
                recruits.visible = false;
                profitability.visible = true;
                state = "hiddenLeft";
                resourcesTab.state = "";
                equipment.state = "hiddenRight";
            }

            onRequestUpdate: heroesModeUpdateRequested()
        }
        ResourcesTab {
            id: resourcesTab

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            onRequestSwitchingToHeroesTab: {
                recruits.visible = true;
                profitability.visible = false;
                equipment.visible = false;
                maxTier.visible = false;
                state = "hiddenRight";
                heroesTab.state = "";
                equipmentsTab.state = "hiddenRight2";
            }

            onRequestSwitchingToEquipmentTab: {
                recruits.visible = false;
                profitability.visible = false;
                equipment.visible = true;
                maxTier.visible = true;
                state = "hiddenLeft";
                equipmentsTab.state = "";
                heroesTab.state = "hiddenLeft2";
            }

            onRequestResourcesUpdate: root.resourcesUpdateRequested()
        }
        EquipmentsTab {
            id: equipmentsTab

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            onRequestSwitchingToResourcesTab: {
                profitability.visible = true;
                equipment.visible = false;
                maxTier.visible = false;
                state = "hiddenRight";
                resourcesTab.state = "";
                heroesTab.state = "hiddenLeft";
            }

            onRequestResourcesUpdate: root.resourcesUpdateRequested()
        }

        Component.onCompleted: {
            recruits.visible = true;
            equipment.visible = false;
            maxTier.visible = false;
            resourcesTab.state = "hiddenRight";
            heroesTab.state = "";
            equipmentsTab.state = "hiddenRight2";
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
                tabs.returnToDefault();
                backClicked()
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
