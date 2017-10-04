import QtQuick 2.9

import "."

Item {
    id: root

    function setText(text_)
    {
        text.text = text_;
    }

    function setArt(source)
    {
        art.source = source;
    }

    function getHeight()
    {
        return height;
    }

    width: 1080
    height: itemBorder.y+itemBorder.height

    Item {
        id: artItem

        x: 17
        y: 17
        width: 262
        height: width

        Image {
            id: art

            x: 3
            y: 3
            width: 256
            height: width
        }
        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
    }

    Text {
        id: text

        x: artItem.x+artItem.width+8
        y: 4
        width: root.width-x-6
        height: (font.pixelSize+8)*lineCount

        color: "#94ef94"
        font.pixelSize: 45
        font.family: fontStencil.name
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }

    Image {
        id: itemBorder
        x: 17
        y: 2*artItem.y+artItem.height>text.height + 6 ? 2*artItem.y+artItem.height : text.height + 6
        width: 1048
        height: 3
        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
