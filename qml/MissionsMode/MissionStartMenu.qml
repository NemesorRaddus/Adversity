import QtQuick 2.0
import Game 1.0

Item {
    id: root

    property string intLandName

    signal backClicked()
    signal nextClicked(string intLandName, string name, string desc)

    function returnToDefault()
    {
        lengthShort.state = "notActive";
        lengthMedium.state = "notActive";
        lengthLong.state = "notActive";
        lengthExtreme.state = "notActive";

        missionLengthText.text = "";

        next.visible = false;

        intLandName = "";
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    function show(internalName_, name_, description_)
    {
        intLandName = internalName_;
        art.source = "qrc:/graphics/Missions/Lands/"+internalName_+".png";
        name.text = name_;
        description.text = description_;
        missionLengthSelect.setLand(internalName_);
    }

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    Item {
        id: land

        width: 1080
        height: 271

        Image {
            id: itemBorder
            x: 17
            y: 265
            width: 1048
            height: 3
            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Item {
            id: artSegment

            x: 17
            y: 0
            width: 262
            height: 262

            Image {
                id: art
                x: 3
                y: 3
                width: 256
                height: 256
            }

            Image {
                id: frame
                x: 0
                y: 0
                width: 262
                height: 262
                source: "qrc:/graphics/GUI/Task_Picture.png"
            }
        }

        Item {
            id: textSegment
            x: 280
            y: 10
            width: 785
            height: 249

            Text {
                id: name
                x: 0
                y: -4
                color: "#94ef94"
                font.pixelSize: 76
                font.family: fontStencil.name
            }

            Text {
                id: description
                x: 0
                y: 113
                width: 785
                height: 136
                color: "#568b56"
                wrapMode: Text.WordWrap
                font.pixelSize: 40
                font.family: fontStencil.name
            }
        }
    }

    Item {
        id: missionLengthSelect

        x: 0
        y: land.height + 8
        width: parent.width

        function setLand(internalName)
        {
            lengthShortIcon.source = "qrc:/graphics/GUI/MissionLength/"+internalName+"1.png";
            lengthMediumIcon.source = "qrc:/graphics/GUI/MissionLength/"+internalName+"2.png";
            lengthLongIcon.source = "qrc:/graphics/GUI/MissionLength/"+internalName+"3.png";
            lengthExtremeIcon.source = "qrc:/graphics/GUI/MissionLength/"+internalName+"4.png";
        }

        Item {
            id: lengthShort

            x: 11
            y: 0
            width: 256
            height: 256

            state: "notActive"

            Image {
                id: lengthShortIcon

                anchors.fill: parent
            }
            MouseArea {
                id: lengthShortMA

                anchors.fill: parent

                onClicked: {
                    if (parent.state == "notActive")
                    {
                        parent.state = "";

                        lengthMedium.state = "notActive";
                        lengthLong.state = "notActive";
                        lengthExtreme.state = "notActive";

                        missionLengthText.text = "Mission length:\nShort (2-4 days)"

                        next.visible = true;
                    }
                }
            }

            states: [
                State {
                    name: "notActive"
                    PropertyChanges { target: lengthShort; opacity: 0.5 }
                }
            ]

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 200 }
            }
        }

        Item {
            id: lengthMedium

            x: lengthShort.x+lengthShort.width+11
            y: lengthShort.y
            width: lengthShort.width
            height: lengthShort.height

            state: "notActive"

            Image {
                id: lengthMediumIcon

                anchors.fill: parent
            }
            MouseArea {
                id: lengthMediumMA

                anchors.fill: parent

                onClicked: {
                    if (parent.state == "notActive")
                    {
                        parent.state = "";

                        lengthShort.state = "notActive";
                        lengthLong.state = "notActive";
                        lengthExtreme.state = "notActive";

                        missionLengthText.text = "Mission length:\nMedium (6-8 days)"

                        next.visible = true;
                    }
                }
            }

            states: [
                State {
                    name: "notActive"
                    PropertyChanges { target: lengthMedium; opacity: 0.5 }
                }
            ]

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 200 }
            }
        }

        Item {
            id: lengthLong

            x: 2*(lengthShort.x+lengthShort.width)+11
            y: lengthShort.y
            width: lengthShort.width
            height: lengthShort.height

            state: "notActive"

            Image {
                id: lengthLongIcon

                anchors.fill: parent
            }
            MouseArea {
                id: lengthLongMA

                anchors.fill: parent

                onClicked: {
                    if (parent.state == "notActive")
                    {
                        parent.state = "";

                        lengthShort.state = "notActive";
                        lengthMedium.state = "notActive";
                        lengthExtreme.state = "notActive";

                        missionLengthText.text = "Mission length:\nLong (11-17 days)"

                        next.visible = true;
                    }
                }
            }

            states: [
                State {
                    name: "notActive"
                    PropertyChanges { target: lengthLong; opacity: 0.5 }
                }
            ]

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 200 }
            }
        }

        Item {
            id: lengthExtreme

            x: 3*(lengthShort.x+lengthShort.width)+11
            y: lengthShort.y
            width: lengthShort.width
            height: lengthShort.height

            state: "notActive"

            Image {
                id: lengthExtremeIcon

                anchors.fill: parent
            }
            MouseArea {
                id: lengthExtremeMA

                anchors.fill: parent

                onClicked: {
                    if (parent.state == "notActive")
                    {
                        parent.state = "";

                        lengthShort.state = "notActive";
                        lengthMedium.state = "notActive";
                        lengthLong.state = "notActive";

                        missionLengthText.text = "Mission length:\nExtreme (28-34 days)"

                        next.visible = true;
                    }
                }
            }

            states: [
                State {
                    name: "notActive"
                    PropertyChanges { target: lengthExtreme; opacity: 0.5 }
                }
            ]

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 200 }
            }
        }
    }

    Item {
        id: back

        x: 150
        y: parent.height - height
        width: 330
        height: backText.height

        Text {
            id: backText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "< Back"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: {
                root.returnToDefault();
                backClicked();
            }
        }
    }

    Item {
        id: next

        x: 600
        y: back.y
        width: 330
        height: nextText.height

        visible: false

        Text {
            id: nextText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "Next >"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: nextMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: {
                GameApi.base.missionInitializer.setLand(name.text);
                if (lengthShort.state == "")
                    GameApi.base.missionInitializer.setDifficulty("Short");
                else if (lengthMedium.state == "")
                    GameApi.base.missionInitializer.setDifficulty("Medium");
                else if (lengthLong.state == "")
                    GameApi.base.missionInitializer.setDifficulty("Long");
                else if (lengthExtreme.state == "")
                    GameApi.base.missionInitializer.setDifficulty("Extreme");
                root.nextClicked(root.intLandName, name.text, description.text);
            }
        }
    }

    Text {
        id: missionLengthText

        x: 0
        y: parent.height*4/5
        width: parent.width

        color: "#94ef94"
        font.pixelSize: 80
        horizontalAlignment: Text.AlignHCenter
        font.family: fontStencil.name
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
