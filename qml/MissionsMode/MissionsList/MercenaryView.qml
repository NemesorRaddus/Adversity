import QtQuick 2.9
import Game 1.0

import "../.."

Item {
    id: root

    width: 1080
    height: 1440

    property string mercenaryName_: ""

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        var am=GameApi.base.mercenaries.amountOfMercenaries();
        var intName = GameApi.globalsCpp.alterNormalTextToInternal(mercenaryName_);
        for (var i=0;i<am;++i)
        {
            GameApi.base.mercenaries.prepareMercenaryAt(i);
            if (GameApi.base.mercenaries.preparedMercenary.name() == intName)
            {
                if (GameApi.base.mercenaries.preparedMercenary.isCommunicationAvailable())
                {
                    delegate.setName(mercenaryName_);
                    delegate.setArtSource(GameApi.base.mercenaries.preparedMercenary.pathToArt());
                    delegate.setProfession(GameApi.base.mercenaries.preparedMercenary.professionString());

                    var ce=GameApi.base.mercenaries.preparedMercenary.combatEffectiveness();
                    var pr=GameApi.base.mercenaries.preparedMercenary.proficiency();
                    var cl=GameApi.base.mercenaries.preparedMercenary.cleverness();
                    var hp=GameApi.base.mercenaries.preparedMercenary.health();
                    var hpMax=GameApi.base.mercenaries.preparedMercenary.healthLimit();
                    var st=GameApi.base.mercenaries.preparedMercenary.stress();
                    var sr=GameApi.base.mercenaries.preparedMercenary.stressResistance();
                    var sl=GameApi.base.mercenaries.preparedMercenary.stressLimit();
                    var sa=GameApi.base.mercenaries.preparedMercenary.salary();
                    var fc=GameApi.base.mercenaries.preparedMercenary.dailyFoodConsumption();

                    var bce=GameApi.base.mercenaries.preparedMercenary.baseCombatEffectiveness();
                    var bpr=GameApi.base.mercenaries.preparedMercenary.baseProficiency();
                    var bcl=GameApi.base.mercenaries.preparedMercenary.baseCleverness();
                    var bhpMax=GameApi.base.mercenaries.preparedMercenary.baseHealthLimit();
                    var bsr=GameApi.base.mercenaries.preparedMercenary.baseStressResistance();
                    var bsl=GameApi.base.mercenaries.preparedMercenary.baseStressLimit();
                    var bsa=GameApi.base.mercenaries.preparedMercenary.baseSalary();
                    var bfc=GameApi.base.mercenaries.preparedMercenary.baseDailyFoodConsumption();

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

                    armorArt.source = GameApi.base.mercenaries.preparedMercenary.hasArmor() ? GameApi.base.mercenaries.preparedMercenary.preparedArmor.pathToArt() : "qrc:/graphics/GUI/Slots/ArmourSlot.png";
                    if (GameApi.base.mercenaries.preparedMercenary.hasWeaponToolInSlot(0))
                    {
                        GameApi.base.mercenaries.preparedMercenary.prepareWeaponTool(0);
                        weapon1Art.source =  GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.pathToArt();
                        weapon1.name = GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.name();
                    }
                    else
                    {
                        weapon1Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                        weapon1.name = "";
                    }
                    if (GameApi.base.mercenaries.preparedMercenary.hasWeaponToolInSlot(1))
                    {
                        GameApi.base.mercenaries.preparedMercenary.prepareWeaponTool(1);
                        weapon2Art.source =  GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.pathToArt();
                        weapon2.name = GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.name();
                    }
                    else
                    {
                        weapon2Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                        weapon2.name = "";
                    }

                    energyAmount.text = GameApi.base.mercenaries.preparedMercenary.carriedEnergy();
                    foodSuppliesAmount.text = GameApi.base.mercenaries.preparedMercenary.carriedFoodSupplies();
                    buildingMaterialsAmount.text = GameApi.base.mercenaries.preparedMercenary.carriedBuildingMaterials();
                    aetheriteAmount.text = GameApi.base.mercenaries.preparedMercenary.carriedAetheriteOre();

                    equipment.visible = true;
                    var eqsAmount = GameApi.base.mercenaries.preparedMercenary.carriedEquipmentAmount();
                    if (eqsAmount>=1)
                    {
                        GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-1);
                        eq1Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();

                        if (eqsAmount>=2)
                        {
                            GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-2);
                            eq2Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();

                            if (eqsAmount>=3)
                            {
                                GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-3);
                                eq3Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();

                                if (eqsAmount>=4)
                                {
                                    GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-4);
                                    eq4Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();

                                    if (eqsAmount>=5)
                                    {
                                        GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-5);
                                        eq5Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();

                                        if (eqsAmount>=6)
                                        {
                                            GameApi.base.mercenaries.preparedMercenary.prepareCarriedEquipment(eqsAmount-6);
                                            eq6Art.source = GameApi.base.mercenaries.preparedMercenary.preparedCarriedEquipment.pathToArt();
                                        }
                                        else
                                            eq6Art.source = "";
                                    }
                                    else
                                    {
                                        eq5Art.source = "";
                                        eq6Art.source = "";
                                    }
                                }
                                else
                                {
                                    eq4Art.source = "";
                                    eq5Art.source = "";
                                    eq6Art.source = "";
                                }
                            }
                            else
                            {
                                eq3Art.source = "";
                                eq4Art.source = "";
                                eq5Art.source = "";
                                eq6Art.source = "";
                            }
                        }
                        else
                        {
                            eq2Art.source = "";
                            eq3Art.source = "";
                            eq4Art.source = "";
                            eq5Art.source = "";
                            eq6Art.source = "";
                        }
                    }
                    else
                    {
                        eq1Art.source = "";
                        eq2Art.source = "";
                        eq3Art.source = "";
                        eq4Art.source = "";
                        eq5Art.source = "";
                        eq6Art.source = "";
                    }
                }
                else
                {
                    delegate.setArtSource(GameApi.base.mercenaries.preparedMercenary.pathToArt());
                    delegate.setName(mercenaryName_);
                    delegate.setProfession(GameApi.base.mercenaries.preparedMercenary.professionString());
                    delegate.setMIA();

                    delegate.setColorHL("#568b56");
                    delegate.setColorSL("#568b56");
                    delegate.setColorCE("#568b56");
                    delegate.setColorPR("#568b56");
                    delegate.setColorCL("#568b56");
                    delegate.setColorSR("#568b56");
                    delegate.setColorFC("#568b56");
                    delegate.setColorSA("#568b56");

                    armorArt.source = GameApi.base.mercenaries.preparedMercenary.hasArmor() ? GameApi.base.mercenaries.preparedMercenary.preparedArmor.pathToArt() : "qrc:/graphics/GUI/Slots/ArmourSlot.png";
                    if (GameApi.base.mercenaries.preparedMercenary.hasWeaponToolInSlot(0))
                    {
                        GameApi.base.mercenaries.preparedMercenary.prepareWeaponTool(0);
                        weapon1Art.source =  GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.pathToArt();
                        weapon1.name = GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.name();
                    }
                    else
                    {
                        weapon1Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                        weapon1.name = "";
                    }
                    if (GameApi.base.mercenaries.preparedMercenary.hasWeaponToolInSlot(1))
                    {
                        GameApi.base.mercenaries.preparedMercenary.prepareWeaponTool(1);
                        weapon2Art.source =  GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.pathToArt();
                        weapon2.name = GameApi.base.mercenaries.preparedMercenary.preparedWeaponTool.name();
                    }
                    else
                    {
                        weapon2Art.source = "qrc:/graphics/GUI/Slots/ToolSlot.png";
                        weapon2.name = "";
                    }

                    energyAmount.text = "?";
                    foodSuppliesAmount.text = "?";
                    buildingMaterialsAmount.text = "?";
                    aetheriteAmount.text = "?";

                    equipment.visible = false;
                }
                break;
            }
        }
    }

    function setMercenary(mercenaryName)
    {
        mercenaryName_=mercenaryName;
        updateEverything();
    }

    Text {
        x: 4
        y: 0

        color: "#94ef94"
        text: "Mercenary:"
        font.pixelSize: 50
        font.family: fontStencil.name
    }

    MercenaryDelegate {
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
            id: energyAmount

            x: 280
            y: 0
            width: 240

            color: "#568b56"
            wrapMode: Text.WordWrap
            text: "Energy will probably run out after 10 days."
            font.pixelSize: 60
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
            id: buildingMaterialsAmount

            x: 280
            y: 0
            width: 240

            color: "#568b56"
            wrapMode: Text.WordWrap
            text: "Materials will probably run out after 10 days."
            font.pixelSize: 60
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
            id: foodSuppliesAmount

            x: 280
            y: 0
            width: 240

            color: "#568b56"
            wrapMode: Text.WordWrap
            text: "Food will probably run out after 10 days."
            font.pixelSize: 60
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
            id: aetheriteAmount

            x: 280
            y: 0
            width: 240

            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 60
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
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
                id: eq1Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
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
                id: eq2Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
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
                id: eq3Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
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
                id: eq4Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
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
                id: eq5Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
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
                id: eq6Art

                x: 1
                y: 1
                width: parent.width-2
                height: parent.height-2
            }
            MouseArea {
                anchors.fill: parent
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
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
