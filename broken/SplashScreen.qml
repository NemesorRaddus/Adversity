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

    function show()
    {
        state = "showingSplash";console.log("Kazało wyświetlić")
    }

    onStateChanged: {
        if (state == "showingSplash")
        {
            if (minDurationInMs === 0)
            {
                privateProperties.tryClosing = true;
                timer.repeat = true;
                timer.interval = canCloseRefreshingRateInMs;
                timer.restart();console.log(1)
            }
            else
            {
                privateProperties.tryClosing = false;
                timer.repeat = false;
                timer.interval = minDurationInMs;
                timer.restart();console.log(2)
            }
        }
        else
        {
            timer.stop();console.log(3)
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
            {console.log("a")
                if (canClose)
                {
                    splashScreen.state = "";console.log("aa")
                }
            }
            else
            {console.log("b")
                if (canClose)
                {console.log("ba")
                    splashScreen.state = "";
                }
                else
                {console.log("bb")
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
        canClose = false;console.log("XX")
        privateProperties.tryClosing = false;
    }
}
