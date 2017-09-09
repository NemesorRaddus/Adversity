import QtQuick 2.9
import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440
    property alias back: back

    signal backClicked()
    signal exploreClicked()

    function returnToDefault()
    {
        updateDelegate();
        armorArt.source = "qrc:/graphics/GUI/Slots/ArmourSlot.png";
        weapon1Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
        weapon2Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
        weapon1.name = "";
        weapon2.name = "";

        predictionNotEnoughResourcesText.checkResources();

        forceActiveFocus();
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    function updateDelegate()
    {
        if (GameApi.base.missionInitializer.isHeroSelected())
        {
            delegate.setEmpty(false);

            delegate.setProfession(GameApi.base.missionInitializer.selectedHero.professionString());

            var ce=GameApi.base.missionInitializer.selectedHero.combatEffectiveness();
            var pr=GameApi.base.missionInitializer.selectedHero.proficiency();
            var cl=GameApi.base.missionInitializer.selectedHero.cleverness();
            var hp=GameApi.base.missionInitializer.selectedHero.health();
            var hpMax=GameApi.base.missionInitializer.selectedHero.healthLimit();
            var st=GameApi.base.missionInitializer.selectedHero.stress();
            var sr=GameApi.base.missionInitializer.selectedHero.stressResistance();
            var sl=GameApi.base.missionInitializer.selectedHero.stressLimit();
            var sa=GameApi.base.missionInitializer.selectedHero.salary();
            var fc=GameApi.base.missionInitializer.selectedHero.dailyFoodConsumption();

            var bce=GameApi.base.missionInitializer.selectedHero.baseCombatEffectiveness();
            var bpr=GameApi.base.missionInitializer.selectedHero.baseProficiency();
            var bcl=GameApi.base.missionInitializer.selectedHero.baseCleverness();
            var bhpMax=GameApi.base.missionInitializer.selectedHero.baseHealthLimit();
            var bsr=GameApi.base.missionInitializer.selectedHero.baseStressResistance();
            var bsl=GameApi.base.missionInitializer.selectedHero.baseStressLimit();
            var bsa=GameApi.base.missionInitializer.selectedHero.baseSalary();
            var bfc=GameApi.base.missionInitializer.selectedHero.baseDailyFoodConsumption();

            delegate.setCE(ce);
            delegate.setPR(pr);
            delegate.setCL(cl);
            delegate.setHP(hp, hpMax);
            delegate.setST(st);
            delegate.setSR(sr);
            delegate.setSL(sl);
            delegate.setSA(sa);
            delegate.setFC(fc);

            if (hpMax == bhpMax)
                delegate.setColorHL("#568b56");
            else if (hpMax > bhpMax)
                delegate.setColorHL("#439b20");
            else
                delegate.setColorHL("#bf0000");

            if (sl == bsl)
                delegate.setColorSL("#568b56");
            else if (sl > bsl)
                delegate.setColorSL("#439b20");
            else
                delegate.setColorSL("#bf0000");

            if (ce == bce)
                delegate.setColorCE("#568b56");
            else if (ce > bce)
                delegate.setColorCE("#439b20");
            else
                delegate.setColorCE("#bf0000");

            if (pr == bpr)
                delegate.setColorPR("#568b56");
            else if (pr > bpr)
                delegate.setColorPR("#439b20");
            else
                delegate.setColorPR("#bf0000");

            if (cl == bcl)
                delegate.setColorCL("#568b56");
            else if (cl > bcl)
                delegate.setColorCL("#439b20");
            else
                delegate.setColorCL("#bf0000");

            if (sr == bsr)
                delegate.setColorSR("#568b56");
            else if (sr > bsr)
                delegate.setColorSR("#bf0000");
            else
                delegate.setColorSR("#439b20");

            if (fc == bfc)
                delegate.setColorFC("#568b56");
            else if (fc > bfc)
                delegate.setColorFC("#bf0000");
            else
                delegate.setColorFC("#439b20");

            if (sa == bsa)
                delegate.setColorSA("#568b56");
            else if (sa > bsa)
                delegate.setColorSA("#bf0000");
            else
                delegate.setColorSA("#439b20");
        }
        else
        {
            delegate.setEmpty(true);
        }
    }

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    Text {
        x: 4
        y: 0

        color: "#94ef94"
        text: "Mercenary:"
        font.pixelSize: 50
        font.family: fontStencil.name
    }

    HeroDelegate {
        id: delegate

        x: 0
        y: 50
        width: parent.width
        height: 271
    }

    Text {
        x: 520
        y: 322

        color: "#94ef94"
        text: "Equipment:"
        font.pixelSize: 50
        font.family: fontStencil.name
    }

    Item {
        id: armor

        x: 4
        y: delegate.y + delegate.height + 4
        width: 260
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: armorArt

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/Slots/ArmourSlot.png"
        }
    }
    Item {
        id: weapon1

        x: armor.x
        y: armor.y + armor.height + 4
        width: 260
        height: width

        property string name: ""

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: weapon1Art

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/Slots/ToolSlot.png"
        }
    }
    Item {
        id: weapon2

        x: weapon1.x
        y: weapon1.y + weapon1.height + 4
        width: weapon1.width
        height: width

        property string name: ""

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: weapon2Art

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/Slots/ToolSlot.png"
        }
    }

    Item {
        id: energy

        x: armor.x + armor.width + 4
        y: (armor.y + armor.height/2 + 80)*0.75

        Image {
            id: energyIcon

            x: 0
            y: 0
            width: 100
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }
        Text {
            id: predictionEnergyText

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            text: "Energy will probably run out after 10 days."
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Item {
        id: buildingMaterials

        x: armor.x + armor.width + 4
        y: (weapon1.y + weapon1.height/2 + 80)*0.75

        Image {
            id: buildingMaterialsIcon

            x: -10
            y: -10
            width: 120
            height: width

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"
        }
        Text {
            id: predictionBuildingMaterialsText

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            text: "Materials will probably run out after 10 days."
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Item {
        id: foodSupplies

        x: armor.x + armor.width + 4
        y: (weapon2.y + weapon2.height/2 + 80)*0.75

        Image {
            id: foodSuppliesIcon

            x: 0
            y: -5
            width: 110
            height: width

            source: "qrc:/graphics/GUI/Resources/Foodsupplies.png"
        }
        Text {
            id: predictionFoodSuppliesText

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            text: "Food will probably run out after 10 days."
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Item {
        id: aetherite

        x: armor.x + armor.width + 4
        y: 2*foodSupplies.y-buildingMaterials.y

        Image {
            id: aetheriteIcon

            x: 0
            y: -5
            width: 110
            height: width

            source: "qrc:/graphics/GUI/Resources/Aetherite.png"
        }
        Text {
            id: predictionAetheriteText

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Text {
        id: predictionNotEnoughResourcesText

        property bool isShowing: false

        x: 0
        y: 1240
        width: root.width

        opacity: 0

        color: "#a00000"
        text: "You don't have enough resources!"
        wrapMode: Text.WordWrap
        font.pixelSize: 55
        font.family: fontStencil.name
        horizontalAlignment: Text.AlignHCenter

        function checkResources()
        {
            if (energySetter.text*1 > GameApi.base.currentEnergyAmount() | buildingMaterialsSetter.text*1 > GameApi.base.currentBuildingMaterialsAmount() | foodSuppliesSetter.text*1 > GameApi.base.currentFoodSuppliesAmount())
                startShowing();
            else
                stopShowing();
        }

        function startShowing()
        {
            if (isShowing == false)
            {
                predictionNotEnoughResourcesFadeOut.start();
                predictionNotEnoughResourcesBlinking.toRunOrNotToRun=true;
                predictionNotEnoughResourcesBlinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                predictionNotEnoughResourcesFadeIn.start();
                predictionNotEnoughResourcesBlinking.toRunOrNotToRun=false;
                predictionNotEnoughResourcesBlinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: predictionNotEnoughResourcesFadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: [
                predictionNotEnoughResourcesText
            ]
        }
        NumberAnimation {
            id: predictionNotEnoughResourcesFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: [
                predictionNotEnoughResourcesText
            ]
        }
        NumberAnimation {
            id: predictionNotEnoughResourcesBlinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 2000
            from: 1
            to: 0.5
            targets: [
                predictionNotEnoughResourcesText
            ]
            onRunningChanged: {
                if (running == false && toRunOrNotToRun == true)
                {
                    if (from == 1)
                    {
                        from = 0.5;
                        to = 1;
                    }
                    else
                    {
                        from = 1;
                        to = 0.5;
                    }

                    running = true;
                }
            }
        }
    }

    Item {
        id: equipment
        x: 20
        y: 1150
        width: parent.width-2*x
        height: 130

        Item {
            id: eq1

            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: eq2

            x: 180
            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: eq3

            x: 360
            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: eq4

            x: 540
            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: eq5

            x: 720
            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: eq6

            x: 900
            width: height
            height: parent.height

            Image {
                anchors.fill: parent

                source: "qrc:/graphics/GUI/Task_Picture2.png"
            }
            Image {
                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2

                source: "qrc:/graphics/Equipment/WeaponTool/Tier_3/UEGArsonistFlameThrower.png"
            }
            MouseArea {
                anchors.fill: parent
            }
        }
    }

    Item {
        id: back

        x: (parent.width-width)/2
        y: parent.height - height
        width: 199
        height: backText.height

        Text {
            id: backText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "< Back"
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: backMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: {
                root.returnToDefault();
                root.backClicked();
            }
        }
    }

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        },
        State {
            name: "hiddenRight2"
            PropertyChanges { target: root; x: 2*width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
