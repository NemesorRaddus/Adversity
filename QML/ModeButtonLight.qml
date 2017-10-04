import QtQuick 2.9
import Game 1.0

Item {
    id: root

    Image {
        id: buttonLight

        anchors.fill: parent

        source: "qrc:/graphics/GUI/Light.png"

        NumberAnimation {
            id: animButtonLight

            from: GameApi.randomize(0,100)/100;
            to: GameApi.randomize(0,100)/100;

            onRunningChanged: {
                if (running == false)
                {
                    from = GameApi.randomize(0,100)/100;
                    to = GameApi.randomize(0,100)/100;
                    running = true;
                }
            }

            duration: 10
            target: buttonLight
            property: "opacity"
            running: true
        }
    }
}
