import QtQuick 2.9

import Game 1.0
import ".."
import "../.."

Item {
    id: root

    readonly property int theoreticalWidth: 540
    readonly property int theoreticalHeight: 732

    property string name_

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name_ = text;
        name.text = GameApi.tr(text);
    }

    function getName()
    {
        return name_;
    }

    function getArtSource()
    {
        return art.source;
    }

    width: 540
    height: 732

    Rectangle {
        id: recOut

        x: 40
        y: 40
        width: 460
        height: 652

        color: "#94ef94"

        Rectangle {
            id: recIn

            x: 5
            y: 5
            width: 450
            height: 642

            color: "#171717"

            Rectangle {
                id: artBorder

                x: 10
                y: 10
                width: 430
                height: 430

                color: "#94ef94"

                Image {
                    id: art

                    x: 4
                    y: 4
                    width: 422
                    height: 422
                }
            }

            Text {
                id: name

                x: 10
                y: 450
                width: 430
                height: 182

                color: "#94ef94"
                font.pixelSize: 65
                font.family: fontStencil.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
