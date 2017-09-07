import QtQuick 2.9

import Game 1.0
import "../.."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 271

    property string name_
    property string profession_

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name_ = text;
        name.text = GameApi.tr(text);
    }

    function setProfession(text)
    {
        profession_ = text;
        prof.text="The "+GameApi.tr(text);
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

    function setST(amount)
    {
        attrSTValue.text = amount;
        statusSTFrame.check(amount,attrSLValue.text);
    }

    function setSL(amount)
    {
        if (amount==-1)
        {
            attrSTValue.text = "N/A";
            attrSLValue.text = "N/A";
            attrSRValue.text = "N/A";
        }
        else
        {
            attrSLValue.text = amount;
            statusSTFrame.check(attrSTValue.text,amount);
        }
    }

    function setSR(amount)
    {
        attrSRValue.text = amount;
    }

    function setSA(amount)
    {
        attrSAValue.text = amount;
    }

    function setFC(amount)
    {
        attrFCValue.text = amount;
    }

    function setCurrentActivity(ca)
    {
        if (ca == "Idle")
            currentlyBusy.source = "";
        else if (ca == "On Mission")
            currentlyBusy.source = "qrc:/graphics/GUI/Settings.png";
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
        attrSLValue.color = col;
    }

    function setColorSR(col)
    {
        attrSRValue.color = col;
    }

    function setColorFC(col)
    {
        attrFCValue.color = col;
    }

    function setColorSA(col)
    {
        attrSAValue.color = col;
    }

    function getName()
    {
        return name;
    }

    function getProfession()
    {
        return prof;
    }

    width: 1080
    height: 271

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

    Image {
        id: itemBorder
        x: 17
        y: 265
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
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: prof
            x: 0
            y: 50
            color: "#94ef94"
            text: "The Bounty Hunter"
            font.pixelSize: 36
            font.family: fontStencil.name
        }

        Image {
            id: attrCEIcon
            x: 0
            y: 84
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/CE.png"
        }
        Text {
            id: attrCEText
            x: 52
            y: 86
            width: 735
            height: 50
            color: "#568b56"
            text: "CE: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrCEValue
            x: 138
            y: 86
            width: 58
            height: 50
            color: "#568b56"
            text: "99"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrPRIcon
            x: 0
            y: 140
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/PR.png"
        }
        Text {
            id: attrPRText
            x: 52
            y: 142
            width: 735
            height: 50
            color: "#568b56"
            text: "PR: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrPRValue
            x: 138
            y: 142
            width: 58
            height: 50
            color: "#568b56"
            text: "99"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrCLIcon
            x: 0
            y: 196
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/CL.png"
        }
        Text {
            id: attrCLText
            x: 52
            y: 198
            width: 735
            height: 50
            color: "#568b56"
            text: "CL: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrCLValue
            x: 138
            y: 198
            width: 58
            height: 50
            color: "#568b56"
            text: "99"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrHPIcon
            x: 206
            y: 84
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/HealthRestored.png"
        }
        Text {
            id: attrHPText
            x: 258
            y: 86
            width: 735
            height: 50
            color: "#568b56"
            text: "HP: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrHPValue
            x: 350
            y: 86
            width: 140
            height: 50
            color: "#568b56"
            text: "99/99"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrSTIcon
            x: 206
            y: 140
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/StressRelief.png"
        }
        Text {
            id: attrSTText
            x: 258
            y: 142
            width: 735
            height: 50
            color: "#568b56"
            text: "ST: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrSTValue
            x: 350
            y: 142
            width: 140
            height: 50
            color: "#568b56"
            text: "666"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrSLIcon
            x: 206
            y: 196
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/StressLimit.png"
        }
        Text {
            id: attrSLText
            x: 258
            y: 198
            width: 735
            height: 50
            color: "#568b56"
            text: "SL: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrSLValue
            x: 350
            y: 198
            width: 140
            height: 50
            color: "#568b56"
            text: "666"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Image {
            id: attrSRIcon
            x: 496
            y: 84
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Attributes/StressResistance.png"
        }
        Text {
            id: attrSRText
            x: 548
            y: 86
            width: 735
            height: 50
            color: "#568b56"
            text: "SR: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrSRValue
            x: 640
            y: 86
            width: 138
            height: 50
            color: "#568b56"
            text: "9.9"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrSAIcon
            x: 496
            y: 140
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Resources/Aetherite.png"
        }
        Text {
            id: attrSAText
            x: 548
            y: 142
            width: 735
            height: 50
            color: "#568b56"
            text: "SA: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrSAValue
            x: 640
            y: 142
            width: 58
            height: 50
            color: "#568b56"
            text: "99"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrFCIcon
            x: 496
            y: 196
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Resources/Foodsupplies.png"
        }
        Text {
            id: attrFCText
            x: 548
            y: 198
            width: 735
            height: 50
            color: "#568b56"
            text: "FC: "
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: attrFCValue
            x: 640
            y: 198
            width: 58
            height: 50
            color: "#568b56"
            text: "9"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
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

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
