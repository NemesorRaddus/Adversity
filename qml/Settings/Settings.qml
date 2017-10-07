import QtQuick 2.9
import QtQml 2.2

import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440

    signal backClicked()

    state: "hidden"

    function show()
    {
        state = "";

        leftArrow.visible = true;
        rightArrow.visible = true;
        leftArrowLogs.visible = true;
        rightArrowLogs.visible = true;
        fpsMA.visible = true;
        exitMA.visible = true;
        creditsMA.visible = true;
        backButton.visible = true;
    }

    function hide()
    {
        state = "hidden";

        leftArrow.visible = false;
        rightArrow.visible = false;
        leftArrowLogs.visible = false;
        rightArrowLogs.visible = false;
        fpsMA.visible = false;
        exitMA.visible = false;
        creditsMA.visible = false;
        backButton.visible = false;

        creditsComp.hide();
    }

    function returnToDefault()
    {
        creditsComp.hide();
    }

    function reactToBackOnToolbar()
    {
        if (creditsComp.state == "")
        {
            creditsComp.hide();
            return true;
        }
        return false;
    }

    function acknowledgeFPSToggle(show)
    {
        if (show)
        {
            showFpsIcon.state = "";
            anim.start();
        }
        else
        {
            showFpsIcon.state = "off";
            anim.stop();
        }
    }

    function update()
    {
        transitionShowFPS.duration = transitionShowFPS.baseDuration * GameApi.animMultiplier();
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();
        animsFadeIn.duration = animsFadeIn.baseDuration * GameApi.animMultiplier();
        animsFadeOut.duration = animsFadeOut.baseDuration * GameApi.animMultiplier();

        versionNumber.text = GameApi.currentVersionNumber();
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Text {
        y: 8
        width: root.width

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.pixelSize: 80
        font.family: fontStencil.name
        text: "Settings"
    }

    Image {
        id: taskBorderTitle

        x: 17
        y: 98

        width: 1048
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        x: 17
        y: 150

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Animations"
        }

        Text {
            id: arrowL
            x: 590
            width: 460
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "<"
        }
        Text {
            id: arrowR
            x: 590
            width: 460
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "                            >"
        }

        Text {
            id: animsText

            x: arrowL.x
            width: arrowR.width
            color: "#94ef94"
            font.pixelSize: arrowL.font.pixelSize
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            property int option: -1

            onOptionChanged: {
                animsFadeIn.start();
            }

            Component.onCompleted: option = GameApi.animationSpeed();

            NumberAnimation {
                id: animsFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                property int baseDuration: 300
                duration: baseDuration
                from: 1
                to: 0
                target: animsText
                onRunningChanged: {
                    if (running == false)
                    {
                        if (animsText.option == 0)
                        {
                            animsText.text = "None";
                            GameApi.setAnimationsSpeed(0);
                            arrowL.visible = false;
                            arrowR.visible = true;
                        }
                        else if (animsText.option == 1)
                        {
                            animsText.text = "Slow";
                            GameApi.setAnimationsSpeed(1);
                            arrowL.visible = true;
                            arrowR.visible = true;
                        }
                        else if (animsText.option == 2)
                        {
                            animsText.text = "Normal";
                            GameApi.setAnimationsSpeed(2);
                            arrowL.visible = true;
                            arrowR.visible = true;
                        }
                        else if (animsText.option == 3)
                        {
                            animsText.text = "Fast";
                            GameApi.setAnimationsSpeed(3);
                            arrowL.visible = true;
                            arrowR.visible = false;
                        }

                        animsFadeOut.start();
                    }
                }
            }
            NumberAnimation {
                id: animsFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                property int baseDuration: 300
                duration: baseDuration
                from: 0
                to: 1
                target: animsText
            }
        }
        MouseArea {
            id: leftArrow

            x: arrowL.x-10
            y: -10
            width: 65
            height: arrowL.height-2*y

            visible: false

            onClicked: {
                if (animsText.option > 0)
                    --animsText.option;
            }
        }
        MouseArea {
            id: rightArrow
            x: arrowR.x+arrowR.width-width+10
            y: leftArrow.y
            width: leftArrow.width
            height: leftArrow.height

            visible: false

            onClicked: {
                if (animsText.option < 3)
                    ++animsText.option;
            }
        }
    }

    Item {
        x: 17
        y: 240

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Show fps"
        }

        Image {
            id: showFpsIcon

            x: 940
            y: -10

            width: 80
            height: width

            source: "qrc:/graphics/GUI/Settings.png"

            state: "off"

            function setOn()
            {
                state = "";
                anim.start();
                GameApi.showFPS(true);
            }

            function setOff()
            {
                state = "off";
                anim.stop();
                GameApi.showFPS(false);
            }

            MouseArea {
                id: fpsMA

                anchors.fill: parent

                visible: false

                onClicked: {
                    if (parent.state == "off")
                        parent.setOn();
                    else
                        parent.setOff();
                }
            }

            RotationAnimator on rotation {
                id: anim
                from: 0;
                to: 360;
                duration: 2500
                loops: RotationAnimation.Infinite
                running: false
            }

            states: State {
                name: "off"
                PropertyChanges { target: showFpsIcon; opacity: 0.5 }
            }

            transitions: Transition {
                NumberAnimation { id: transitionShowFPS; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
            }
        }
    }

    Item {
        x: 17
        y: 330

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Logs"
        }

        Text {
            id: arrowLLogs
            x: 590
            width: 460
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "<"
        }
        Text {
            id: arrowRLogs
            x: 590
            width: 460
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "                            >"
        }

        Text {
            id: logsText

            x: arrowLLogs.x
            width: arrowRLogs.width
            color: "#94ef94"
            font.pixelSize: arrowLLogs.font.pixelSize
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            property int option: -1
            property int lastSavedOption: GameApi.logsAmount();

            onOptionChanged: {
                logsFadeIn.start();
            }

            Component.onCompleted: option = GameApi.logsAmount();

            NumberAnimation {
                id: logsFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                property int baseDuration: 300
                duration: baseDuration
                from: 1
                to: 0
                target: logsText
                onRunningChanged: {
                    if (running == false)
                    {
                        if (logsText.option == 0)
                        {
                            logsText.text = "None";
                            permissionsText.visible = false;
                            GameApi.setLogsAmount(0);
                            arrowLLogs.visible = false;
                            arrowRLogs.visible = true;
                            if (logsText.option != logsText.lastSavedOption)
                                pleaseRestartText.visible = true;
                            else
                                pleaseRestartText.visible = false;
                        }
                        else if (logsText.option == 1)
                        {
                            logsText.text = "Some";
                            GameApi.requestReadWritePermissions();
                            permissionsText.visible = true;
                            GameApi.setLogsAmount(1);
                            arrowLLogs.visible = true;
                            arrowRLogs.visible = true;
                            if (logsText.option != logsText.lastSavedOption)
                                pleaseRestartText.visible = true;
                            else
                                pleaseRestartText.visible = false;
                        }
                        else if (logsText.option == 2)
                        {
                            logsText.text = "Most";
                            permissionsText.visible = true;
                            GameApi.setLogsAmount(2);
                            arrowLLogs.visible = true;
                            arrowRLogs.visible = true;
                            if (logsText.option != logsText.lastSavedOption)
                                pleaseRestartText.visible = true;
                            else
                                pleaseRestartText.visible = false;
                        }
                        else if (logsText.option == 3)
                        {
                            logsText.text = "All";
                            permissionsText.visible = true;
                            GameApi.setLogsAmount(3);
                            arrowLLogs.visible = true;
                            arrowRLogs.visible = false;
                            if (logsText.option != logsText.lastSavedOption)
                                pleaseRestartText.visible = true;
                            else
                                pleaseRestartText.visible = false;
                        }

                        logsFadeOut.start();
                    }
                }
            }
            NumberAnimation {
                id: logsFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                property int baseDuration: 300
                duration: baseDuration
                from: 0
                to: 1
                target: logsText
            }
        }
        MouseArea {
            id: leftArrowLogs

            x: arrowLLogs.x-10
            y: -10
            width: 65
            height: arrowLLogs.height-2*y

            visible: false

            onClicked: {
                if (logsText.option > 0)
                    --logsText.option;
            }
        }
        MouseArea {
            id: rightArrowLogs
            x: arrowRLogs.x+arrowRLogs.width-width+10
            y: leftArrowLogs.y
            width: leftArrowLogs.width
            height: leftArrowLogs.height

            visible: false

            onClicked: {
                if (logsText.option < 3)
                    ++logsText.option;
            }
        }
    }

    Item {
        x: 17
        y: 420

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Exit game"
        }

        Image {
            id: exitGame

            x: 950

            width: 60
            height: width

            source: "qrc:/graphics/GUI/Abort.png"

            MouseArea {
                id: exitMA

                anchors.fill: parent

                anchors.margins: -10

                visible: false

                onClicked: {
                    Qt.quit();
                }
            }
        }
    }

    Item {
        x: 17
        y: 510

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Credits"
        }

        Image {
            id: credits

            x: 950

            width: 60
            height: width

            source: "qrc:/graphics/GUI/Profitability.png"

            MouseArea {
                id: creditsMA
                anchors.fill: parent

                anchors.margins: -10

                onClicked: creditsComp.show();
            }
        }
    }

    Text {
        id: permissionsText

        x: 17
        y: 750
        width: parent.width - 2*x

        horizontalAlignment: Text.AlignHCenter

        visible: false

        text: "Android read/write permission must be granted to save logs."
        color: "#c0efc0"
        font.pixelSize: 50
        font.family: fontStencil.name
        wrapMode: Text.Wrap
    }

    Text {
        id: logsPathText

        x: 17
        y: 900
        width: parent.width - 2*x

        horizontalAlignment: Text.AlignHCenter

        function setPath(path)
        {
            if (path == "" || path == undefined)
                text = "";
            else
                text = "Logs are saved in:\n"+path;
        }

        color: "#94ef94"
        font.pixelSize: 50
        font.family: fontStencil.name
        wrapMode: Text.Wrap

        Component.onCompleted: setPath(GameApi.pathToLogs());
    }

    Text {
        id: pleaseRestartText

        x: 17
        y: 1130
        width: parent.width - 2*x

        horizontalAlignment: Text.AlignHCenter

        visible: false

        color: "#94ef94"
        font.pixelSize: 60
        font.family: fontStencil.name
        text: "Please restart the game"
    }

    Text {
        id: versionNumber

        x: 17
        y: 1250

        color: "#94ef94"
        font.pixelSize: 60
        font.family: fontStencil.name
        text: "v1.0.0"
    }

    Image {
        id: taskBorderBottom

        x: 17
        y: 1334

        width: 1048
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 400
        y: 1344
        width: 260
        height: 120

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            visible: false

            anchors.fill: parent

            onClicked: backClicked()
        }
    }

    Credits {
        id: creditsComp

        anchors.fill: parent

        onBackClicked: hide();
    }

    states: State {
        name: "hidden"
        PropertyChanges { target: root; opacity: 0.0 }
    }

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 200 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
