import QtQuick 2.5

import "../.."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 271

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name.text = text;
    }

    function setProfession(text)
    {
        prof.text="The "+text;
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
                    source = "qrc:/graphics/GUI/LowHealth80.png";
                else if (hp/hpMax <= 0.4)
                    source = "qrc:/graphics/GUI/LowHealth60.png";
                else if (hp/hpMax <= 0.6)
                    source = "qrc:/graphics/GUI/LowHealth40.png";
                else if (hp/hpMax <= 0.8)
                    source = "qrc:/graphics/GUI/LowHealth20.png";
                else
                    source = "";
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
                    source = "qrc:/graphics/GUI/HighStress80.png";
                else if (stress/stressLimit >= 0.6)
                    source = "qrc:/graphics/GUI/HighStress60.png";
                else if (stress/stressLimit >= 0.4)
                    source = "qrc:/graphics/GUI/HighStress40.png";
                else if (stress/stressLimit >= 0.2)
                    source = "qrc:/graphics/GUI/HighStress20.png";
                else
                    source = "";
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
            source: "qrc:/graphics/GUI/CE.png"
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
            source: "qrc:/graphics/GUI/PR.png"
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
            source: "qrc:/graphics/GUI/CL.png"
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
            source: "qrc:/graphics/GUI/HealthRestored.png"
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
            source: "qrc:/graphics/GUI/StressRelief.png"
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
            source: "qrc:/graphics/GUI/StressLimit.png"
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
            source: "qrc:/graphics/GUI/StressResistance.png"
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
            width: 58
            height: 50
            color: "#568b56"
            text: "9.9"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: attrSAIcon
            x: 496
            y: 140
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/Aetherite.png"
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
            source: "qrc:/graphics/GUI/Foodsupplies.png"
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

            visible: false

            x: 708
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
