import QtQuick 2.0
import Game 1.0

import "../.."
import ".."

Item {
    id: root

    signal backClicked()

    function setItem(name)
    {

    }

    state: "hiddenDown"

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

    states: [
        State {
            name: "hiddenDown"
            PropertyChanges { target: root; y: -height }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 1000 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
