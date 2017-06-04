import QtQuick 2.0

Item {
    id: root

    signal requestSwitchingToHeroesTab()
    signal requestSwitchingToEquipmentTab()

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -1 *width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}
