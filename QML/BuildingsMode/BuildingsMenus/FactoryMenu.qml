import QtQuick 2.5

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()
    signal resourcesUpdateRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.factory.description());
        topBar.setLevel("Level: "+GameApi.base.factory.currentLevel());
        table.update();
        upgradeInfo.update();
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    function returnToDefault()
    {

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
            setArtSource("qrc:/graphics/Buildings/Factory.png");
            setName(GameApi.tr("Factory"));
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
            energyDrainAmount1.text = GameApi.base.factory.basicCostInEnergy()+"/Day";
            maxCyclesAmount1.text = GameApi.base.factory.maxCycles()+"/Day";
            aetheriteUsedAmount1.text = GameApi.base.factory.useCostInAetheriteSingle();
            productionAmount1.text = 0-GameApi.base.factory.productionInBuildingMaterialsSingle();

            cyclesAmount.amount = GameApi.base.factory.currentCycles();
            cyclesAccept.setAnimationDuration(cyclesAmount.amount);

            if (GameApi.base.factory.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                maxCyclesAmount2.visible = false;
                aetheriteUsedAmount2.visible = false;
                productionAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.factory.basicCostInEnergyAfterUpgrade()+"/Day";
                maxCyclesAmount2.text = GameApi.base.factory.maxCyclesAfterUpgrade()+"/Day";
                aetheriteUsedAmount2.text = GameApi.base.factory.useCostInAetheriteSingleAfterUpgrade();
                productionAmount2.text = 0-GameApi.base.factory.productionInBuildingMaterialsSingleAfterUpgrade();
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
            id: maxCyclesText

            x: 15
            y: 128

            color: "#94ef94"
            text: "Cycles Limit"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: maxCyclesIcon

            x: 430
            y: 128
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Settings.png"
        }
        Text {
            id: maxCyclesAmount1

            x: 560
            y: 128
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: maxCyclesAmount2

            x: 860
            y: 128
            width: 200

            color: "#94ef94"
            text: "10/Day"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: aetheriteUsedText

            x: 15
            y: 192

            color: "#94ef94"
            text: "Cost"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: aetheriteUsedIcon

            x: 430
            y: 192
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Aetherite.png"
        }
        Text {
            id: aetheriteUsedAmount1

            x: 640
            y: 192

            color: "#94ef94"
            text: "1"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: aetheriteUsedAmount2

            x: 940
            y: 192

            color: "#94ef94"
            text: "1"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Text {
            id: productionText

            x: 15
            y: 256

            color: "#94ef94"
            text: "Production"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: productionIcon

            x: 430
            y: 256
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Buildingmaterials.png"
        }
        Text {
            id: productionAmount1

            x: 620
            y: 256
            width: 77

            color: "#94ef94"
            text: "10"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: productionAmount2

            x: 920
            y: 256
            width: 77

            color: "#94ef94"
            text: "10"
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
            if (GameApi.base.factory.maxLevelReached())
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
                energyAmount.text = GameApi.base.factory.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.factory.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.factory.requirementsForNextLevelTime();
                if (GameApi.base.factory.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.factory.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.factory.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.factory.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.factory.requirementsForNextLevelTime();
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
        id: productionInfo

        x: 0
        y: upgradeInfo.y + upgradeInfo.height
        width: 1080
        height: 200

        Text {
            id: productionTextBigger

            x: 15
            y: 0

            color: "#94ef94"
            text: "Production: "
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Text {
            id: productionTextSmaller

            x: 15
            y: 95

            color: "#94ef94"
            text: "Cycles done per Day: "
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
            font.family: fontStencil.name
        }

        Text {
            id: cyclesAmount

            property int amount

            x: 660
            y: 65
            width: 120

            color: "#94ef94"
            text: amount
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }

        Item {
            id: cyclesSubtract

            x: 500
            y: 35
            width: 200
            height: width

            Text {
                id: cyclesSubtractMinus

                anchors.fill: parent

                color: "#94ef94"
                text: "-"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 160
                font.family: fontStencil.name
            }

            MouseArea {
                id: cyclesSubtractMA

                anchors.fill: parent

                onClicked: {
                    if (cyclesAmount.amount > 0)
                    {
                        --cyclesAmount.amount;
                    }
                }
            }
        }

        Item {
            id: cyclesAdd

            x: 750
            y: 54
            width: 200
            height: width

            Text {
                id: cyclesAddPlus

                anchors.fill: parent

                color: "#94ef94"
                text: "+"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 120
                font.family: fontStencil.name
            }

            MouseArea {
                id: cyclesAddMA

                anchors.fill: parent

                onClicked: {
                    if (cyclesAmount.amount < GameApi.base.factory.maxCycles())
                    {
                        ++cyclesAmount.amount;
                    }
                }
            }
        }

        Item {
            id: cyclesAccept

            function setAnimationDuration(cycles)
            {
                if (cycles === 0)
                    animation.stop();
                else
                {
                    animation.duration = 4000 - (cycles-1)*800;
                    animation.restart();
                }
            }

            x: 920
            y: 30
            width: 148
            height: width

            Image {
                id: cyclesAcceptImage

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Settings.png"

                RotationAnimator on rotation {
                    id: animation

                    from: 0
                    to: 360
                    duration: 4000
                    loops: RotationAnimation.Infinite
                    running: false
                }
            }

            MouseArea {
                id: cyclesAcceptMA

                anchors.fill: parent

                onClicked: {
                    GameApi.base.factory.setCurrentCycles(cyclesAmount.amount);
                    cyclesAccept.setAnimationDuration(cyclesAmount.amount);
                    resourcesUpdateRequested();
                }
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
                cyclesAmount.amount = GameApi.base.factory.currentCycles();
                backClicked();
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
