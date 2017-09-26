import QtQuick 2.9
import QtGraphicalEffects 1.0

import Game 1.0

import "../.."
import ".."

Item {
    id: root

    width: 1080
    height: 1440

    signal reportsClicked()
    signal mercenaryClicked()
    signal missionManagementClicked()

    property string name_

    function update()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        var am = GameApi.base.heroes.amountOfHeroes();
        var intName = GameApi.globalsCpp.alterNormalTextToInternal(name_);
        for (var i=0;i<am;++i)
        {
            GameApi.base.heroes.prepareHeroAt(i);
            if (intName == GameApi.base.heroes.preparedHero.name())
            {
                var normalLandName = GameApi.base.heroes.preparedHero.assignedMission.land.name();
                landArt.source = "qrc:/graphics/Missions/Lands/" + GameApi.globalsCpp.alterNormalTextToInternal(normalLandName) + ".png";
                infoText.set(name_,normalLandName,GameApi.base.heroes.preparedHero.assignedMission.daysSpent());
                signalIcon.set(GameApi.base.heroes.preparedHero.isCommunicationAvailable());
                missionLengthIcon.set(normalLandName,GameApi.base.heroes.preparedHero.assignedMission.difficultyString());
                sbeActivationIcon.set(GameApi.base.heroes.preparedHero.isStressBorderEffectActive());
                break;
            }
        }
    }

    function setHero(name)
    {
        name_ = name;
        update();
    }

    Item {
        id: land
        width: root.width
        height: width

        opacity: 0.3

        Image {
            id: landArt

            anchors.fill: parent
            opacity: 0

            source: "qrc:/graphics/Missions/Lands/HegosPlains.png"
        }
        GaussianBlur {
            anchors.fill: landArt
            source: landArt
            radius: 60
            samples: 30
            deviation: 30
            cached: true
        }
    }
    Image {
        id: opMaskUp

        anchors.fill: land

        rotation: 180

        source: "qrc:/graphics/GUI/Mask.png"
    }
    Image {
        id: opMaskDown

        anchors.fill: land

        source: "qrc:/graphics/GUI/Mask.png"
    }

    Text {
        id: infoText

        x: 0
        y: 0
        width: root.width

        horizontalAlignment: Text.AlignHCenter

        function set(name, land, daysOnMission)
        {
            text = "\nMercenary:\n"+name+"\n\nLand:\n"+land+"\n\nDays on mission:\n"+daysOnMission+"\n";
        }

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 80
    }

    Item {
        id: buttons

        x: 200
        y: 873
        width: 680
        height: 323

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter

            color: "#94ef94"
            font.family: fontStencil.name
            font.pixelSize: 50
            text: "< Reports\n\nMercenary >\n\nMission management"
        }

        MouseArea {
            x: 117
            y: -23
            width: 452
            height: 100

            onClicked: reportsClicked()
        }

        MouseArea {
            x: 117
            y: 77
            width: 452
            height: 130

            onClicked: mercenaryClicked()
        }

        MouseArea {
            x: 0
            y: 208
            width: 680
            height: 115

            onClicked: missionManagementClicked()
        }
    }

    Image {
        x: 200
        y: 1070
        width: 50
        height: width

        source: "qrc:/graphics/GUI/Settings.png"
    }
    Image {
        x: 830
        y: 1070
        width: 50
        height: width
        source: "qrc:/graphics/GUI/Settings.png"
    }

    Item {
        id: missionIcons

        y: 1238

        Image {
            id: signalIcon

            x: missionLengthIcon.x-168
            width: 128
            height: width

            function set(signalOn)
            {
                source = "qrc:/graphics/GUI/" + (signalOn ? "Connected" : "Disconnected") + ".png";
            }

            source: "qrc:/graphics/GUI/Connected.png"
        }
        Image {
            id: missionLengthIcon

            x: 444
            y: -64
            width: 192
            height: width

            function set(land, length)
            {
                var s1,s2;
                s1=GameApi.globalsCpp.alterNormalTextToInternal(land);
                if (length == "Short")
                    s2="1";
                else if (length == "Medium")
                    s2="2";
                else if (length == "Long")
                    s2="3";
                else if (length == "Extreme")
                    s2="4";
                source = "qrc:/graphics/GUI/MissionLength/"+s1+s2+".png";
            }

            source: "qrc:/graphics/GUI/MissionLength/AuroraForest4.png"
        }
        Image {
            id: sbeActivationIcon

            x: missionLengthIcon.x+232
            width: 128
            height: width

            function set(sbeOn)
            {
                visible = sbeOn;
            }

            source: "qrc:/graphics/GUI/Attributes/StressLimit.png"
        }
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
