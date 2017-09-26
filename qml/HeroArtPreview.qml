import QtQuick 2.9

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 1920

    width: 1080
    height: 1920

    function show(artSource)
    {
        transitionBackgroundHider.duration = transitionBackgroundHider.baseDuration * GameApi.animMultiplier();

        artBox.visible = true;
        artBoxArt.source = artSource;
        backgroundHider.state = "hidingContent";
        closeMA.visible = true;
    }

    function hide()
    {
        artBox.visible = false;
        backgroundHider.state = "";
        closeMA.visible = false;
    }

    signal closing()

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
        id: backgroundHider

        anchors.fill: parent

        opacity: 0

        source: "qrc:/graphics/GUI/Background.png"

        states: [
            State {
                name: "hidingContent"
                PropertyChanges { target: backgroundHider; opacity: 0.75 }
            }
        ]

        transitions: Transition {
            NumberAnimation { id: transitionBackgroundHider; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
        }
    }

    MouseArea {
        id: closeMA

        visible: false

        anchors.fill: parent

        onClicked: {
            hide();
            root.closing();
        }
    }

    Item {
        id: artBox

        visible: false

        width: 778
        height: 778
        anchors.centerIn: parent

        Rectangle {
            id: artBoxRect

            anchors.fill: parent

            color: "#171717"

            border.color: "#94ef94"
            border.width: 5
        }

        Image {
            id: artBoxArt

            x: 5
            y: 5
            width: 768
            height: 768
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
