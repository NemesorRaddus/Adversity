import QtQuick 2.9
import QtQuick.Window 2.3

import Game 1.0

Window {
    id: root

    visible: true

    title: "Adversity debug console"

    x: 150
    y: 500
    width: 500
    height: 300

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    ListModel {
        id: lm
    }
    Component {
        id: delegateComp
        Item {
            id: delegateRoot

            width: content.width
            height: content.height

            Text {
                id: content

                width: metrics.boundingRect.width
                height: metrics.boundingRect.height

                font.pixelSize: 25
                color: "#94ef94"

                text: log

                TextMetrics {
                    id: metrics

                    text: content.text
                    font: content.font
                }
            }
        }
    }
    ListView {
        id: list

        x: 10
        y: 10
        width: parent.width - 2*x
        height: input.y - 2*y

        contentWidth: contentItem.width
        contentHeight: contentItem.height

        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        clip: true

        delegate: delegateComp
        model: lm;

        function acknowledgeAddition(forcefully)
        {
            if (forcefully || atYEnd)
                positionViewAtEnd();
        }
        function showItem(index)
        {
            positionViewAtIndex(index, ListView.Contain);
        }
    }

    TextInput {
        id: input

        property int currentCopiedCommandIndex: -1

        x: 10
        y: parent.height - height
        width: parent.width - 2*x
        height: font.pixelSize + 10

        font.pixelSize: 25
        color: "#94ef94"

        focus: true

        Keys.priority: Keys.BeforeItem
        Keys.onPressed: {
            if (event.key == Qt.Key_Up)
            {
                if (currentCopiedCommandIndex == -1)
                {
                    text = lm.get(lm.count-1).log;
                    currentCopiedCommandIndex = lm.count-1;
                    list.positionViewAtEnd();
                }
                else if (currentCopiedCommandIndex > 0)
                {
                    text = lm.get(--currentCopiedCommandIndex).log;
                    list.showItem(currentCopiedCommandIndex);
                }
            }
            else if (event.key == Qt.Key_Down)
            {
                if (currentCopiedCommandIndex != -1 && currentCopiedCommandIndex < lm.count - 1)
                {
                    text = lm.get(++currentCopiedCommandIndex).log;
                    list.showItem(currentCopiedCommandIndex);
                }
            }
        }

        onAccepted: {
            eval("GameApi.h4xLogic."+GameApi.globalsCpp.sanitize(text));
            if (eval("(GameApi.h4xLogic.isAutoUpdateEnabled())"))
                eval("GameApi.h4xLogic.forceUIUpdate()");
            lm.append({log: input.text});
            text = "";
            currentCopiedCommandIndex = -1;
            list.acknowledgeAddition(true);
        }

        onFocusChanged: {
            focus = true;
        }
    }
}
