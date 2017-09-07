import QtQuick 2.9

Item {
    id: root

    property bool scrollingEnabled: true
    property bool alwaysScroll: false // scrolls even if text is short enough to be fully visible
    property alias text: scrollingText.text
    property alias font: scrollingText.font
    property alias color: scrollingText.color
    property int refreshingRate: 60 // in Hz
    property int scrollingSpeed: 20 // % of component width per second
    property int startPauseDuration: 0 // in ms
    property int hidingPauseDuration: 0 // in ms
    property int startX: 0 // % of component width, how far the text will be on the right at the start
    property bool fluid: true // if true, at full text hiding the text will appear on the other side; else the text will jump to start position

    height: scrollingText.height
    clip: true

    function reset()
    {
        members.tempX = -startX/100 * width;
        startPauseTimer.stop();
        timer.stop();
        hidingPauseTimer.stop();
        startPauseTimer.maybeStart();
    }

    QtObject {
        id: members

        property real tempX: -startX/100 * root.width
    }

    Text {
        id: scrollingText

        x: -members.tempX

        property bool onTheLeft: true

        onTextChanged: {
            reset();
        }
    }

    Timer {
        id: startPauseTimer

        interval: startPauseDuration
        running: false
        repeat: false

        function maybeStart()
        {
            if (scrollingEnabled && (root.width < scrollingText.width || alwaysScroll))
                running = true;
            else
                running = false;
        }

        onTriggered: {
            timer.start();
        }
    }

    Timer {
        id: timer

        interval: 1000/refreshingRate
        running: false
        repeat: true

        onTriggered: {
            var change = scrollingSpeed/100/refreshingRate*root.width;
            if (scrollingText.onTheLeft)
            {
                members.tempX = members.tempX + change;

                if (members.tempX > scrollingText.width)
                {
                    if (fluid)
                    {
                        scrollingText.onTheLeft = false;
                        members.tempX = -root.width;
                        stop();
                        hidingPauseTimer.start();
                    }
                    else
                        root.reset();
                }
            }
            else
            {
                if (startX/100 * root.width + members.tempX >= -change)
                {
                    scrollingText.onTheLeft = true;
                    stop();
                    startPauseTimer.maybeStart();
                }
                else
                    members.tempX = members.tempX + change;
            }
        }
    }

    Timer {
        id: hidingPauseTimer

        interval: hidingPauseDuration
        running: false
        repeat: false

        onTriggered: {
            timer.start();
        }
    }
}
