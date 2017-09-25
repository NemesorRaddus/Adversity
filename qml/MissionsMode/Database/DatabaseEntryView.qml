import QtQuick 2.9
import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440

    property string category: ""

    signal backClicked()

    state: "hiddenDown"

    function reactToBackOnToolbar()
    {
        return false;
    }

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name.text = GameApi.tr(text);
        fade.nameAfterFading=text;
    }

    function setDescription(desc)
    {
        description.text = desc;
    }

    function setInhabitancyText(text)
    {
        lands.text=text;
    }

    function setItem(name, category)
    {
        root.category = category;
        setArtSource("qrc:/graphics/Database/"+GameApi.globalsCpp.alterNormalTextToInternal(category)+"/"+GameApi.globalsCpp.alterNormalTextToInternal(name)+".png");
        setName(name);
        GameApi.base.database.prepareCategory(category);
        var am=GameApi.base.database.amountOfEntriesInCurrentCategory();
        for (var i=0;i<am;++i)
            if (GameApi.base.database.nameOfEntry(i) == name)
            {
                setDescription(GameApi.base.database.descriptionOfEntry(i));
                setInhabitancyText(GameApi.base.database.inhabitancyTextOfEntry(i));

                if (i == 0)
                    previous.visible = false;
                else
                    previous.visible = true;

                if (i+1<am)
                    next.visible = true;
                else
                    next.visible = false;

                break;
            }
    }

    function getName()
    {
        return name;
    }

    function goToPrevious()
    {
        GameApi.base.database.prepareCategory(root.category);
        var am=GameApi.base.database.amountOfEntriesInCurrentCategory();
        for (var i=1;i<am;++i)//button visibility guarantees it's ok
            if (GameApi.base.database.nameOfEntry(i) == fade.nameAfterFading)
            {
                fade.nameAfterFading = GameApi.base.database.nameOfEntry(i-1);
                fade.descriptionAfterFading = GameApi.base.database.descriptionOfEntry(i-1);
                fade.inhabitancyAfterFading = GameApi.base.database.inhabitancyTextOfEntry(i-1);
                fade.artAfterFading = "qrc:/graphics/Database/"+GameApi.globalsCpp.alterNormalTextToInternal(root.category)+"/"+GameApi.globalsCpp.alterNormalTextToInternal(fade.nameAfterFading)+".png";

                if (i-1<=0)
                    previous.visible = false;

                next.visible = true;

                break;
            }
        fade.start();
    }

    function goToNext()
    {
        GameApi.base.database.prepareCategory(root.category);
        var am=GameApi.base.database.amountOfEntriesInCurrentCategory();
        for (var i=0;i<am;++i)
            if (GameApi.base.database.nameOfEntry(i) == fade.nameAfterFading)
            {
                fade.nameAfterFading = GameApi.base.database.nameOfEntry(i+1);
                fade.descriptionAfterFading = GameApi.base.database.descriptionOfEntry(i+1);
                fade.inhabitancyAfterFading = GameApi.base.database.inhabitancyTextOfEntry(i+1);
                fade.artAfterFading = "qrc:/graphics/Database/"+GameApi.globalsCpp.alterNormalTextToInternal(root.category)+"/"+GameApi.globalsCpp.alterNormalTextToInternal(fade.nameAfterFading)+".png";

                if (i+1>=am-1)
                    next.visible = false;

                previous.visible = true;

                break;
            }
        fade.start();
    }

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    Item {
        id: changeablePart

        x: 0
        y: 15
        width: parent.width
        height: parent.height-y

        Item {
            id: topBar

            width: 1080

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

                    x: 6
                    y: -6

                    color: "#94ef94"
                    text: "Splitterhound"
                    font.pixelSize: 90
                    font.family: fontStencil.name
                }

                Text {
                    id: lands

                    x: 6
                    y: 65
                    width: 779
                    height: 184

                    color: "#94ef94"
                    text: "Noticed inhabitants of:\n"
                    font.pixelSize: 50
                    font.family: fontStencil.name
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }
            }
        }

        Flickable {
            id: descriptionFlickable

            x: 17
            y: 279
            width: 1048
            height: 1094

            contentWidth: width
            contentHeight: description.height

            boundsBehavior: Flickable.StopAtBounds

            clip: true

            Text {
                id: description

                width: parent.width
                height: descriptionMetrics.boundingRect.height*lineCount

                color: "#94ef94"
                font.pixelSize: 50
                font.family: fontStencil.name
                wrapMode: Text.WordWrap
            }

            TextMetrics {
                id: descriptionMetrics

                font: description.font
                text: description.text
            }
        }

        NumberAnimation {
            id: fade

            property string artAfterFading: ""
            property string nameAfterFading: ""
            property string inhabitancyAfterFading: ""
            property string descriptionAfterFading: ""

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            target: changeablePart
            running: false
            onRunningChanged: {
                if (running == false)
                {
                    if (from == 1)
                    {
                        setArtSource(artAfterFading);
                        setName(nameAfterFading);
                        setInhabitancyText(inhabitancyAfterFading);
                        setDescription(descriptionAfterFading);
                        from = 0;
                        to = 1;
                        start();
                    }
                    else
                    {
                        from = 1;
                        to = 0;
                    }
                }
            }
        }
    }

    Image {
        id: taskBorder

        x: 17
        y: 1390
        width: 1046
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 17
        y: 1396
        width: 1048
        height: 68

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            anchors.rightMargin: 421
            anchors.leftMargin: 418

            anchors.fill: parent

            onClicked: backClicked()
        }
    }

    Item {
        id: previous

        x: 27
        y: 1396
        width: 1028
        height: 68

        Text {
            id: previousText

            anchors.fill: parent
            color: "#94ef94"
            text: "< Previous"
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: previousButton

            anchors.rightMargin: 697

            anchors.fill: parent

            onClicked: root.goToPrevious()
        }
    }

    Item {
        id: next

        x: 27
        y: 1396
        width: 1028
        height: 68

        Text {
            id: nextText

            anchors.fill: parent
            color: "#94ef94"
            text: "Next >"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: nextButton

            anchors.leftMargin: 831

            anchors.fill: parent

            onClicked: root.goToNext()
        }
    }

    states: [
        State {
            name: "hiddenDown"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 300 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
