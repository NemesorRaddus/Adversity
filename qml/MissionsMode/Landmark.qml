import QtQuick 2.0

Item {
    id: root

    property string name_
    property string description_
    property string artSource_

    signal iconClicked(int x, int y, string name, string description, string pathToArt)

    function setName(name)
    {
        name_ = name;
    }

    function setDescription(description)
    {
        description_ = description;
    }

    function setArtSource(path)
    {
        artSource_ = path;
    }

    function getName()
    {
        return name_;
    }

    function getDescription()
    {
        return description_;
    }

    function getArtSource()
    {
        return artSource_;
    }

    Image {
        id: icon

        anchors.fill: parent

        source: "qrc:/graphics/GUI/CE.png"

        MouseArea {
            id: ma

            anchors.fill: parent

            onClicked: iconClicked(root.x+root.width/2, root.y+root.height/2, name_, description_, artSource_)
        }
    }
}
