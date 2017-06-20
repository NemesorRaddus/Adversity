import QtQuick 2.5

import Game 1.0
import "../.."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 271

    property string name_
    property string type_
    property string tier_

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name_ = text;
        name.text = GameApi.tr(text);
    }

    function setType(text)
    {
        type_ = text;
        type.text = GameApi.tr(text);
    }

    function setTier(nr)
    {
        tier_ = nr;
        tier.text = "Tier "+nr;
    }

    function setCost(nr)
    {
        buyCostAmount.text = nr;
    }

    function setBonus(index, bName, bValue)
    {
        if (bValue == 0 || bValue == undefined)
        {
            switch (index)//visible off
            {
            case 0:
                bonus1Icon.visible = false;
                bonus1Text.visible = false;
                bonus1Value.visible = false;
                break;
            case 1:
                bonus2Icon.visible = false;
                bonus2Text.visible = false;
                bonus2Value.visible = false;
                break;
            case 2:
                bonus3Icon.visible = false;
                bonus3Text.visible = false;
                bonus3Value.visible = false;
                break;
            case 3:
                bonus4Icon.visible = false;
                bonus4Text.visible = false;
                bonus4Value.visible = false;
                break;
            case 4:
                bonus5Icon.visible = false;
                bonus5Text.visible = false;
                bonus5Value.visible = false;
                break;
            case 5:
                bonus6Icon.visible = false;
                bonus6Text.visible = false;
                bonus6Value.visible = false;
                break;
            }
        }
        else
        {//icon and text
            if (bName == "Combat Effectiveness")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus1Text.text = "CE";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus2Text.text = "CE";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus3Text.text = "CE";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus4Text.text = "CE";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus5Text.text = "CE";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/CE.png";
                    bonus6Text.text = "CE";
                    break;
                }
            }
            else if (bName == "Proficiency")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus1Text.text = "PR";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus2Text.text = "PR";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus3Text.text = "PR";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus4Text.text = "PR";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus5Text.text = "PR";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/PR.png";
                    bonus6Text.text = "PR";
                    break;
                }
            }
            else if (bName == "Cleverness")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus1Text.text = "CL";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus2Text.text = "CL";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus3Text.text = "CL";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus4Text.text = "CL";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus5Text.text = "CL";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/CL.png";
                    bonus6Text.text = "CL";
                    break;
                }
            }
            else if (bName == "Luck")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus1Text.text = "LU";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus2Text.text = "LU";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus3Text.text = "LU";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus4Text.text = "LU";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus5Text.text = "LU";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/Profitability.png";
                    bonus6Text.text = "LU";
                    break;
                }
            }
            else if (bName == "Health Limit")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus1Text.text = "HL";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus2Text.text = "HL";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus3Text.text = "HL";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus4Text.text = "HL";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus5Text.text = "HL";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus6Text.text = "HL";
                    break;
                }
            }
            else if (bName == "Daily Health Recovery")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus1Text.text = "DHR";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus2Text.text = "DHR";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus3Text.text = "DHR";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus4Text.text = "DHR";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus5Text.text = "DHR";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/HealthRestored.png";
                    bonus6Text.text = "DHR";
                    break;
                }
            }
            else if (bName == "Stress Resistance")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus1Text.text = "SR";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus2Text.text = "SR";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus3Text.text = "SR";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus4Text.text = "SR";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus5Text.text = "SR";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/StressResistance.png";
                    bonus6Text.text = "SR";
                    break;
                }
            }
            else if (bName == "Stress Limit")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus1Text.text = "SL";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus2Text.text = "SL";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus3Text.text = "SL";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus4Text.text = "SL";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus5Text.text = "SL";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus6Text.text = "SL";
                    break;
                }
            }
            else if (bName == "Stress Border")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus1Text.text = "SB";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus2Text.text = "SB";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus3Text.text = "SB";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus4Text.text = "SB";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus5Text.text = "SB";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/StressLimit.png";
                    bonus6Text.text = "SB";
                    break;
                }
            }
            else if (bName == "Daily Stress Recovery")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus1Text.text = "DSR";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus2Text.text = "DSR";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus3Text.text = "DSR";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus4Text.text = "DSR";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus5Text.text = "DSR";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/StressRelief.png";
                    bonus6Text.text = "DSR";
                    break;
                }
            }
            else if (bName == "Salary")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus1Text.text = "SA";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus2Text.text = "SA";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus3Text.text = "SA";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus4Text.text = "SA";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus5Text.text = "SA";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/Aetherite.png";
                    bonus6Text.text = "SA";
                    break;
                }
            }
            else if (bName == "Daily Food Consumption")
            {
                switch (index)
                {
                case 0:
                    bonus1Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus1Text.text = "DFC";
                    break;
                case 1:
                    bonus2Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus2Text.text = "DFC";
                    break;
                case 2:
                    bonus3Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus3Text.text = "DFC";
                    break;
                case 3:
                    bonus4Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus4Text.text = "DFC";
                    break;
                case 4:
                    bonus5Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus5Text.text = "DFC";
                    break;
                case 5:
                    bonus6Icon.source = "qrc:/graphics/GUI/Foodsupplies.png";
                    bonus6Text.text = "DFC";
                    break;
                }
            }

            switch (index)//visible on
            {
            case 0:
                bonus1Icon.visible = true;
                bonus1Text.visible = true;
                bonus1Value.visible = true;
                break;
            case 1:
                bonus2Icon.visible = true;
                bonus2Text.visible = true;
                bonus2Value.visible = true;
                break;
            case 2:
                bonus3Icon.visible = true;
                bonus3Text.visible = true;
                bonus3Value.visible = true;
                break;
            case 3:
                bonus4Icon.visible = true;
                bonus4Text.visible = true;
                bonus4Value.visible = true;
                break;
            case 4:
                bonus5Icon.visible = true;
                bonus5Text.visible = true;
                bonus5Value.visible = true;
                break;
            case 5:
                bonus6Icon.visible = true;
                bonus6Text.visible = true;
                bonus6Value.visible = true;
                break;
            }

            //plus or minus
            if (bValue > 0)
                bValue = "+"+bValue;
            else
                bValue = "-"+bValue;

            //value setting
            switch (index)
            {
            case 0:
                bonus1Value.text = bValue;
                break;
            case 1:
                bonus2Value.text = bValue;
                break;
            case 2:
                bonus3Value.text = bValue;
                break;
            case 3:
                bonus4Value.text = bValue;
                break;
            case 4:
                bonus5Value.text = bValue;
                break;
            case 5:
                bonus6Value.text = bValue;
                break;
            }
        }
    }

    function getName()
    {
        return name_;
    }

    function getType()
    {
        return profession_;
    }

    function getTier()
    {
        return tier_;
    }

    width: 1080
    height: 271

//    transform: [
//        Scale {
//            id: someScale

//            xScale: width/theoreticalWidth
//            yScale: height/theoreticalHeight
//        },
//        Translate {
//            x: (width-theoreticalWidth*someScale.xScale)/2
//            y: (height-theoreticalHeight*someScale.yScale)/2
//        }
//    ]

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
            text: "Biohazard Protection Suit"
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: type
            x: 150
            y: 50
            color: "#94ef94"
            text: "Armor"
            font.pixelSize: 36
            font.family: fontStencil.name
        }

        Text {
            id: tier
            x: 0
            y: 50
            color: "#94ef94"
            text: "Tier 2"
            font.pixelSize: 36
            font.family: fontStencil.name
        }

        Image {
            id: bonus1Icon
            x: 0
            y: 84
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/CE.png"
        }
        Text {
            id: bonus1Text
            x: 52
            y: 86
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus1Value
            x: 164
            y: 86
            width: 160
            height: 50
            color: "#568b56"
            text: "+99"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: bonus2Icon
            x: 0
            y: 140
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/PR.png"
        }
        Text {
            id: bonus2Text
            x: 52
            y: 142
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus2Value
            x: 164
            y: 142
            width: 160
            height: 50
            color: "#568b56"
            text: "+99"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: bonus3Icon
            x: 0
            y: 196
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/CL.png"
        }
        Text {
            id: bonus3Text
            x: 52
            y: 198
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus3Value
            x: 164
            y: 198
            width: 160
            height: 50
            color: "#568b56"
            text: "+99"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: bonus4Icon
            x: 313
            y: 86
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/HealthRestored.png"
        }
        Text {
            id: bonus4Text
            x: 365
            y: 88
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus4Value
            x: 477
            y: 88
            width: 160
            height: 50
            color: "#568b56"
            text: "+66"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: bonus5Icon
            x: 313
            y: 142
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/StressRelief.png"
        }
        Text {
            id: bonus5Text
            x: 365
            y: 144
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus5Value
            x: 477
            y: 144
            width: 160
            height: 50
            color: "#568b56"
            text: "+66"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Image {
            id: bonus6Icon
            x: 313
            y: 198
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/StressLimit.png"
        }
        Text {
            id: bonus6Text
            x: 365
            y: 200
            width: 94
            height: 50
            color: "#568b56"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
        Text {
            id: bonus6Value
            x: 477
            y: 200
            width: 160
            height: 50
            color: "#568b56"
            text: "+66"
            wrapMode: Text.Wrap
            maximumLineCount: 1
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: buyText
            x: 636
            y: 86
            color: "#94ef94"
            text: "Buy"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Image {
            id: buyCostIcon

            x: 620
            y: 171
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Aetherite.png"
        }
        Text {
            id: buyCostAmount

            x: 681
            y: 164
            color: "#94ef94"
            text: "800"
            wrapMode: Text.WordWrap
            font.pixelSize: 56
            font.family: fontStencil.name
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
