import QtQuick 2.9
import Game 1.0

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
    Text {
        id: buildInfo

        x: parent.width/1000
        y: parent.height-font.pixelSize
        width: parent.width*998/1000

        font.family: fontStencil.name
        color: "#ffffff"
        font.pixelSize: 20*parent.width/450

        Component.onCompleted: text = "v"+GameApi.buildInfo.versionNumber()+" "+GameApi.buildInfo.buildTime()+" "+GameApi.buildInfo.buildType()+" "+GameApi.buildInfo.additionalBuildInfo()
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    states: [
        State {
            name: "showingSplash"
            PropertyChanges { target: splashScreen;  opacity: 1.0 }
        }
    ]

    transitions: Transition {
        from: "showingSplash"; to: ""
        PropertyAnimation { id: transitionRoot; target: splashScreen; property: "opacity";  duration: splashDisappearAnimationDuration * GameApi.animMultiplier() }
    }
}
