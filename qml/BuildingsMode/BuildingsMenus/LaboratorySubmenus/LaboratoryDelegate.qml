import QtQuick 2.9
import QtGraphicalEffects 1.0

import "."

Item {
    id: root

    readonly property int theoreticalWidth: 1048
    readonly property int theoreticalHeight: 118

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

    width: 1048
    height: 118

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

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    Item{

        x:312
        y: 0
        width: 734
        height: 115

        clip: true

        Image{
            id: mercenaryArt

            x: 0
            y: -271
            width: 734
            height: 734

            source: "qrc:/graphics/Mercs/Gunzerker/PaulLuft.png"
        }

        GaussianBlur {
            anchors.fill: mercenaryArt
            source: mercenaryArt
            radius: 40
            samples: 20
            deviation: 20
            cached: true
        }
    }

    Image{
        id: overlay

        x: 312
        y:0
        width: 734
        height: 115

        source: "qrc:/graphics/GUI/MercenarySlot/Opacity_Mask.png"
    }

    Image{
        id: taskBorder

        x: 0
        y: 115
        width: parent
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Text{
        //Imie najemnika. Jezeli jest pute powinno byc "Empty Slot" czy cos w tym stylu.

        x: 5
        y: 0
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        color: "#94ef94"
        text: "Paul Luft"
        font.pixelSize: 90
        font.family: fontStencil.name
    }

    MouseArea{
        anchors.fill: parent
    }
    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
