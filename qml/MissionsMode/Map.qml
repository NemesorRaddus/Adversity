import QtQuick 2.9

import "LandmarkScripts.js" as Scripts
import ".."
import Game 1.0

Item {
    id: root

    signal exploreClicked(string intLandName, string landName)
    signal databaseClicked()
    signal missionsClicked()

    function returnToDefault()
    {
        landmarksManager.hideInfo();
        mapImageItem.returnToDefault();
    }

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();
        transitionLandmarkInfo.duration = transitionLandmarkInfo.baseDuration * GameApi.animMultiplier();
        transitionMissionButton.duration = transitionMissionButton.baseDuration * GameApi.animMultiplier();
        transitionDatabaseButton.duration = transitionDatabaseButton.baseDuration * GameApi.animMultiplier();
        missionShowTimer.interval = missionShowTimer.baseInterval * GameApi.animMultiplier();
        databaseShowTimer.interval = databaseShowTimer.baseInterval * GameApi.animMultiplier();
        databaseNewEntryAnimation.duration = databaseNewEntryAnimation.baseDuration * GameApi.animMultiplier();

        if (GameApi.base.database.areThereNewEntries())
            databaseButton.startAnimating();
        else
            databaseButton.stopAnimating();
    }

    function acknowledgeModeStateChange(currentState)
    {
        if (currentState == "")
        {
            databaseShowTimer.start();
            missionShowTimer.start();
        }
        else
        {
            databaseButton.state = "hidden";
            missionButton.state = "hidden";
        }
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
                if (centerX+landmarkInfo.width/2 < mapImage.width)
                    landmarkInfo.x = centerX-landmarkInfo.width/2;
                else
                    landmarkInfo.x = mapImage.width-landmarkInfo.width;
                if (centerY+landmarkInfo.height/2 < mapImage.height)
                    landmarkInfo.y = centerY-landmarkInfo.height/2;
                else
                    landmarkInfo.y = mapImage.height-landmarkInfo.height;
                landmarkInfo.setName(name);
                landmarkInfo.setDescription(description);
                landmarkInfo.setArtSource(art);

                landmarkInfo.state = "";
                landmarkInfoBoxClicksCatcher.visible = true;
                landmarkDescFlickable.visible = true;
                exploreMA.visible = true;
            }
            function hideInfo()
            {
                landmarkInfo.state = "hidden";
                landmarkInfoBoxClicksCatcher.visible = false;
                landmarkInfo.setName("");
                landmarkDescFlickable.visible = false;
                exploreMA.visible = false;
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

                MouseArea {
                    id: landmarkInfoBoxClicksCatcher

                    anchors.fill: parent
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
                Flickable {
                    id: landmarkDescFlickable

                    x: landmarkName.x
                    y: landmarkName.y + landmarkName.height
                    width: parent.width - x - 20
                    height: exploreButton.y-y

                    visible: false

                    boundsBehavior: Flickable.StopAtBounds

                    contentWidth: landmarkDesc.width
                    contentHeight: landmarkDesc.height

                    clip: true

                    Text {
                        id: landmarkDesc

                        width: parent.width
                        height: landmarkDescMetrics.boundingRect.height*lineCount

                        color: "#94ef94"
                        font.pixelSize: 40
                        font.family: fontStencil.name

                        wrapMode: Text.WordWrap
                    }
                    TextMetrics {
                        id: landmarkDescMetrics

                        font: landmarkDesc.font
                        text: landmarkDesc.text
                    }
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

                        visible: false

                        onClicked: {
                            var intName=""+landmarkArt.source;
                            intName=intName.slice(intName.lastIndexOf("/")+1,-4);
                            exploreClicked(intName, landmarkName.text);
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
                    NumberAnimation { id: transitionLandmarkInfo; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 100 }
                }
            }
        }
    }

    Item {
        id: databaseButton

        x: 10
        y: parent.height-height
        width: 100
        height: 135

        state: "hidden"

        property bool isAnimationActive: false

        function startAnimating()
        {
            isAnimationActive=true;
            databaseNewEntryAnimation.start();
        }

        function stopAnimating()
        {
            isAnimationActive=false;
            databaseNewEntryAnimation.stop();
            databaseButtonIcon.opacity=1.0;
        }

        Rectangle {
            anchors.fill: parent

            color: "#94ef94"

            Rectangle {
                x: 5
                y: 5
                width: 90
                height: 130

                color: "#171717"

                Image {
                    id: databaseButtonIcon

                    x: 5
                    y: 10
                    width: 80
                    height: 120

                    source: "qrc:/graphics/GUI/Database.png"
                }
            }
        }

        NumberAnimation {
            id: databaseNewEntryAnimation

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 1200
            duration: baseDuration
            from: 1
            to: 0.5
            target: databaseButtonIcon
            onRunningChanged: {
                if (running == false && databaseButton.isAnimationActive)
                {
                    if (from == 1)
                    {
                        from = 0.5;
                        to = 1;
                    }
                    else
                    {
                        from = 1;
                        to = 0.5;
                    }
                    start();
                }
            }
        }

        Timer {
            id: databaseShowTimer

            property int baseInterval: 500
            interval: baseInterval

            running: false
            repeat: false

            onTriggered: {
                databaseButton.state = "";
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                GameApi.base.database.setAreThereNewUnlockedEntries(0);
                parent.stopAnimating();
                root.databaseClicked();
            }
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: databaseButton; y: root.height }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionDatabaseButton; properties: "y"; easing.type: Easing.OutQuint; duration: baseDuration; property int baseDuration: 1000 }
        }
    }

    Item {
        id: missionButton

        x: databaseButton.x+databaseButton.x+databaseButton.width+4
        y: parent.height-height
        width: 100
        height: 135

        state: "hidden"

        Rectangle {
            anchors.fill: parent

            color: "#94ef94"

            Rectangle {
                x: 5
                y: 5
                width: 90
                height: 130

                color: "#171717"

                Image {
                    x: 3
                    y: 4
                    width: 84
                    height: 126

                    source: "qrc:/graphics/GUI/Missions.png"
                }
            }
        }

        Timer {
            id: missionShowTimer

            property int baseInterval: 700
            interval: baseInterval

            running: false
            repeat: false

            onTriggered: {
                missionButton.state = "";
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: root.missionsClicked()
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: missionButton; y: root.height }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionMissionButton; properties: "y"; easing.type: Easing.OutQuint; duration: baseDuration; property int baseDuration: 1000 }
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
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
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
