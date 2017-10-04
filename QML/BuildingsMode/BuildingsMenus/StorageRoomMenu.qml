import QtQuick 2.9

import Game 1.0
import ".."
import "./EquipmentsList"

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        topBar.setDescription(GameApi.base.storageRoom.description());
        topBar.setLevel("Level: "+GameApi.base.storageRoom.currentLevel());
        table.update();
        upgradeInfo.update();
        equipmentsListCnt.update();
    }

    function reactToBackOnToolbar()
    {
        if (armoury.state == "")
        {
            armoury.state = "hidden";
            return true;
        }
        else
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
            setArtSource("qrc:/graphics/Buildings/StorageRoom.png");
            setName(GameApi.tr("StorageRoom"));
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
            energyDrainAmount1.text = GameApi.base.storageRoom.basicCostInEnergy()+"/Day";
            maxStorageAmount1.text = GameApi.base.storageRoom.buildingMaterialsLimit();

            if (GameApi.base.storageRoom.maxLevelReached())
            {
                levelText3.visible = false;
                energyDrainAmount2.visible = false;
                maxStorageAmount2.visible = false;
            }
            else
            {
                energyDrainAmount2.text = GameApi.base.storageRoom.basicCostInEnergyAfterUpgrade()+"/Day";
                maxStorageAmount2.text = GameApi.base.storageRoom.buildingMaterialsLimitAfterUpgrade();
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
            id: maxStorageText

            x: 15
            y: 128

            color: "#94ef94"
            text: "Max Storage"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Image {
            id: maxStorageIcon

            x: 430
            y: 128
            width: 66
            height: width

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"
        }
        Text {
            id: maxStorageAmount1

            x: 570
            y: 128
            width: 180

            color: "#94ef94"
            text: "10000"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        Text {
            id: maxStorageAmount2

            x: 870
            y: 128
            width: 180

            color: "#94ef94"
            text: "10000"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }

        Image {
            id: taskBorderBottom

            x: 17
            y: 208

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
            if (GameApi.base.storageRoom.maxLevelReached())
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
                energyAmount.text = GameApi.base.storageRoom.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.storageRoom.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.storageRoom.requirementsForNextLevelTime();
                if (GameApi.base.storageRoom.isBeingUpgraded())
                {
                    upgradeButton.markAsUpgraded(true);
                    timeRemaining.time = GameApi.base.storageRoom.upgradeTimeRemaining();
                    timeRemaining.visible = true;
                    timeRemainingIcon.visible = true;
                }
                else
                {
                    upgradeButton.markAsUpgraded(false);
                    timeRemaining.visible = false;
                    timeRemainingIcon.visible = false;
                }
                energyAmount.text = GameApi.base.storageRoom.requirementsForNextLevelEnergy();
                bmAmount.text = GameApi.base.storageRoom.requirementsForNextLevelBM();
                timeAmount.text = GameApi.base.storageRoom.requirementsForNextLevelTime();
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
        id: equipmentsListItem

        x: 0
        y: upgradeInfo.y + upgradeInfo.height + 8

        Text {
            id: equipmentsListText

            x: 15
            y: 0

            color: "#94ef94"
            text: "Owned Equipment:"
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Text {
            id: equipmentsListCnt

            x: 15
            y: 80
            width: root.width

            function update()
            {
                text = GameApi.base.amountOfAvailableWeaponsTools()+" weapons and tools available.\n"+GameApi.base.amountOfAvailableArmors()+" armours and uniforms available.";
            }

            color: "#94ef94"
            font.pixelSize: 50
            font.family: fontStencil.name
        }
    }

    Item {
        id: viewArmoury

        x: 15
        y: equipmentsListItem.y + 200
        width: 500
        height: viewArmouryText.font.pixelSize + 6

        Text {
            id: viewArmouryText

            x: 0
            y: 0

            color: "#94ef94"
            text: "View Armoury >"
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: viewArmouryMA

            anchors.fill: parent

            onClicked: {
                armouryList.update();
                armoury.state = "";
            }
        }
    }

    Image {
        id: backTaskBorder

        x: 17
        y: 1348
        width: 1048
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
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
                if (armoury.state == "")
                    armoury.state = "hidden";
                else
                    backClicked();
            }
        }
    }

    Item {
        id: armoury

        x: 0
        y: 0
        width: parent.width
        height: backTaskBorder.y

        state: "hidden"

        EquipmentsList {
            id: armouryList

            x: 0
            y: 0
            width: parent.width
            height: parent.height
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: armoury; x: width }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
