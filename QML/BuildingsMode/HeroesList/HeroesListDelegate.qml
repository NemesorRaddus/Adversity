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
        prof.text=text;
    }

    function setCE(amount)
    {
        attrCEText.text = "CE: "+amount;
    }

    function setPR(amount)
    {
        attrPRText.text = "PR: "+amount;
    }

    function setCL(amount)
    {
        attrCLText.text = "CL: "+amount;
    }

    function getName()
    {
        return name;
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
            y: 0
            color: "#94ef94"
            text: qsTr("Marek Jakubowski")
            font.pixelSize: 50
            font.family: fontStencil.name
        }

        Text {
            id: prof
            x: 0
            y: 50
            color: "#94ef94"
            text: qsTr("Bounty Hunter")
            font.pixelSize: 36
            font.family: fontStencil.name
        }

        Image {
            id: attrCEIcon
            x: 0
            y: 86
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/CE.png"
        }
        Text {
            id: attrCEText
            x: 50
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("CE: ")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }
        Text {
            id: attrCEValue
            x: 0
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("99")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }

        Image {
            id: attrPRIcon
            x: 0
            y: 86
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/PR.png"
        }
        Text {
            id: attrPRText
            x: 50
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("PR: ")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }
        Text {
            id: attrPRValue
            x: 0
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("99")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }

        Image {
            id: attrCLIcon
            x: 0
            y: 86
            width: 50
            height: 50
            source: "qrc:/graphics/GUI/CL.png"
        }
        Text {
            id: attrCLText
            x: 50
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("CL: ")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }
        Text {
            id: attrCLValue
            x: 0
            y: 86
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("99")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
