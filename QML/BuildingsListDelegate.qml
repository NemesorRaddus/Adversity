import QtQuick 2.5

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

    Image {
        id: art
        x: 20
        y: 3
        width: 256
        height: 256
    }

    Image {
        id: frame
        x: 17
        y: 0
        width: 262
        height: 262
        source: "qrc:/graphics/GUI/Task_Picture.png"
    }

    Text {
        id: name
        x: 280
        y: 10
        color: "#94ef94"
        text: qsTr("Power Plant")
        font.pixelSize: 60
        font.family: "Stencil"
    }

    Text {
        id: level
        x: 280
        y: 70
        color: "#94ef94"
        text: qsTr("Level: 10")
        font.pixelSize: 40
        font.family: "Stencil"
    }

    Text {
        id: description
        x: 280
        y: 123
        width: 785
        height: 136
        color: "#568b56"
        text: qsTr("Energy for everyone!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
        wrapMode: Text.WordWrap
        font.pixelSize: 30
        font.family: "Stencil"
    }

}
