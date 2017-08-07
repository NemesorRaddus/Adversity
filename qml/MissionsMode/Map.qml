import QtQuick 2.0

import "LandmarkScripts.js" as Scripts
import ".."
import Game 1.0

Item {
    id: root

    signal exploreClicked(string areaName)

    function returnToDefault()
    {
        landmarksManager.hideInfo();
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
                    mapImage.move(Math.ceil(mapMA.mouseX) - mapMA.x0, Math.ceil(mapMA.mouseY) - mapMA.y0);

                    mapMA.x0 = Math.ceil(mapMA.mouseX);
                    mapMA.y0 = Math.ceil(mapMA.mouseY);
                }
                else
                {
                    if ((Math.abs(mapMA.mouseX - mapMA.x0) >= Globals.windowWidth * mapMA.coordChangedThresholdForScrolling / 100) || (Math.abs(mapMA.mouseY - mapMA.y0) >= Globals.windowHeight * mapMA.coordChangedThresholdForScrolling / 100))
                    {
                        mapMA.isScrollingActive = true;
                        mapImage.move(mapMA.mouseX - mapMA.x0, mapMA.mouseY - mapMA.y0);
                        mapMA.x0 = mapMA.mouseX;
                        mapMA.y0 = mapMA.mouseY;
                    }
                }
            }
        }
    }

    Image {
        id: mapImage

        x: -(width - root.width)/2
        y: -(height - root.height)/2

        source: "qrc:/graphics/Missions/Map.png"

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
            target: mapImage
            property: "opacity"
            running: true
        }

        Item {
            id: landmarksManager

            readonly property int landmarkIconSize: 100 // = width = height

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

                landmarkInfo.visible = true;
            }
            function hideInfo()
            {
                landmarkInfo.visible = false;
                landmarkInfo.setName("");
            }

            Item { // to make icons appear under landmark info
                id: landmarksManagerIconsHandler
            }

            Rectangle {
                id: landmarkInfo

                visible: false

                width: 800
                height: landmarkArt.height + landmarkArt.y*2 + 100

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
                    font.pixelSize: 50
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
                    font.pixelSize: 40
                    font.family: fontStencil.name

                    wrapMode: Text.WordWrap
                    maximumLineCount: 5
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
                    width: 300
                    height: width
                }

                MouseArea {
                    id: landmarkInfoBoxClicksCatcher

                    anchors.fill: parent
                }

                Item {
                    id: exploreButton

                    x: landmarkDesc.x + landmarkDesc.width/2
                    y: landmarkDesc.y + landmarkDesc.height + 10
                    width: 200
                    height: exploreText.font.pixelSize + 4

                    Text {
                        id: exploreText

                        anchors.fill: parent

                        color: "#94ef94"
                        font.pixelSize: 50
                        font.family: fontStencil.name
                        text: "Explore"
                    }
                    MouseArea {
                        id: exploreMA

                        anchors.fill: parent

                        onClicked: exploreClicked(landmarkName.text)
                    }
                }
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    Component.onCompleted: {
        Scripts.setupList(3);
        Scripts.createItem(1150,450,landmarksManager.landmarkIconSize,"Super Plains", "Plainlands","Yay, plains!!!");
        Scripts.createItem(1150,1600,landmarksManager.landmarkIconSize,"Friggin Desert", "Desert","Please no...");
        Scripts.createItem(550,950,landmarksManager.landmarkIconSize,"Forrest's Forest", "Forest","Lots of trees you have there m8");
    }
}
