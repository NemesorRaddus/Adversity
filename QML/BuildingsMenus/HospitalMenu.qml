import QtQuick 2.5

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.hospital.description());
        topBar.setLevel("Level: "+GameApi.base.hospital.currentLevel());
        table.update();
        upgradeInfo.update();
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
            setArtSource("qrc:/graphics/Buildings/Hospital.png");
            setName("Hospital");
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
            energyDrainAmount1.text = GameApi.base.hospital.basicCostInEnergy()+"/Day";
            slotsAmount1.text = GameApi.base.hospital.amountOfSlots();
            energyCostAmount1.text = GameApi.base.hospital.useCostInEnergySingle()+"/Day";
            foodSuppliesCostAmount1.text = GameApi.base.hospital.useCostInFoodSuppliesSingle()+"/Day";
            hpRestoredAmount1.text = GameApi.base.hospital.hpRestoredPerDay()+"/Day";

            if (GameApi.base.hospital.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                slotsAmount2.visible = false;
                energyCostAmount2.visible = false;
                foodSuppliesCostAmount2.visible = false;
                hpRestoredAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.hospital.basicCostInEnergyAfterUpgrade()+"/Day";
                slotsAmount2.text = GameApi.base.hospital.amountOfSlotsAfterUpgrade();
                energyCostAmount2.text = GameApi.base.hospital.useCostInEnergySingleAfterUpgrade()+"/Day";
                foodSuppliesCostAmount2.text = GameApi.base.hospital.useCostInFoodSuppliesSingleAfterUpgrade()+"/Day";
                hpRestoredAmount2.text = GameApi.base.hospital.hpRestoredPerDayAfterUpgrade()+"/Day";
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

            source: "qrc:/graphics/GUI/Energy.png"
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
            id: foodSuppliesCostText

            x: 15
            y: 256

            color: "#94ef94"
            text: "Food cost"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: foodSuppliesCostIcon

            x: 430
            y: 256
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Foodsupplies.png"
        }
        Text {
            id: foodSuppliesCostAmount1

            x: 560
            y: 256
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: foodSuppliesCostAmount2

            x: 860
            y: 256
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: hpRestoredText

            x: 15
            y: 320

            color: "#94ef94"
            text: "Hp restored"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: hpRestoredIcon

            x: 430
            y: 320
            width: 66
            height: width

            source: "qrc:/graphics/GUI/HealthRestored.png"
        }
        Text {
            id: hpRestoredAmount1

            x: 560
            y: 320
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: hpRestoredAmount2

            x: 860
            y: 320
            width: 200

            color: "#94ef94"
            text: "1/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Image {
            id: taskBorderBottom

            x: 17
            y: 400

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
        height: 200

        function update()
        {
            if (GameApi.base.hospital.maxLevelReached())
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
                energyAmount.text = GameApi.base.hospital.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.hospital.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.hospital.requirementsForNextLevelTime();
                if (GameApi.base.hospital.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.hospital.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.hospital.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.hospital.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.hospital.requirementsForNextLevelTime();
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

            onClicked: backClicked()
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
