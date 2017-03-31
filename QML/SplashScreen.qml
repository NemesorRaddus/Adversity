import QtQuick 2.0

Item {
    id: splashScreen

    property alias splashImageSource: splashImage.source
    property int splashDisappearAnimationDuration: 500
    property int minDurationInMs: 1000
    property bool canClose: false
    property int canCloseRefreshingRateInMs: 100

    visible: true
    opacity: 0.0

    signal showing()
    signal hiding()

    function show()
    {
        state = "showingSplash";
    }

    onStateChanged: {
        if (state == "showingSplash")
        {
            if (minDurationInMs === 0)
            {
                privateProperties.tryClosing = true;
                timer.repeat = true;
                timer.interval = canCloseRefreshingRateInMs;
                timer.restart();
            }
            else
            {
                privateProperties.tryClosing = false;
                timer.repeat = false;
                timer.interval = minDurationInMs;
                timer.restart();
            }
            showing();
        }
        else
        {
            timer.stop();
            hiding();
        }
    }

    QtObject {
        id: privateProperties

        property bool tryClosing: false
    }

    Timer {
        id: timer

        running: false
        repeat: false

        onTriggered: {
            if (privateProperties.tryClosing)
            {
                if (canClose)
                {
                    splashScreen.state = "";
                }
            }
            else
            {
                if (canClose)
                {
                    splashScreen.state = "";
                }
                else
                {
                    privateProperties.tryClosing = true;
                    repeat = true;
                    interval = canCloseRefreshingRateInMs;
                    restart();
                }
            }
        }
    }

    Image {
        id: splashImage

        anchors.fill: parent
    }

    states: [
        State {
            name: "showingSplash"
            PropertyChanges { target: splashScreen;  opacity: 1.0 }
        }
    ]

    transitions: [
        Transition {
            from: "showingSplash"; to: ""
            PropertyAnimation { target: splashScreen; property: "opacity";  duration: splashDisappearAnimationDuration }
        }
    ]

    Component.onCompleted: {
        canClose = false;
        privateProperties.tryClosing = false;
    }
}
