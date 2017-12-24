import QtQuick 2.9
import Game 1.0

Item {
    id: root

    signal backClicked()
    signal exploreClicked()

    function returnToDefault()
    {
        mercenariesList.state = "hidden";
        equipmentsList.state = "hidden";

        GameApi.base.missions.missionInitializer.setMercenary("");
        GameApi.base.missions.missionInitializer.setArmor("");
        GameApi.base.missions.missionInitializer.setWeaponTool("", 0);
        GameApi.base.missions.missionInitializer.setWeaponTool("", 1);

        GameApi.base.missions.missionInitializer.setAetherite(0);
        GameApi.base.missions.missionInitializer.setEnergy(0);
        GameApi.base.missions.missionInitializer.setBuildingMaterials(0);
        GameApi.base.missions.missionInitializer.setFoodSupplies(0);

        updateDelegate();
        armorArt.source = "qrc:/graphics/GUI/Slots/ArmourSlot.png";
        weapon1Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
        weapon2Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
        weapon1.name = "";
        weapon2.name = "";

        energySetter.text = "0";
        buildingMaterialsSetter.text = "0";
        foodSuppliesSetter.text = "0";

        energySetter.checkAmount();
        buildingMaterialsSetter.checkAmount();
        foodSuppliesSetter.checkAmount();

        warningNotEnoughResourcesText.checkResources();

        forceActiveFocus();
    }

    function reactToBackOnToolbar()
    {
        if (mercenariesList.state == "")
        {
            mercenariesList.state = "hidden";
            return true;
        }
        else if (equipmentsList.state == "")
        {
            equipmentsList.state = "hidden";
            return true;
        }
        else
            return false;
    }

    function updateDelegate()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();
        transitionMercenariesList.duration = transitionMercenariesList.baseDuration * GameApi.animMultiplier();
        transitionEquipmentsList.duration = transitionEquipmentsList.baseDuration * GameApi.animMultiplier();

        if (GameApi.base.missions.missionInitializer.isMercenarySelected())
        {
            delegate.setEmpty(false);

            delegate.setProfession(GameApi.base.missions.missionInitializer.selectedMercenary.professionString());

            var ce=GameApi.base.missions.missionInitializer.selectedMercenary.combatEffectiveness();
            var pr=GameApi.base.missions.missionInitializer.selectedMercenary.proficiency();
            var cl=GameApi.base.missions.missionInitializer.selectedMercenary.cleverness();
            var hp=GameApi.base.missions.missionInitializer.selectedMercenary.health();
            var hpMax=GameApi.base.missions.missionInitializer.selectedMercenary.healthLimit();
            var st=GameApi.base.missions.missionInitializer.selectedMercenary.stress();
            var sr=GameApi.base.missions.missionInitializer.selectedMercenary.stressResistance();
            var sl=GameApi.base.missions.missionInitializer.selectedMercenary.stressLimit();
            var sa=GameApi.base.missions.missionInitializer.selectedMercenary.salary();
            var fc=GameApi.base.missions.missionInitializer.selectedMercenary.dailyFoodConsumption();

            var bce=GameApi.base.missions.missionInitializer.selectedMercenary.baseCombatEffectiveness();
            var bpr=GameApi.base.missions.missionInitializer.selectedMercenary.baseProficiency();
            var bcl=GameApi.base.missions.missionInitializer.selectedMercenary.baseCleverness();
            var bhpMax=GameApi.base.missions.missionInitializer.selectedMercenary.baseHealthLimit();
            var bsr=GameApi.base.missions.missionInitializer.selectedMercenary.baseStressResistance();
            var bsl=GameApi.base.missions.missionInitializer.selectedMercenary.baseStressLimit();
            var bsa=GameApi.base.missions.missionInitializer.selectedMercenary.baseSalary();
            var bfc=GameApi.base.missions.missionInitializer.selectedMercenary.baseDailyFoodConsumption();

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
            delegate.setEmpty(true);
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

    MouseArea {
        id: focusLoser

        anchors.fill: parent

        onClicked: root.forceActiveFocus();
    }

    MercenaryDelegate {
        id: delegate

        x: 0
        y: 50
        width: parent.width
        height: 271

        onOpenListRequested: {
            mercenariesList.update();
            mercenariesList.state = "";
        }
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
        MouseArea {
            id: armorMA

            anchors.fill: parent

            onClicked: {
                equipmentsList.showArmors();
                equipmentsList.state = "";
            }
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
        MouseArea {
            id: weapon1MA

            anchors.fill: parent

            onClicked: {
                equipmentsList.slot=0;
                equipmentsList.showWeaponsTools(weapon2.name);
                equipmentsList.state = "";
            }
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
        MouseArea {
            id: weapon2MA

            anchors.fill: parent

            onClicked: {
                equipmentsList.slot=1;
                equipmentsList.showWeaponsTools(weapon1.name);
                equipmentsList.state = "";
            }
        }
    }

    Item {
        id: energy

        x: armor.x + armor.width + 4
        y: armor.y + armor.height/2 - 45

        Image {
            id: energyIcon

            x: 0
            y: 0
            width: 100
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }
        Text {
            id: warningEnergyText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningEnergyFadeOut.start();
                    warningEnergyBlinking.toRunOrNotToRun=true;
                    warningEnergyBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningEnergyFadeIn.start();
                    warningEnergyBlinking.toRunOrNotToRun=false;
                    warningEnergyBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningEnergyFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningEnergyText
                ]
            }
            NumberAnimation {
                id: warningEnergyFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningEnergyText
                ]
            }
            NumberAnimation {
                id: warningEnergyBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningEnergyText
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
        TextInput {
            id: energySetter

            x: 110
            y: 10
            width: 250
            height: 100

            color: "#94ef94"
            text: "0"
            font.pixelSize: 100
            font.family: fontStencil.name

            function checkAmount()
            {
                if (GameApi.base.missions.missionInitializer.isMercenarySelected())
                {
                    var mindays = 0;
                    if (GameApi.base.missions.missionInitializer.length() == "Short")
                        mindays = 2;
                    else if (GameApi.base.missions.missionInitializer.length() == "Medium")
                        mindays = 6;
                    else if (GameApi.base.missions.missionInitializer.length() == "Long")
                        mindays = 11;
                    else if (GameApi.base.missions.missionInitializer.length() == "Extreme")
                        mindays = 28;

                    var needam = GameApi.base.missions.missionInitializer.selectedMercenary.dailyEquipmentCostEnergy() * mindays;
                    var curam = text*1;
                    if (needam > curam)
                    {
                        warningEnergyText.text = "Tip: at least "+needam+" energy recommended."
                        warningEnergyText.startShowing();
                    }
                    else
                        warningEnergyText.stopShowing();
                }
                else
                    warningEnergyText.stopShowing();

                warningNotEnoughResourcesText.checkResources();
            }

            maximumLength: 3
            validator: RegExpValidator { regExp: /(\d|[1-9]\d+)/}
            inputMethodHints: Qt.ImhDigitsOnly

            onAccepted: {
                root.forceActiveFocus();
            }

            onFocusChanged: {
                if (!focus)
                {
                    if (text=="")
                        text="0";
                    checkAmount();
                    warningNotEnoughResourcesText.checkResources();
                }
            }
        }
    }
    Item {
        id: buildingMaterials

        x: armor.x + armor.width + 4
        y: weapon1.y + weapon1.height/2 - 45

        Image {
            id: buildingMaterialsIcon

            x: -10
            y: -10
            width: 120
            height: width

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"
        }
        Text {
            id: warningBuildingMaterialsText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningBuildingMaterialsFadeOut.start();
                    warningBuildingMaterialsBlinking.toRunOrNotToRun=true;
                    warningBuildingMaterialsBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningBuildingMaterialsFadeIn.start();
                    warningBuildingMaterialsBlinking.toRunOrNotToRun=false;
                    warningBuildingMaterialsBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningBuildingMaterialsFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningBuildingMaterialsText
                ]
            }
            NumberAnimation {
                id: warningBuildingMaterialsFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningBuildingMaterialsText
                ]
            }
            NumberAnimation {
                id: warningBuildingMaterialsBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningBuildingMaterialsText
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
        TextInput {
            id: buildingMaterialsSetter

            x: 110
            y: 10
            width: 250
            height: 100

            color: "#94ef94"
            text: "0"
            font.pixelSize: 100
            font.family: fontStencil.name

            function checkAmount()
            {
                if (GameApi.base.missions.missionInitializer.isMercenarySelected())
                {
                    var mindays = 0;
                    if (GameApi.base.missions.missionInitializer.length() == "Short")
                        mindays = 2;
                    else if (GameApi.base.missions.missionInitializer.length() == "Medium")
                        mindays = 6;
                    else if (GameApi.base.missions.missionInitializer.length() == "Long")
                        mindays = 11;
                    else if (GameApi.base.missions.missionInitializer.length() == "Extreme")
                        mindays = 28;

                    var needam = GameApi.base.missions.missionInitializer.selectedMercenary.dailyEquipmentCostBM() * mindays;
                    var curam = text*1;
                    if (needam > curam)
                    {
                        warningBuildingMaterialsText.text = "Tip: at least "+needam+" materials recommended."
                        warningBuildingMaterialsText.startShowing();
                    }
                    else
                        warningBuildingMaterialsText.stopShowing();
                }
                else
                    warningBuildingMaterialsText.stopShowing();

                warningNotEnoughResourcesText.checkResources();
            }

            maximumLength: 3
            validator: RegExpValidator { regExp: /(\d|[1-9]\d+)/}
            inputMethodHints: Qt.ImhDigitsOnly

            onAccepted: {
                root.forceActiveFocus();
            }

            onFocusChanged: {
                if (!focus)
                {
                    if (text=="")
                        text="0";
                    checkAmount();
                    warningNotEnoughResourcesText.checkResources();
                }
            }
        }
    }
    Item {
        id: foodSupplies

        x: armor.x + armor.width + 4
        y: weapon2.y + weapon2.height/2 - 45

        Image {
            id: foodSuppliesIcon

            x: 0
            y: -5
            width: 110
            height: width

            source: "qrc:/graphics/GUI/Resources/Foodsupplies.png"
        }
        Text {
            id: warningFoodSuppliesText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningFoodSuppliesFadeOut.start();
                    warningFoodSuppliesBlinking.toRunOrNotToRun=true;
                    warningFoodSuppliesBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningFoodSuppliesFadeIn.start();
                    warningFoodSuppliesBlinking.toRunOrNotToRun=false;
                    warningFoodSuppliesBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningFoodSuppliesFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningFoodSuppliesText
                ]
            }
            NumberAnimation {
                id: warningFoodSuppliesFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningFoodSuppliesText
                ]
            }
            NumberAnimation {
                id: warningFoodSuppliesBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningFoodSuppliesText
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
        TextInput {
            id: foodSuppliesSetter

            x: 110
            y: 10
            width: 250
            height: 100

            color: "#94ef94"
            text: "0"
            font.pixelSize: 100
            font.family: fontStencil.name

            function checkAmount()
            {
                if (GameApi.base.missions.missionInitializer.isMercenarySelected())
                {
                    var mindays = 0;
                    if (GameApi.base.missions.missionInitializer.length() == "Short")
                        mindays = 2;
                    else if (GameApi.base.missions.missionInitializer.length() == "Medium")
                        mindays = 6;
                    else if (GameApi.base.missions.missionInitializer.length() == "Long")
                        mindays = 11;
                    else if (GameApi.base.missions.missionInitializer.length() == "Extreme")
                        mindays = 28;

                    var needam = GameApi.base.missions.missionInitializer.selectedMercenary.dailyFoodConsumption() * mindays;
                    var curam = text*1;
                    if (needam > curam)
                    {
                        warningFoodSuppliesText.text = "Tip: at least "+needam+" food recommended."
                        warningFoodSuppliesText.startShowing();
                    }
                    else
                        warningFoodSuppliesText.stopShowing();
                }
                else
                    warningFoodSuppliesText.stopShowing();

                warningNotEnoughResourcesText.checkResources();
            }

            maximumLength: 3
            validator: RegExpValidator { regExp: /(\d|[1-9]\d+)/}
            inputMethodHints: Qt.ImhDigitsOnly

            onAccepted: {
                root.forceActiveFocus();
            }

            onFocusChanged: {
                if (!focus)
                {
                    if (text=="")
                        text="0";
                    checkAmount();
                    warningNotEnoughResourcesText.checkResources();
                }
            }
        }
    }

    Text {
        id: warningNotEnoughResourcesText

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
            if (energySetter.text*1 > GameApi.base.resources.currentEnergyAmount() | buildingMaterialsSetter.text*1 > GameApi.base.resources.currentBuildingMaterialsAmount() | foodSuppliesSetter.text*1 > GameApi.base.resources.currentFoodSuppliesAmount())
                startShowing();
            else
                stopShowing();
        }

        function startShowing()
        {
            if (isShowing == false)
            {
                warningNotEnoughResourcesFadeOut.start();
                warningNotEnoughResourcesBlinking.toRunOrNotToRun=true;
                warningNotEnoughResourcesBlinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                warningNotEnoughResourcesFadeIn.start();
                warningNotEnoughResourcesBlinking.toRunOrNotToRun=false;
                warningNotEnoughResourcesBlinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: warningNotEnoughResourcesFadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: warningNotEnoughResourcesText
        }
        NumberAnimation {
            id: warningNotEnoughResourcesFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: warningNotEnoughResourcesText
        }
        NumberAnimation {
            id: warningNotEnoughResourcesBlinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 2000
            from: 1
            to: 0.5
            targets: warningNotEnoughResourcesText
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
        id: back

        x: 150
        y: parent.height - height
        width: 330
        height: backText.height

        Text {
            id: backText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "< Back"
            font.pixelSize: 100
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

    Item {
        id: explore

        x: 560
        y: back.y - 10
        width: 330
        height: exploreText.height

        visible: true

        Text {
            id: exploreText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "Explore"
            font.pixelSize: 110
            font.family: fontStencil.name
        }
        MouseArea {
            id: exploreMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: {
                GameApi.logger.trace("Explore clicked");
                warningNotEnoughResourcesText.checkResources();
                if (!warningNotEnoughResourcesText.isShowing && GameApi.base.missions.missionInitializer.isMercenarySelected())
                {
                    GameApi.base.missions.missionInitializer.setEnergy(energySetter.text);
                    GameApi.base.missions.missionInitializer.setBuildingMaterials(buildingMaterialsSetter.text);
                    GameApi.base.missions.missionInitializer.setFoodSupplies(foodSuppliesSetter.text);

                    if (GameApi.base.missions.missionInitializer.start())
                        root.exploreClicked();
                }
            }
        }
    }

    MercenariesList {
        id: mercenariesList

        x: 0
        y: 0
        width: root.width
        height: root.height

        state: "hidden"

        onMercenaryClicked: {
            GameApi.base.missions.missionInitializer.setMercenary(GameApi.globalsCpp.alterNormalTextToInternal(mercenaryName));

            if (mercenaryName == "")
            {
                delegate.setName("");
                delegate.setArtSource("qrc:/graphics/GUI/Slots/MercenarySlot.png");
                updateDelegate();
            }
            else
            {
                delegate.setName(mercenaryName);
                delegate.setArtSource(artSource);
                updateDelegate();
            }

            energySetter.checkAmount();
            buildingMaterialsSetter.checkAmount();
            foodSuppliesSetter.checkAmount();

            state = "hidden";
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: mercenariesList; x: width }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionMercenariesList; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
        }
    }

    EquipmentsList {
        id: equipmentsList

        property int slot

        x: 0
        y: 0
        width: root.width
        height: root.height

        state: "hidden"

        onSelected: {
            if (armors)
            {
                if (name == "")
                    armorArt.source = "qrc:/graphics/GUI/Slots/ArmourSlot.png";
                else
                    armorArt.source = artSource;
                GameApi.base.missions.missionInitializer.setArmor(name);
            }
            else
            {
                GameApi.base.missions.missionInitializer.setWeaponTool(name, slot);
                if (slot == 0)
                {
                    if (name == "")
                        weapon1Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                    else
                        weapon1Art.source = artSource;
                    weapon1.name=name;
                }
                else
                {
                    if (name == "")
                        weapon2Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                    else
                        weapon2Art.source = artSource;
                    weapon2.name=name;
                }
            }

            updateDelegate();

            energySetter.checkAmount();
            buildingMaterialsSetter.checkAmount();
            foodSuppliesSetter.checkAmount();

            state = "hidden";
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: equipmentsList; x: width }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionEquipmentsList; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
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
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
