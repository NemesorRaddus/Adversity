import QtQuick 2.9

import Game 1.0
import "../.."

Item {
    id: root

    property string name_
    property string profession_
    property string land_
    property string missionLength_
    property int daysSpent_
    property bool signalOn_
    property bool sbeOn_

    function setArtSource(source)
    {
        art.source = source;
    }

    function setName(text)
    {
        name_ = text;
        name.text = text;
    }

    function setProfession(text)
    {
        profession_ = text;
        prof.text="The "+text;
    }

    function setStatusFrames(hp,hl,st,sl)
    {
        statusHPFrame.check(hp,hl);
        statusSTFrame.check(st,sl);
    }

    function setMissionInfo(land,length,daysSpent,signalOn,sbeOn)
    {
        land_=land;
        missionLength_=length;
        daysSpent_=daysSpent;
        signalOn_=signalOn;
        sbeOn_=sbeOn;

        missionLengthIcon.update();
        signalIcon.update();
        sbeActivationIcon.update();
        info.update();
    }

    function getName()
    {
        return name_;
    }

    function getProfession()
    {
        return profession_;
    }

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

            source: "qrc:/graphics/Mercs/Gunzerker/PaulLuft.png"
        }

        Image {
            id: missionLengthIcon

            x: 184
            y: 3
            width: 75
            height: width

            function update()
            {
                var s1,s2;
                s1=GameApi.globalsCpp.alterNormalTextToInternal(land_);
                if (missionLength_ == "Short")
                    s2="1";
                else if (missionLength_ == "Medium")
                    s2="2";
                else if (missionLength_ == "Long")
                    s2="3";
                else if (missionLength_ == "Extreme")
                    s2="4";
                source = "qrc:/graphics/GUI/MissionLength/"+s1+s2+".png";
            }

            source: "qrc:/graphics/GUI/MissionLength/AuroraForest4.png"
        }

        Image {
            id: signalIcon

            x: missionLengthIcon.x
            y: missionLengthIcon.y+missionLengthIcon.height
            width: 75
            height: width

            function update()
            {
                source = "qrc:/graphics/GUI/" + (root.signalOn_ ? "Connected" : "Disconnected") + ".png";
            }

            source: "qrc:/graphics/GUI/Connected.png"
        }

        Image {
            id: sbeActivationIcon

            x: signalIcon.x
            y: signalIcon.y+signalIcon.height
            width: 75
            height: width

            function update()
            {
                visible = root.sbeOn_;
            }

            source: "qrc:/graphics/GUI/Attributes/StressLimit.png"
        }

        Image {
            id: frame

            x: 0
            y: 0
            width: 262
            height: 262

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }

        Image {
            id: statusHPFrame
            x: 3
            y: 3
            width: 256
            height: 256

            function check(hp, hpMax)
            {
                if (hp/hpMax <= 0.2)
                    source = "qrc:/graphics/GUI/Status frames/LowHealth80.png";
                else if (hp/hpMax <= 0.4)
                    source = "qrc:/graphics/GUI/Status frames/LowHealth60.png";
                else if (hp/hpMax <= 0.6)
                    source = "qrc:/graphics/GUI/Status frames/LowHealth40.png";
                else if (hp/hpMax <= 0.8)
                    source = "qrc:/graphics/GUI/Status frames/LowHealth20.png";
                else
                    source = "";
            }

            NumberAnimation {
                id: animHP
                from: 0;
                to: 1;

                onRunningChanged: {
                    if (running == false)
                    {
                        if (from == 0)
                        {
                            from = 1;
                            to = 0;
                            running = true;
                        }
                        else
                        {
                            from = 0;
                            to = 1;
                            running = true;
                        }
                    }
                }

                duration: 1500
                target: statusHPFrame
                property: "opacity"
                running: true
            }
        }

        Image {
            id: statusSTFrame
            x: 3
            y: 3
            width: 256
            height: 256

            function check(stress, stressLimit)
            {
                if (stress/stressLimit >= 0.8)
                    source = "qrc:/graphics/GUI/Status frames/HighStress80.png";
                else if (stress/stressLimit >= 0.6)
                    source = "qrc:/graphics/GUI/Status frames/HighStress60.png";
                else if (stress/stressLimit >= 0.4)
                    source = "qrc:/graphics/GUI/Status frames/HighStress40.png";
                else if (stress/stressLimit >= 0.2)
                    source = "qrc:/graphics/GUI/Status frames/HighStress20.png";
                else
                    source = "";
            }

            NumberAnimation {
                id: animST
                from: 0;
                to: 1;

                onRunningChanged: {
                    if (running == false)
                    {
                        if (from == 0)
                        {
                            from = 1;
                            to = 0;
                            running = true;
                        }
                        else
                        {
                            from = 0;
                            to = 1;
                            running = true;
                        }
                    }
                }

                duration: 1500
                target: statusSTFrame
                property: "opacity"
                running: true
            }
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
            x: 2
            y: -6
            color: "#94ef94"
            text: "Marek Jakubowski"
            font.pixelSize: 56
            font.family: fontStencil.name
        }

        Text {
            id: prof
            x: 2
            y: 50
            color: "#94ef94"
            text: "The Bounty Hunter"
            font.pixelSize: 36
            font.family: fontStencil.name
        }

        Text {
            id: info

            x: 2
            y: 99
            width: 777
            height: 152

            function update()
            {
                text="Land: "+root.land_+"\nMission type: "+root.missionLength_+"\nDays spent: "+root.daysSpent_+"\nSignal status: "+(root.signalOn_ ? "On" : "Off");
            }

            color: "#94ef94"
            font.pixelSize: 32
            font.family: fontStencil.name
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}
