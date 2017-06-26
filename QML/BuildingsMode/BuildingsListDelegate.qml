import QtQuick 2.5

import "."

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

    function setLevel(text)
    {
        level.text = text;
    }

    function setDescription(text)
    {
        description.text = text;
    }

    function getName()
    {
        return name;
    }

    function markAsUpgraded(isUpgraded)
    {
        if (isUpgraded)
        {
            currentlyUpgraded.visible = true;
            currentlyUpgraded.anim.restart();
        }
        else
        {
            currentlyUpgraded.visible = false;
            currentlyUpgraded.anim.stop();
        }
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
            y: -4
            color: "#94ef94"
            text: qsTr("Powerplant")
            font.pixelSize: 76
            font.family: fontStencil.name
        }

        Text {
            id: level
            x: 0
            y: 60
            color: "#94ef94"
            text: qsTr("Level: 1")
            font.pixelSize: 44
            font.family: fontStencil.name
        }

        Text {
            id: description
            x: 0
            y: 113
            width: 785
            height: 136
            color: "#568b56"
            text: qsTr("Description")
            wrapMode: Text.WordWrap
            font.pixelSize: 40
            font.family: fontStencil.name
        }

        Image {
            id: currentlyUpgraded

            property alias anim: anim

            visible: false

            x: 732
            y: 0
            width: 62
            height: 62

            source: "qrc:/graphics/GUI/Settings.png"

            RotationAnimator on rotation {
                id: anim
                from: 0;
                to: 360;
                duration: 2500
                loops: RotationAnimation.Infinite
                running: false
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
