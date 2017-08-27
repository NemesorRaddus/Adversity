import QtQuick 2.0

import "LandmarkScripts.js" as Scripts
import ".."
import Game 1.0

Item {
    id: root

    signal exploreClicked(string intLandName, string landName, string landDesc)

    function returnToDefault()
    {
        landmarksManager.hideInfo();
        mapImageItem.returnToDefault();
    }

    function updateEverything()
    {

    }

    MouseArea {
        id: mapMA

        readonly property int coordChangedThresholdForScrolling: 1 // percent; <0;100>; after moving  by this percent of screen width or height, scrolling mode will be activated and mouse release will no longer cause click - instead map will be scrolled

        property int x0: -1
        property int y0: -1
        property bool isScrollingActive: false

        anchors.fill: parent

        signal requestLandmarkInfoClosing()

        onPressed: {
            x0 = mouseX;
            y0 = mouseY;
            movementCheckTimer.start();
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else if (root.state == "")
                landmarksManager.hideInfo();
            x0 = -1;
            y0 = -1;
            movementCheckTimer.stop();
        }

        Timer {
            id: movementCheckTimer

            interval: 16
            repeat: true
            running: false

            onTriggered: {
                if (mapMA.isScrollingActive == true)
                {
                    mapImageItem.move(Math.ceil(mapMA.mouseX) - mapMA.x0, Math.ceil(mapMA.mouseY) - mapMA.y0);

                    mapMA.x0 = Math.ceil(mapMA.mouseX);
                    mapMA.y0 = Math.ceil(mapMA.mouseY);
                }
                else
                {
                    if ((Math.abs(mapMA.mouseX - mapMA.x0) >= Globals.windowWidth * mapMA.coordChangedThresholdForScrolling / 100) || (Math.abs(mapMA.mouseY - mapMA.y0) >= Globals.windowHeight * mapMA.coordChangedThresholdForScrolling / 100))
                    {
                        mapMA.isScrollingActive = true;
                        mapImageItem.move(mapMA.mouseX - mapMA.x0, mapMA.mouseY - mapMA.y0);
                        mapMA.x0 = mapMA.mouseX;
                        mapMA.y0 = mapMA.mouseY;
                    }
                }
            }
        }
    }

    Item {
        id: mapImageItem

        property real customOpacity: 1.0

        x: -(width - root.width)/2
        y: -(height - root.height)/2
        width: mapImage.width
        height: mapImage.height

        function returnToDefault()
        {
            if (mapImage.status == Image.Ready)
            {
                x = -(width - root.width)/2;
                y = -(height - root.height)/2;
            }
        }

        function move(xChange,yChange)
        {
            x += xChange;
            y += yChange;

            if (x > 0)
                x = 0;
            else if (x < -root.width)
                x = -root.width;

            if (y > 0)
                y = 0;
            else if (y < -root.height)
                y = -root.height;
        }

        onCustomOpacityChanged: landmarksManagerIconsHandler.opacity = customOpacity; // this line is to suppress warning got when doing opacity: customOpacity there

        NumberAnimation {
            id: animMapLight

            from: GameApi.randomize(92,100)/100;
            to: GameApi.randomize(92,100)/100;

            onRunningChanged: {
                if (running == false)
                {
                    from = GameApi.randomize(92,100)/100;
                    to = GameApi.randomize(92,100)/100;
                    running = true;
                }
            }

            duration: 250
            target: mapImageItem
            property: "customOpacity"
            running: true
        }

        Image {
            id: mapImage

            opacity: parent.customOpacity

            source: "qrc:/graphics/Missions/Map.png"

            asynchronous: true
        }

        Item {
            id: landmarksManager

            readonly property int landmarkIconSize: 150 // = width = height

            function handleIconClick(centerX, centerY, name, description, art)
            {
                if (landmarkInfo.getName() == name)
                    hideInfo();
                else
                    showInfo(centerX, centerY, name, description, art);
            }

            function showInfo(centerX, centerY, name, description, art)
            {
                landmarkInfo.x = centerX-landmarkInfo.width/2;
                landmarkInfo.y = centerY-landmarkInfo.height/2;
                landmarkInfo.setName(name);
                landmarkInfo.setDescription(description);
                landmarkInfo.setArtSource(art);

                landmarkInfo.state = "";
                landmarkInfoBoxClicksCatcher.visible = true;
            }
            function hideInfo()
            {
                landmarkInfo.state = "hidden";
                landmarkInfoBoxClicksCatcher.visible = false;
                landmarkInfo.setName("");
            }

            Item { // to make icons appear under landmark info
                id: landmarksManagerIconsHandler
            }

            Rectangle {
                id: landmarkInfo

                width: 1000
                height: landmarkArt.height + landmarkArt.y*2

                color: "#171717"

                border.color: "#94ef94"
                border.width: 5

                function setName(name_)
                {
                    landmarkName.text = name_;
                }
                function setDescription(desc_)
                {
                    landmarkDesc.text = desc_;
                }
                function setArtSource(path_)
                {
                    landmarkArt.source = path_;
                }
                function getName()
                {
                    return landmarkName.text;
                }

                Text {
                    id: landmarkName

                    x: landmarkArt.x + landmarkArt.width + 10
                    y: landmarkArt.y
                    width: parent.width - x - 20
                    height: font.pixelSize + 6

                    color: "#94ef94"
                    font.pixelSize: 60
                    font.family: fontStencil.name
                    horizontalAlignment: Text.AlignHCenter

                    wrapMode: Text.NoWrap
                }
                Text {
                    id: landmarkDesc

                    x: landmarkName.x
                    y: landmarkName.y + landmarkName.height
                    width: parent.width - x - 20
                    height: (font.pixelSize + 6)*maximumLineCount

                    color: "#94ef94"
                    font.pixelSize: 45
                    font.family: fontStencil.name

                    wrapMode: Text.WordWrap
                    maximumLineCount: 3
                }
                Rectangle {
                    id: landmarkArtRect

                    x: 0
                    y: 0
                    width: landmarkArt.width + border.width*2
                    height: width

                    border.width: 5
                    border.color: "#94ef94"
                }

                Image {
                    id: landmarkArt

                    x: landmarkArtRect.border.width
                    y: landmarkArtRect.border.width
                    width: 400
                    height: width
                }

                MouseArea {
                    id: landmarkInfoBoxClicksCatcher

                    anchors.fill: parent
                }

                Item {
                    id: exploreButton

                    x: parent.width - width
                    y: parent.height - height
                    width: 280
                    height: exploreText.font.pixelSize + 8

                    Text {
                        id: exploreText

                        anchors.fill: parent

                        color: "#94ef94"
                        font.pixelSize: 60
                        font.family: fontStencil.name
                        text: "Explore"
                    }
                    MouseArea {
                        id: exploreMA

                        x: -20
                        y: -20
                        width: parent.width - 2*x
                        height: parent.height - 2*y

                        onClicked: {
                            var intName=""+landmarkArt.source;
                            intName=intName.slice(intName.lastIndexOf("/")+1,-4);
                            exploreClicked(intName, landmarkName.text, landmarkDesc.text);
                        }
                    }
                }

                states: [
                    State {
                        name: "hidden"
                        PropertyChanges { target: landmarkInfo; opacity: 0 }
                    }
                ]

                transitions: Transition {
                    NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 100 }
                }
            }
        }
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -width }
        },
        State {
            name: "hiddenLeft2"
            PropertyChanges { target: root; x: -2*width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    Component.onCompleted: {
        var am=GameApi.lands.amountOfLands();
        Scripts.setupList(am);
        for (var i=0;i<am;++i)
        {
            GameApi.lands.prepareLandAt(i);
            Scripts.createItem(GameApi.lands.preparedLand.posX(),GameApi.lands.preparedLand.posY(),landmarksManager.landmarkIconSize,GameApi.lands.preparedLand.name(),GameApi.globalsCpp.alterNormalTextToInternal(GameApi.lands.preparedLand.name()),GameApi.lands.preparedLand.description());
        }
    }
}
