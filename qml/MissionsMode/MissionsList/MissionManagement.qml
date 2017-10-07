import QtQuick 2.9
import QtGraphicalEffects 1.0

import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440

    property string name_

    signal abortClicked()

    function reactToBackOnToolbar()
    {
        return false;
    }

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        var am=GameApi.base.heroes.amountOfHeroes();
        var intName = GameApi.globalsCpp.alterNormalTextToInternal(name_);
        for (var i=0;i<am;++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);
            if (GameApi.base.heroes.preparedHero.name() == intName)
            {
                if (GameApi.base.heroes.preparedHero.isCommunicationAvailable())
                {
                    connectionBackground.source = "qrc:/graphics/GUI/Connected.png";
                    connectionLostText.stopShowing();
                    noSignalAbortText.setNoSignal(0);
                }
                else
                {
                    connectionBackground.source = "qrc:/graphics/GUI/Disconnected.png";
                    connectionLostText.startShowing();
                    noSignalAbortText.setNoSignal(1);
                }

                break;
            }
        }
    }

    function setHero(heroName)
    {
        name_=heroName;
        updateEverything();
    }

    function show()
    {
        state = "";
        abortMA.visible = true;
    }
    function hide()
    {
        state = "hidden";
        abortMA.visible = false;
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: connectionBackground
        x: -60
        y: 120
        width: 1200
        height: 1200

        opacity: 0

        source: "qrc:/graphics/GUI/Connected.png"
    }
    GaussianBlur {
        anchors.fill: connectionBackground
        source: connectionBackground
        opacity: 0.4
        radius: 60
        samples: 30
        deviation: 30
        cached: true
    }

    Item {
        y: 1100
        width: parent.width
        height: 150

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter

            color: "#680000"
            font.family: fontStencil.name
            font.pixelSize: 150
            text: "Abort"
        }
        MouseArea {
            id: abortMA

            anchors.fill: parent

            visible: false

            onClicked: {
                GameApi.logger.trace("Abort clicked");
                var am=GameApi.base.heroes.amountOfHeroes();
                var intName = GameApi.globalsCpp.alterNormalTextToInternal(name_);
                for (var i=0;i<am;++i)
                {
                    GameApi.base.heroes.prepareHeroAt(i);
                    if (GameApi.base.heroes.preparedHero.name() == intName)
                    {
                        GameApi.base.heroes.preparedHero.assignedMission.abort();
                        root.abortClicked();
                        break;
                    }
                }
            }
        }
    }

    Text {
        id: connectionLostText

        x: 0
        y: 35
        width: parent.width

        horizontalAlignment: Text.AlignHCenter

        color: "#bf0000"
        font.family: fontStencil.name
        font.pixelSize: 100
        text: "Connection lost!"

        opacity: 0

        property bool isShowing: false

        function startShowing()
        {
            if (isShowing == false)
            {
                connectionLostTextFadeOut.start();
                connectionLostTextBlinking.toRunOrNotToRun=true;
                connectionLostTextBlinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                connectionLostTextFadeIn.start();
                connectionLostTextBlinking.toRunOrNotToRun=false;
                connectionLostTextBlinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: connectionLostTextFadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: [
                connectionLostText
            ]
        }
        NumberAnimation {
            id: connectionLostTextFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: [
                connectionLostText
            ]
        }
        NumberAnimation {
            id: connectionLostTextBlinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 2000
            from: 1
            to: 0.5
            targets: [
                connectionLostText
            ]
            onRunningChanged: {
                if (running == false && toRunOrNotToRun == true)
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

                    running = true;
                }
            }
        }

    }

    Text {
        id: noSignalAbortText
        x: 20
        y: 197
        width: 1040

        horizontalAlignment: Text.AlignHCenter

        function setNoSignal(noSignal)
        {
            if (noSignal)
                text = "We've lost track of "+GameApi.tr(root.name_)+". It means that something disrupts connection or connection module in the suit is damaged. In the worst case this mercenary is dead. Each day without a sign of living influences stress level of all mercenaries (including the lost one), especially with similar character type.";
            else
                text = "";
        }

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 50
        wrapMode: Text.WordWrap
    }

    Text {
        id: abortText

        x: 20
        y: 793
        width: 1040

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 50
        text: "You can abort mission at any time, but be wary that you will sentence your mercenary to death. Aborting mission will affect other mercenaries stress condition."
        wrapMode: Text.WordWrap
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; opacity: 0.0 }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
