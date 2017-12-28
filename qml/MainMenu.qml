import QtQuick 2.9

import Game 1.0

Item {
    id: root

    width: 1080
    height: 1920

    function update()
    {
        backgroundSkyMove.duration = backgroundSkyMove.baseDuration * GameApi.animMultiplier();
        backgroundPlanetMove.duration = backgroundPlanetMove.baseDuration * GameApi.animMultiplier();
        backgroundMoonMove.duration = backgroundMoonMove.baseDuration * GameApi.animMultiplier();
        titleFadeOut.duration = titleFadeOut.baseDuration * GameApi.animMultiplier();
        newGameFadeOut.duration = newGameFadeOut.baseDuration * GameApi.animMultiplier();
        loadGameFadeOut.duration = loadGameFadeOut.baseDuration * GameApi.animMultiplier();
        settingsFadeOut.duration = settingsFadeOut.baseDuration * GameApi.animMultiplier();
        creditsFadeOut.duration = creditsFadeOut.baseDuration * GameApi.animMultiplier();
        exitFadeOut.duration = exitFadeOut.baseDuration * GameApi.animMultiplier();
        overlayFadeOut.duration = overlayFadeOut.baseDuration * GameApi.animMultiplier();
    }

    function startAnimations()
    {
        titleFadeOut.start();
    }

    Image {
        id: backgroundSky

        x: -0.05 * root.width
        y: -0.05 * root.height
        width: 1.1 * root.width
        height: 1.1 * root.height

        source: "qrc:/graphics/SplashSky.png"

        NumberAnimation {
            id: backgroundSkyMove

            properties: "x"
            easing.type: Easing.Linear
            property int baseDuration: 20000
            duration: baseDuration
            from: backgroundSky.x
            to: -0.1 * root.width
            target: backgroundSky

            onRunningChanged: {
                if (!running)
                {
                    if (to == -0.1 * root.width)
                    {
                        from = to;
                        to = 0;
                        running = true;
                    }
                    else
                    {
                        from = to;
                        to = -0.1 * root.width;
                        running = true;
                    }
                }
            }
        }
    }

    Image {
        id: backgroundPlanet

        x: -0.05 * root.width
        y: -0.05 * root.height
        width: 1.1 * root.width
        height: 1.1 * root.height

        source: "qrc:/graphics/SplashPlanet.png"

        NumberAnimation {
            id: backgroundPlanetMove

            properties: "x"
            easing.type: Easing.Linear
            property int baseDuration: 20000
            duration: baseDuration
            from: backgroundPlanet.x
            to: -0.15 * root.width
            target: backgroundPlanet

            onRunningChanged: {
                if (!running)
                {
                    if (to == -0.15 * root.width)
                    {
                        from = to;
                        to = 0.05;
                        running = true;
                    }
                    else
                    {
                        from = to;
                        to = -0.15 * root.width;
                        running = true;
                    }
                }
            }
        }
    }

    Image {
        id: backgroundMoon

        x: -0.05 * root.width
        y: -0.05 * root.height
        width: 1.1 * root.width
        height: 1.1 * root.height

        source: "qrc:/graphics/SplashMoon.png"

        NumberAnimation {
            id: backgroundMoonMove

            properties: "x"
            easing.type: Easing.Linear
            property int baseDuration: 20000
            duration: baseDuration
            from: backgroundMoon.x
            to: -0.3 * root.width
            target: backgroundMoon

            onRunningChanged: {
                if (!running)
                {
                    if (to == -0.3 * root.width)
                    {
                        from = to;
                        to = 0.2;
                        running = true;
                    }
                    else
                    {
                        from = to;
                        to = -0.3 * root.width;
                        running = true;
                    }
                }
            }
        }
    }

    Image {
        x: root.width - width - 20
        y: root.height - width - 20
        width: 150
        height: width

        source: "qrc:/graphics/Logo.png"
    }

    Text {
        id: title

        x: 20
        y: 20

        opacity: 0

        color: "#94ef94"
        text: "Adversity"
        font.pixelSize: 150
        font.family: fontStencil.name

        NumberAnimation {
            id: titleFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 1000
            duration: baseDuration
            from: 0
            to: 1
            target: title

            onRunningChanged: {
                if (!running)
                    titleTimer.start();
            }
        }

        Timer {
            id: titleTimer

            running: false
            repeat: false
            interval: 600

            onTriggered: newGameFadeOut.start();
        }
    }
    Item {
        id: newGame

        x: 20
        y: 1000
        width: 636
        height: 118

        opacity: 0

        Text {
            x: 0
            y: 0

            color: "#94ef94"
            text: "New Game"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
        }
        Image {
            x: parent.width - width
            y: 0
            width: parent.height
            height: width

            source: "qrc:/graphics/MainMenu/Save_New.png"
        }

        NumberAnimation {
            id: newGameFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 200
            duration: baseDuration
            from: 0
            to: 1
            target: newGame

            onRunningChanged: {
                if (running)
                {
                    newGameTimer.interval = newGameFadeOut.duration;
                    newGameTimer.start();
                }
            }
        }

        Timer {
            id: newGameTimer

            running: false
            repeat: false

            onTriggered: loadGameFadeOut.start();
        }
    }
    Item {
        id: loadGame

        x: 20
        y: newGame.y + newGame.height + 20
        width: 680
        height: 118

        opacity: 0

        Text {
            x: 0
            y: 0

            color: "#94ef94"
            text: "Load Game"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
        }
        Image {
            x: parent.width - width
            y: 0
            width: 118
            height: width

            source: "qrc:/graphics/MainMenu/Save_Copy.png"
        }

        NumberAnimation {
            id: loadGameFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 200
            duration: baseDuration
            from: 0
            to: 1
            target: loadGame

            onRunningChanged: {
                if (running)
                {
                    loadGameTimer.interval = loadGameFadeOut.duration;
                    loadGameTimer.start();
                }
            }
        }

        Timer {
            id: loadGameTimer

            running: false
            repeat: false

            onTriggered: settingsFadeOut.start();
        }
    }
    Item {
        id: settings

        x: 20
        y: loadGame.y + loadGame.height + 20
        width: 610
        height: 118

        opacity: 0

        Text {
            x: 0
            y: 0

            color: "#94ef94"
            text: "Settings"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
        }
        Image {
            x: parent.width - width
            y: 0
            width: 118
            height: width

            source: "qrc:/graphics/MainMenu/Settings.png"
        }

        NumberAnimation {
            id: settingsFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 200
            duration: baseDuration
            from: 0
            to: 1
            target: settings

            onRunningChanged: {
                if (running)
                {
                    settingsTimer.interval = settingsFadeOut.duration;
                    settingsTimer.start();
                }
            }
        }

        Timer {
            id: settingsTimer

            running: false
            repeat: false

            onTriggered: creditsFadeOut.start();
        }
    }
    Item {
        id: credits

        x: 20
        y: settings.y + settings.height + 20
        width: 570
        height: 118

        opacity: 0

        Text {
            x: 0
            y: 0

            color: "#94ef94"
            text: "Credits"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
        }
        Image {
            x: parent.width - width
            y: 0
            width: 118
            height: width

            source: "qrc:/graphics/GUI/Slots/MercenarySlot.png"
        }

        NumberAnimation {
            id: creditsFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 200
            duration: baseDuration
            from: 0
            to: 1
            target: credits

            onRunningChanged: {
                if (running)
                {
                    creditsTimer.interval = creditsFadeOut.duration;
                    creditsTimer.start();
                }
            }
        }

        Timer {
            id: creditsTimer

            running: false
            repeat: false

            onTriggered: exitFadeOut.start();
        }
    }
    Item {
        id: exit

        x: 20
        y: credits.y + credits.height + 20
        width: 380
        height: 118

        opacity: 0

        Text {
            x: 0
            y: 0

            color: "#94ef94"
            text: "Exit"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
        }
        Image {
            x: parent.width - width
            y: 0
            width: 118
            height: width

            source: "qrc:/graphics/MainMenu/Exit.png"
        }

        NumberAnimation {
            id: exitFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 200
            duration: baseDuration
            from: 0
            to: 1
            target: exit

            onRunningChanged: {
                if (!running)
                {
                    backgroundSkyMove.start();
                    backgroundPlanetMove.start();
                    backgroundMoonMove.start();
                }
            }
        }
    }
    Image {
        id: overlay

        anchors.fill: parent

        source: "qrc:/graphics/MainMenu/Overlay.png"

        opacity: 0

        NumberAnimation {
            id: overlayFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 250
            duration: baseDuration
            from: 0
            target: overlay

            onRunningChanged: {
                if (!running)
                {
                    if (from == 0)
                    {
                        from = 1;
                        to = 0;
                        running = true;
                    }
                    else
                    {
                        from = 0;
                        to = 1;
                        overlayTimer.interval = GameApi.randomize(5, 30) * 1000;
                        overlayTimer.start();
                    }
                }
            }
        }

        Timer {
            id: overlayTimer

            running: true
            repeat: true

            onTriggered: overlayFadeOut.start();
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    Timer {
        id: x
        interval: 2000
        onRunningChanged: {
            if (!running)
                startAnimations();
        }
    }

    Component.onCompleted: startAnimations();
}
