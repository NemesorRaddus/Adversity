import QtQuick 2.9

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 1920

    width: 1080
    height: 1920

    signal hiding()

    function cursorLoseFocus()
    {
        root.forceActiveFocus();
    }

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

    onVisibleChanged: {
        if (visible)
        {
            con.text="";
            con.forceActiveFocus();
        }
        else
            hiding();
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: background2

        anchors.fill: parent

        opacity: 0.15

        source: "qrc:/graphics/splash.png"
    }

    TextInput {
        id: con

        x: 48
        y: 480
        width: root.width - 2*x
        height: font.pixelSize

        color: "#94ef94"
        wrapMode: TextInput.Wrap
        font.pixelSize: 62
        font.family: "Consolas"

        onAccepted: {
            if (text == "forceUIUpdate()")
            {
                eval("GameApi.h4xLogic.forceUIUpdate()");
                parent.forceActiveFocus();
                parent.visible=false;
            }
            else
            {
                eval("GameApi.h4xLogic."+GameApi.globalsCpp.sanitize(text));
                if (eval("(GameApi.h4xLogic.isAutoUpdateEnabled())"))
                {
                    eval("GameApi.h4xLogic.forceUIUpdate()");
                    parent.forceActiveFocus();
                    parent.visible=false;
                }
                else
                    text = "";
            }
        }
    }
}
