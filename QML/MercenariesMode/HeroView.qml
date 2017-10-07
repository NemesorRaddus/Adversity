import QtQuick 2.9

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    property string heroName
    property string currentActivity_
    property bool dismissConfirmDialogVisible: false
    property bool artPreviewVisible: false

    signal backClicked()
    signal upgradeRequested()
    signal buildingMenuRequested(string buildingName)
    signal dismissClicked()
    signal unbanRequested(string heroName_, string buildingName)
    signal guiUpdateRequested()
    signal artPreviewRequested(string artSource)

    function setMercenary(name)
    {
        if (name != "" && name != undefined)
        {
            for (var i=0;i<GameApi.base.heroes.amountOfHeroes();++i)
            {
                GameApi.base.heroes.prepareHeroAt(i);
                if (GameApi.base.heroes.preparedHero.name() == name)
                {
                    heroName=name;
                    if (GameApi.base.heroes.preparedHero.isCommunicationAvailable())
                    {
                        topBar.setArtSource(GameApi.base.heroes.preparedHero.pathToArt());
                        topBar.setName(GameApi.base.heroes.preparedHero.name());
                        topBar.setProfession(GameApi.base.heroes.preparedHero.professionString());
                        topBar.setCE(GameApi.base.heroes.preparedHero.combatEffectiveness());
                        topBar.setPR(GameApi.base.heroes.preparedHero.proficiency());
                        topBar.setCL(GameApi.base.heroes.preparedHero.cleverness());
                        topBar.setHP(GameApi.base.heroes.preparedHero.health(), GameApi.base.heroes.preparedHero.healthLimit());
                        topBar.setST(GameApi.base.heroes.preparedHero.stress(), GameApi.base.heroes.preparedHero.stressLimit());
                        topBar.setSR(GameApi.base.heroes.preparedHero.stressResistance());
                        topBar.setDSR(GameApi.base.heroes.preparedHero.dailyStressRecovery());
                        topBar.setDHR(GameApi.base.heroes.preparedHero.dailyHealthRecovery());
                        topBar.setDFC(GameApi.base.heroes.preparedHero.dailyFoodConsumption());
                        topBar.setSA(GameApi.base.heroes.preparedHero.salary())
                        topBar.setNature(GameApi.base.heroes.preparedHero.natureString());

                        if (GameApi.base.heroes.preparedHero.healthLimit() == GameApi.base.heroes.preparedHero.baseHealthLimit())
                            topBar.setColorHL("#568b56");
                        else if (GameApi.base.heroes.preparedHero.healthLimit() > GameApi.base.heroes.preparedHero.baseHealthLimit())
                            topBar.setColorHL("#439b20");
                        else
                            topBar.setColorHL("#bf0000");

                        if (GameApi.base.heroes.preparedHero.stressLimit() == GameApi.base.heroes.preparedHero.baseStressLimit())
                            topBar.setColorSL("#568b56");
                        else if (GameApi.base.heroes.preparedHero.stressLimit() > GameApi.base.heroes.preparedHero.baseStressLimit())
                            topBar.setColorSL("#439b20");
                        else
                            topBar.setColorSL("#bf0000");

                        if (GameApi.base.heroes.preparedHero.combatEffectiveness() == GameApi.base.heroes.preparedHero.baseCombatEffectiveness())
                            topBar.setColorCE("#568b56");
                        else if (GameApi.base.heroes.preparedHero.combatEffectiveness() > GameApi.base.heroes.preparedHero.baseCombatEffectiveness())
                            topBar.setColorCE("#439b20");
                        else
                            topBar.setColorCE("#bf0000");

                        if (GameApi.base.heroes.preparedHero.proficiency() == GameApi.base.heroes.preparedHero.baseProficiency())
                            topBar.setColorPR("#568b56");
                        else if (GameApi.base.heroes.preparedHero.proficiency() > GameApi.base.heroes.preparedHero.baseProficiency())
                            topBar.setColorPR("#439b20");
                        else
                            topBar.setColorPR("#bf0000");

                        if (GameApi.base.heroes.preparedHero.cleverness() == GameApi.base.heroes.preparedHero.baseCleverness())
                            topBar.setColorCL("#568b56");
                        else if (GameApi.base.heroes.preparedHero.cleverness() > GameApi.base.heroes.preparedHero.baseCleverness())
                            topBar.setColorCL("#439b20");
                        else
                            topBar.setColorCL("#bf0000");

                        if (GameApi.base.heroes.preparedHero.stressResistance() == GameApi.base.heroes.preparedHero.baseStressResistance())
                            topBar.setColorSR("#568b56");
                        else if (GameApi.base.heroes.preparedHero.stressResistance() > GameApi.base.heroes.preparedHero.baseStressResistance())
                            topBar.setColorSR("#bf0000");
                        else
                            topBar.setColorSR("#439b20");

                        if (GameApi.base.heroes.preparedHero.dailyStressRecovery() == GameApi.base.heroes.preparedHero.baseDailyStressRecovery())
                            topBar.setColorDSR("#568b56");
                        else if (GameApi.base.heroes.preparedHero.dailyStressRecovery() > GameApi.base.heroes.preparedHero.baseDailyStressRecovery())
                            topBar.setColorDSR("#439b20");
                        else
                            topBar.setColorDSR("#bf0000");

                        if (GameApi.base.heroes.preparedHero.dailyHealthRecovery() == GameApi.base.heroes.preparedHero.baseDailyHealthRecovery())
                            topBar.setColorDHR("#568b56");
                        else if (GameApi.base.heroes.preparedHero.dailyHealthRecovery() > GameApi.base.heroes.preparedHero.baseDailyHealthRecovery())
                            topBar.setColorDHR("#439b20");
                        else
                            topBar.setColorDHR("#bf0000");

                        if (GameApi.base.heroes.preparedHero.dailyFoodConsumption() == GameApi.base.heroes.preparedHero.baseDailyFoodConsumption())
                            topBar.setColorDFC("#568b56");
                        else if (GameApi.base.heroes.preparedHero.dailyFoodConsumption() > GameApi.base.heroes.preparedHero.baseDailyFoodConsumption())
                            topBar.setColorDFC("#bf0000");
                        else
                            topBar.setColorDFC("#439b20");

                        if (GameApi.base.heroes.preparedHero.salary() == GameApi.base.heroes.preparedHero.baseSalary())
                            topBar.setColorSA("#568b56");
                        else if (GameApi.base.heroes.preparedHero.salary() > GameApi.base.heroes.preparedHero.baseSalary())
                            topBar.setColorSA("#bf0000");
                        else
                            topBar.setColorSA("#439b20");

                        currentActivity_=GameApi.base.heroes.preparedHero.currentActivityString();
                        topBar.setCurrentActivity(currentActivity_);
                        currentActivity.setCurrentActivity(currentActivity_);

                        if (GameApi.base.heroes.preparedHero.isImmuneToStress())
                            stressBorderEffect.setImmunity();
                        else
                        {
                            if (GameApi.base.heroes.preparedHero.isStressBorderEffectActive())
                                stressBorderEffect.setCurrentSBE(GameApi.base.heroes.preparedHero.currentStressBorderEffectNameString());
                            else
                                stressBorderEffect.setNoCurrentSBE();
                        }
                    }
                    else
                    {
                        topBar.setArtSource(GameApi.base.heroes.preparedHero.pathToArt());
                        topBar.setName(GameApi.base.heroes.preparedHero.name());
                        topBar.setProfession(GameApi.base.heroes.preparedHero.professionString());
                        topBar.setMIA();

                        topBar.setColorHL("#568b56");
                        topBar.setColorSL("#568b56");
                        topBar.setColorCE("#568b56");
                        topBar.setColorPR("#568b56");
                        topBar.setColorCL("#568b56");
                        topBar.setColorSR("#568b56");
                        topBar.setColorDSR("#568b56");
                        topBar.setColorDHR("#568b56");
                        topBar.setColorDFC("#568b56");
                        topBar.setColorSA("#568b56");

                        currentActivity_="On Mission";
                        currentActivity.setCurrentActivity(currentActivity_);

                        stressBorderEffect.setMIA();
                    }
                    break;
                }
            }
        }
    }
    function dismissMercenary()
    {
        dismissConfirmDialogVisible = false;
        GameApi.base.heroes.dismissHero(heroName);
        if (currentActivity_ == "In Hospital")
            unbanRequested(heroName, "Hospital");
        else if (currentActivity_ == "On Training Ground")
            unbanRequested(heroName, "Training Ground");
        else if (currentActivity_ == "In Gym")
            unbanRequested(heroName, "Gym");
        else if (currentActivity_ == "In Laboratory")
            unbanRequested(heroName, "Laboratory");
        else if (currentActivity_ == "In Playing Field")
            unbanRequested(heroName, "Playing Field");
        else if (currentActivity_ == "In Bar")
            unbanRequested(heroName, "Bar");
        else if (currentActivity_ == "In Shrine")
            unbanRequested(heroName, "Shrine");
        else if (currentActivity_ == "In Seclusion")
            unbanRequested(heroName, "Seclusion");
        guiUpdateRequested();
    }

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        setMercenary(heroName);
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    width: 1080
    height: 1464

    onStateChanged: {
        if (state == "")
        {
            artPreviewMA.enabled = true;
            dismissButtonMA.enabled = true;
            backButton.enabled = true;
        }
        else
        {
            artPreviewMA.enabled = false;
            dismissButtonMA.enabled = false;
            backButton.enabled = false;
        }
    }

    Item {
        id: topBar

        width: 1080
        height: itemBorder.y + itemBorder.height

        function setArtSource(source)
        {
            art.source = source;
        }

        function setName(text)
        {
            name.text = GameApi.tr(text);
        }

        function setProfession(text)
        {
            prof.text="The "+GameApi.tr(text);
        }

        function setMIA()
        {
            attrCEValue.text = "?";
            attrPRValue.text = "?";
            attrCLValue.text = "?";
            attrHPValue.text = "?/?";
            attrSTValue.text = "?/?";
            attrSRValue.text = "?";
            attrDSRValue.text = "?";
            attrDHRValue.text = "?";
            attrSAValue.text = "?";
            attrDFCValue.text = "?";

            natureValue.text = "?";

            statusHPFrame.source = "";
            statusSTFrame.source = "";

            currentlyBusy.source = "qrc:/graphics/GUI/Disconnected.png";
        }

        function setCE(amount)
        {
            attrCEValue.text = amount;
        }

        function setPR(amount)
        {
            attrPRValue.text = amount;
        }

        function setCL(amount)
        {
            attrCLValue.text = amount;
        }

        function setHP(current, max)
        {
            attrHPValue.text = current+'/'+max;
            statusHPFrame.check(current,max);
        }

        function setST(st,sl)
        {
            if (sl==-1)
            {
                attrSTValue.text = "N/A";
            }
            else
            {
                attrSTValue.text = st+"/"+sl;
                statusSTFrame.check(st,sl);
            }
        }

        function setSR(amount)
        {
            attrSRValue.text = Math.floor(amount)+"."+Math.round(amount*100);
        }

        function setDSR(amount)
        {
            attrDSRValue.text = amount+"/Day";
        }

        function setDHR(amount)
        {
            attrDHRValue.text = amount+"/Day";
        }

        function setDFC(amount)
        {
            attrDFCValue.text = amount+"/Day";
        }

        function setSA(amount)
        {
            attrSAValue.text = amount+"/Week";
        }

        function setColorCE(col)
        {
            attrCEValue.color = col;
        }

        function setColorPR(col)
        {
            attrPRValue.color = col;
        }

        function setColorCL(col)
        {
            attrCLValue.color = col;
        }

        function setColorHL(col)
        {
            attrHPValue.color = col;
        }

        function setColorSL(col)
        {
            attrSTValue.color = col;
        }

        function setColorSR(col)
        {
            attrSRValue.color = col;
        }

        function setColorDSR(col)
        {
            attrDSRValue.color = col;
        }

        function setColorDHR(col)
        {
            attrDHRValue.color = col;
        }

        function setColorDFC(col)
        {
            attrDFCValue.color = col;
        }

        function setColorSA(col)
        {
            attrSAValue.color = col;
        }

        function setNature(nat)
        {
            natureValue.text = nat;
        }

        function setCurrentActivity(ca)
        {
            if (ca == "Idle")
                currentlyBusy.source = "";
            else if (ca == "On Mission")
                currentlyBusy.source = "qrc:/graphics/GUI/OnMission.png";
            else if (ca == "In Hospital")
                currentlyBusy.source = "qrc:/graphics/Buildings/Hospital.png";
            else if (ca == "On Training Ground")
                currentlyBusy.source = "qrc:/graphics/Buildings/TrainingGround.png";
            else if (ca == "In Gym")
                currentlyBusy.source = "qrc:/graphics/Buildings/Gym.png";
            else if (ca == "In Laboratory")
                currentlyBusy.source = "qrc:/graphics/Buildings/Laboratory.png";
            else if (ca == "In Playing Field")
                currentlyBusy.source = "qrc:/graphics/Buildings/PlayingField.png";
            else if (ca == "In Bar")
                currentlyBusy.source = "qrc:/graphics/Buildings/Bar.png";
            else if (ca == "In Shrine")
                currentlyBusy.source = "qrc:/graphics/Buildings/Shrine.png";
            else if (ca == "In Seclusion")
                currentlyBusy.source = "qrc:/graphics/Buildings/Seclusion.png";
            else if (ca == "Arriving")
                currentlyBusy.source = "qrc:/graphics/Buildings/DockingStation.png";
            else
                currentlyBusy.source = "";
        }

        function getName()
        {
            return name;
        }

        function getProfession()
        {
            return prof;
        }

        Image {
            id: itemBorder
            x: 17
            y: natureText.y + natureText.height + 12
            width: 1048
            height: 3
            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Item {
            id: artSegment

            x: 17
            y: 0
            width: 262
            height: 262

            Image {
                id: art
                x: 3
                y: 3
                width: 256
                height: 256
            }

            Image {
                id: frame
                x: 0
                y: 0
                width: 262
                height: 262
                source: "qrc:/graphics/GUI/Task_Picture.png"
            }

            Image {
                id: statusHPFrame
                x: 3
                y: 3
                width: 256
                height: 256

                function check(hp, hpMax)
                {
                    if (hp/hpMax <= 0.2)
                        source = "qrc:/graphics/GUI/Status frames/LowHealth80.png";
                    else if (hp/hpMax <= 0.4)
                        source = "qrc:/graphics/GUI/Status frames/LowHealth60.png";
                    else if (hp/hpMax <= 0.6)
                        source = "qrc:/graphics/GUI/Status frames/LowHealth40.png";
                    else if (hp/hpMax <= 0.8)
                        source = "qrc:/graphics/GUI/Status frames/LowHealth20.png";
                    else
                        source = "";
                }

                NumberAnimation {
                    id: animHP
                    from: 0;
                    to: 1;

                    onRunningChanged: {
                        if (running == false)
                        {
                            if (from == 0)
                            {
                                from = 1;
                                to = 0;
                                running = true;
                            }
                            else
                            {
                                from = 0;
                                to = 1;
                                running = true;
                            }
                        }
                    }

                    duration: 1500
                    target: statusHPFrame
                    property: "opacity"
                    running: true
                }
            }

            Image {
                id: statusSTFrame
                x: 3
                y: 3
                width: 256
                height: 256

                function check(stress, stressLimit)
                {
                    if (stress/stressLimit >= 0.8)
                        source = "qrc:/graphics/GUI/Status frames/HighStress80.png";
                    else if (stress/stressLimit >= 0.6)
                        source = "qrc:/graphics/GUI/Status frames/HighStress60.png";
                    else if (stress/stressLimit >= 0.4)
                        source = "qrc:/graphics/GUI/Status frames/HighStress40.png";
                    else if (stress/stressLimit >= 0.2)
                        source = "qrc:/graphics/GUI/Status frames/HighStress20.png";
                    else
                        source = "";
                }

                NumberAnimation {
                    id: animST
                    from: 0;
                    to: 1;

                    onRunningChanged: {
                        if (running == false)
                        {
                            if (from == 0)
                            {
                                from = 1;
                                to = 0;
                                running = true;
                            }
                            else
                            {
                                from = 0;
                                to = 1;
                                running = true;
                            }
                        }
                    }

                    duration: 1500
                    target: statusSTFrame
                    property: "opacity"
                    running: true
                }
            }

            MouseArea {
                id: artPreviewMA

                anchors.fill: parent

                onClicked: {
                    root.artPreviewVisible = true;
                    root.artPreviewRequested(art.source);
                }
            }
        }

        Item {
            id: textSegment
            x: 280
            y: 10
            width: 785
            height: 249

            Text {
                id: name
                x: 0
                y: -6
                color: "#94ef94"
                text: "Marek Jakubowski"
                font.pixelSize: 60
                font.family: fontStencil.name
            }

            Text {
                id: prof
                x: 0
                y: 45
                color: "#94ef94"
                text: "The Bounty Hunter"
                font.pixelSize: 45
                font.family: fontStencil.name
            }

            Image {
                id: attrHPIcon
                x: 8
                y: 105
                width: 50
                height: 50
                source: "qrc:/graphics/GUI/Attributes/HealthRestored.png"
            }
            Text {
                id: attrHPText
                x: 69
                y: 109
                width: 200
                height: font.pixelSize + 6
                color: "#568b56"
                text: "Health: "
                font.pixelSize: 56
                font.family: fontStencil.name
            }
            Text {
                id: attrHPValue
                x: 350
                y: attrHPText.y
                width: 140
                height: font.pixelSize + 6
                color: "#568b56"
                text: "99/99"
                font.pixelSize: 56
                font.family: fontStencil.name
            }

            Image {
                id: attrSTIcon
                x: 8
                y: 167
                width: 50
                height: 50
                source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
            }
            Text {
                id: attrSTText
                x: attrHPText.x
                y: 171
                width: 200
                height: font.pixelSize+6
                color: "#568b56"
                text: "Stress:"
                font.pixelSize: 56
                font.family: fontStencil.name
            }
            Text {
                id: attrSTValue
                x: attrHPValue.x
                y: attrSTText.y
                width: 250
                height: font.pixelSize+6
                color: "#568b56"
                text: "666/666"
                font.pixelSize: 56
                font.family: fontStencil.name
            }

            Image {
                id: attrCEIcon
                x: -264
                y: 269
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Attributes/CE.png"
            }
            Text {
                id: attrCEText
                x: -206
                y: 274
                width: 620
                height: font.pixelSize+6
                color: "#568b56"
                text: "Combat Effectiveness: "
                font.pixelSize: 50
                font.family: fontStencil.name
            }
            Text {
                id: attrCEValue
                x: 500
                y: attrCEText.y
                width: 250
                height: font.pixelSize+6
                color: "#568b56"
                text: "99"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrPRIcon
                x: attrCEIcon.x
                y: attrCEIcon.y + attrCEText.height
                width: attrCEIcon.width
                height: width
                source: "qrc:/graphics/GUI/Attributes/PR.png"
            }
            Text {
                id: attrPRText
                x: attrCEText.x
                y: attrCEText.y + attrCEText.height
                width: 350
                height: font.pixelSize+6
                color: "#568b56"
                text: "Proficiency: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrPRValue
                x: attrCEValue.x
                y: attrPRText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "99"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrCLIcon
                x: attrPRIcon.x
                y: attrPRIcon.y + attrPRText.height
                width: attrPRIcon.width
                height: width
                source: "qrc:/graphics/GUI/Attributes/CL.png"
            }
            Text {
                id: attrCLText
                x: attrPRText.x
                y: attrPRText.y + attrPRText.height
                width: 340
                height: font.pixelSize+6
                color: "#568b56"
                text: "Cleverness: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrCLValue
                x: attrCEValue.x
                y: attrCLText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "99"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrSRIcon
                x: attrCLIcon.x
                y: attrCLIcon.y + attrCLText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Attributes/StressResistance.png"
            }
            Text {
                id: attrSRText
                x: attrCLText.x
                y: attrCLText.y + attrCLText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Stress Resistance: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrSRValue
                x: attrCEValue.x
                y: attrSRText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "9.9"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
                maximumLineCount: 1
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrDSRIcon
                x: attrSRIcon.x
                y: attrSRIcon.y + attrSRText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
            }
            Text {
                id: attrDSRText
                x: attrSRText.x
                y: attrSRText.y + attrSRText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Stress Relief: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrDSRValue
                x: attrCEValue.x
                y: attrDSRText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "9/Day"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrDHRIcon
                x: attrDSRIcon.x
                y: attrDSRIcon.y + attrDSRText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Attributes/HealthRestored.png"
            }
            Text {
                id: attrDHRText
                x: attrDSRText.x
                y: attrDSRText.y + attrDSRText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Health Recovery: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrDHRValue
                x: attrCEValue.x
                y: attrDHRText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "9/Day"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrDFCIcon
                x: attrDHRIcon.x
                y: attrDHRIcon.y + attrDHRText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Resources/Foodsupplies.png"
            }
            Text {
                id: attrDFCText
                x: attrDHRText.x
                y: attrDHRText.y + attrDHRText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Food Consumption: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrDFCValue
                x: attrCEValue.x
                y: attrDFCText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "9/Day"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: attrSAIcon
                x: attrDFCIcon.x
                y: attrDFCIcon.y + attrDFCText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Resources/Aetherite.png"
            }
            Text {
                id: attrSAText
                x: attrDFCText.x
                y: attrDFCText.y + attrDFCText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Salary: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: attrSAValue
                x: attrCEValue.x
                y: attrSAText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "9/Week"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: natureIcon
                x: attrSAIcon.x
                y: attrSAIcon.y + attrSAText.height
                width: 50
                height: width
                source: "qrc:/graphics/GUI/Slots.png"
            }
            Text {
                id: natureText
                x: attrSAText.x
                y: attrSAText.y + attrSAText.height
                width: 520
                height: font.pixelSize+6
                color: "#568b56"
                text: "Nature: "
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }
            Text {
                id: natureValue
                x: attrCEValue.x
                y: natureText.y
                width: attrCEValue.width
                height: font.pixelSize+6
                color: "#568b56"
                text: "Convivial"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: attrCEText.font.pixelSize
                font.family: fontStencil.name
            }

            Image {
                id: currentlyBusy

                x: 698
                y: -4
                width: 88
                height: 88
            }
        }
    }

    Item {
        id: currentActivity

        x: 0
        y: topBar.height + 6
        width: 1080
        height: currentActivityTaskBorder.y + currentActivityTaskBorder.height

        function setCurrentActivity(ca)
        {
            currentActivityValue.text = ca;

            if (ca == "Idle")
            {
                currentActivityDescription.text = "This mercenary is awaiting orders in the barracks.";
                currentActivityGoToText.visible = false;
                currentActivityGoToMA.visible = false;
            }
            else if (ca == "On Mission")
            {
                var remDays=GameApi.base.remainingMissionDaysForHero(heroName);
                currentActivityDescription.text = remDays!=-1 ? topBar.getName().text+" is exploring the wilderness. Days until return: "+remDays : topBar.getName().text+" is missing in action.";
                currentActivityGoToText.visible = false;
                currentActivityGoToMA.visible = false;
            }
            else if (ca == "In Hospital")
            {
                currentActivityDescription.text = topBar.getName().text+" is under treatment.\nDays until full recovery: "+GameApi.base.hospital.daysToFullRecovery(GameApi.globalsCpp.alterNormalTextToInternal(heroName));
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "On Training Ground")
            {
                currentActivityDescription.text = topBar.getName().text+" is training combat skills.\nThe training will end in "+(GameApi.base.trainingGround.remainingDaysOfTraining(GameApi.globalsCpp.alterNormalTextToInternal(topBar.getName().text))+1)+" days.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Gym")
            {
                currentActivityDescription.text = topBar.getName().text+" is working out at the gym.\nVisible effects will appear in "+(GameApi.base.gym.remainingDaysOfTraining(GameApi.globalsCpp.alterNormalTextToInternal(topBar.getName().text))+1)+" days.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Laboratory")
            {
                currentActivityDescription.text = topBar.getName().text+" is expanding knowledge.\nThe study will end after "+(GameApi.base.laboratory.remainingDaysOfTraining(GameApi.globalsCpp.alterNormalTextToInternal(topBar.getName().text))+1)+" days.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Playing Field")
            {
                currentActivityDescription.text = topBar.getName().text+" currently rests at playing field.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Bar")
            {
                currentActivityDescription.text = topBar.getName().text+" chills out in bar.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Shrine")
            {
                currentActivityDescription.text = topBar.getName().text+" is focused on prayer.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "In Seclusion")
            {
                currentActivityDescription.text = topBar.getName().text+" meditates in total silence.";
                currentActivityGoToText.visible = true;
                currentActivityGoToMA.visible = true;
            }
            else if (ca == "Arriving")
            {
                currentActivityDescription.text = topBar.getName().text+" is travelling to your base.\nEstimated time of arrival: "+(GameApi.base.dockingStation.remainingDaysUntilHeroArrival(GameApi.globalsCpp.alterNormalTextToInternal(heroName))+1)+" days.";
                currentActivityGoToText.visible = false;
                currentActivityGoToMA.visible = false;
            }
        }

        Text {
            id: currentActivityText

            x: 17
            y: 5
            width: 420
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Current Activity:"
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: currentActivityValue

            x: currentActivityText.x + currentActivityText.width
            y: currentActivityText.y
            width: 1060-x
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "On Training Ground"
            font.pixelSize: 50
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignRight
        }

        Text {
            id: currentActivityDescription

            x: currentActivityText.x
            y: currentActivityText.y + currentActivityText.height + 10
            width: currentActivityGoToText.x - x - 10
            height: (font.pixelSize+4)*3

            color: "#94ef94"
            text: "This mercenary is awaiting orders in the barracks"
            wrapMode: Text.WordWrap
            maximumLineCount: 3
            font.pixelSize: 40
            font.family: fontStencil.name
        }

        Text {
            id: currentActivityGoToText

            x: 900
            y: currentActivityDescription.y + 10
            width: 150
            height: font.pixelSize

            color: "#94ef94"
            text: "Go to"
            font.pixelSize: 65
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: currentActivityGoToMA

            anchors.fill: currentActivityGoToText

            onClicked: {
                if (currentActivity_ == "On Mission")
                    ;//TODO mission
                else if (currentActivity_ == "In Hospital")
                    buildingMenuRequested("Hospital");
                else if (currentActivity_ == "On Training Ground")
                    buildingMenuRequested("Training Ground");
                else if (currentActivity_ == "In Gym")
                    buildingMenuRequested("Gym");
                else if (currentActivity_ == "In Laboratory")
                    buildingMenuRequested("Laboratory");
                else if (currentActivity_ == "In Playing Field")
                    buildingMenuRequested("Playing Field");
                else if (currentActivity_ == "In Bar")
                    buildingMenuRequested("Bar");
                else if (currentActivity_ == "In Shrine")
                    buildingMenuRequested("Shrine");
                else if (currentActivity_ == "In Seclusion")
                    buildingMenuRequested("Seclusion");
            }
        }

        Image {
            id: currentActivityTaskBorder

            x: 17
            y: currentActivityDescription.y + currentActivityDescription.height + 8
            width: 1048
            height: 3
            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Item {
        id: stressBorderEffect

        x: 17
        y: currentActivity.y + currentActivity.height
        width: 1048
        height: stressBorderEffectTaskBorder.y + stressBorderEffectTaskBorder.height + 4

        function setNoCurrentSBE()
        {
            stressBorderEffectValue.text = "-";
            stressBorderEffectDescription.text = "";
        }

        function setCurrentSBE(sbeName)
        {
            stressBorderEffectValue.text = sbeName;
            if (sbeName == "None")
                stressBorderEffectDescription.text = "";
            else if (sbeName == "Faint")
                stressBorderEffectDescription.text = topBar.getName().text+" is feeling sick and overwhelmed, which results in overall worse performance and greater vulnerability to stress.";
            else if (sbeName == "Desertion")
                stressBorderEffectDescription.text = "Some crew members say they heard rumors that "+topBar.getName().text+" is about to leave base without your permission.";
            else if (sbeName == "Fear")
                stressBorderEffectDescription.text = topBar.getName().text+" is afraid of going on mission. Additionally, fear clearly decreases the ability to fight.";
            else if (sbeName == "Fanatic Wrath")
                stressBorderEffectDescription.text = topBar.getName().text+" believes to be the chosen one, which turns out in reckless behaviour, yet effective in combat. However this state fades quickly after the danger disappears.";
            else if (sbeName == "Paranoia")
                stressBorderEffectDescription.text = "Everything seems unnatural and suspicious to "+topBar.getName().text+", which strengthens "+topBar.getName().text+"'s restlessness.";
            else if (sbeName == "Hopeless")
                stressBorderEffectDescription.text = "The amount of stress put on "+topBar.getName().text+" destroyed any belief in success, causing many opportunities unused.";
            else if (sbeName == "Confusion")
                stressBorderEffectDescription.text = topBar.getName().text+" is disorientated. Clumsiness affects "+topBar.getName().text+"'s combat and survival skills.";
            else if (sbeName == "Masochism")
                stressBorderEffectDescription.text = "Pain occurs to "+topBar.getName().text+" as the only solution to madness "+topBar.getName().text+" is exposed to.";
            else if (sbeName == "Abandonce")
                stressBorderEffectDescription.text = topBar.getName().text+" feels alienated and misunderstood by others, which slightly affects "+topBar.getName().text+"'s overall performance and decreases an ability to bear stress.";
            else if (sbeName == "Madness")
                stressBorderEffectDescription.text = topBar.getName().text+" behaves irrationally refusing to use equipment.";
            else if (sbeName == "Rage")
                stressBorderEffectDescription.text = "All "+topBar.getName().text+"'s thoughts concentrate on agression, decreasing other skills and vulnerability to stress.";
            else if (sbeName == "Restive")
                stressBorderEffectDescription.text = "Anxiety helps "+topBar.getName().text+" in combat, but disables the mercenary from recovering after a failure.";
            else if (sbeName == "Restlessness")
                stressBorderEffectDescription.text = topBar.getName().text+" is anxious, being put on stress every day.";
            else if (sbeName == "Stupor")
                stressBorderEffectDescription.text = "Because of stress, "+topBar.getName().text+" behaves unprofessionally causing a decrease in talents to the level of the least developed ability.";
            else if (sbeName == "Consciousness")
                stressBorderEffectDescription.text = "Curiosity takes over "+topBar.getName().text+", icreasing mind potential at the cost of being caught off guard and leaving heavier resources.";
            else if (sbeName == "Caution")
                stressBorderEffectDescription.text = "In extreme conditions "+topBar.getName().text+" desires to survive at all costs which affects "+topBar.getName().text+"'s combat skills and logical thinking.";
            else if (sbeName == "Awareness")
                stressBorderEffectDescription.text = topBar.getName().text+" focuses on being ready to fight, making "+topBar.getName().text+" less agile and less contributed to other tasks.";
            else if (sbeName == "Stone Skin")
                stressBorderEffectDescription.text = "Huge amount of stress caused a shock after which "+topBar.getName().text+" doesn't feel pain, making the mercenary able to handle more injuries.";
            else if (sbeName == "Multitasking")
                stressBorderEffectDescription.text = topBar.getName().text+" is obsessed with being better than all of the crew, which results in unified but not impressive skills.";
            else if (sbeName == "Equilibrium")
                stressBorderEffectDescription.text = "Traumatic experience had made "+topBar.getName().text+" wanting to be able to overcome any situation.";
            else if (sbeName == "Bravery")
                stressBorderEffectDescription.text = "Stress had awoken a hidden hero in "+topBar.getName().text+", increasing overall performance and making "+topBar.getName().text+" unwilling to die.";
            else if (sbeName == "Stress Resistant")
                stressBorderEffectDescription.text = "Extensive exposure to stress made "+topBar.getName().text+" much better at handling with stress.";
            else if (sbeName == "The Lucky One")
                stressBorderEffectDescription.text = topBar.getName().text+" seems to be unbelievably lucky under stress.";
            else if (sbeName == "Doombringer")
                stressBorderEffectDescription.text = "Traumatic experience let "+topBar.getName().text+" unleash the true potential of this mercenary.";
            else if (sbeName == "Excellence")
                stressBorderEffectDescription.text = "Under pressure "+topBar.getName().text+" becomes incredibly efficient in any given task.";
            else if (sbeName == "Absolute")
                stressBorderEffectDescription.text = topBar.getName().text+" can focus on the most developed skill, pushing its limits even further.";
            else
                stressBorderEffectDescription.text = "";
        }

        function setImmunity()
        {
            stressBorderEffectValue.text = "N/A";
            stressBorderEffectDescription.text = "Because of mechanical nature, this mercenary cannot have any quirks.";
        }

        function setMIA()
        {
            stressBorderEffectValue.text = "?";
            stressBorderEffectDescription.text = "";
        }

        Text {
            id: stressBorderEffectText

            x: 0
            y: 0
            width: 220
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "Quirk:"
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: stressBorderEffectValue

            x: 350
            y: stressBorderEffectText.y
            height: font.pixelSize + 4

            color: "#94ef94"
            text: "N/A"
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: stressBorderEffectDescription

            x: 0
            y: stressBorderEffectText.y + stressBorderEffectText.height
            width: parent.width - x
            height: (font.pixelSize + 4)*lineCount

            color: "#94ef94"
            text: "This mercenary is immune to stress. Thus, he/she is never affected by any stress border effect."
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }

        Image {
            id: stressBorderEffectTaskBorder

            x: 0
            y: stressBorderEffectDescription.y + stressBorderEffectDescription.height + 6
            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    Text {
        id: dismissButtonText

        x: 747
        y: stressBorderEffect.y + stressBorderEffect.height
        width: 280
        height: font.pixelSize + 4

        color: "#b30000"
        text: "Dismiss"
        font.pixelSize: 75
        font.family: fontStencil.name
    }
    MouseArea {
        id: dismissButtonMA

        anchors.fill: dismissButtonText

        onClicked: {
            GameApi.logger.trace("Dismiss clicked");
            dismissConfirmDialogVisible = true;
            dismissClicked();
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
            text: "Back"
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

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
