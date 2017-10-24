#include "missionreports.h"

#include "general/game.h"

EncounterReport::EncounterReport(const QString &mercenaryArt, const QVector<EventReport> &events, const Time &time) noexcept
    : Report(ReportEnums::T_Encounter, time), m_mercenaryArt(mercenaryArt), m_events(events) {}

QString EncounterReport::text() const noexcept
{
    QString r;
    for (const auto &e : m_events)
        r+=e+"\n";
    return r;
}

SignalLostReport::SignalLostReport(const QString &mercenaryArt, const QString &mercenaryName, const QString &landName, const Time &time) noexcept
    : Report(ReportEnums::T_SignalLost, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName), m_landName(landName) {}

QString SignalLostReport::text() const noexcept
{
    return "We've lost connection with "+Game::gameInstance()->tr(m_mercenaryName)+", who is exploring "+m_landName+".";
}

SignalRetrievedReport::SignalRetrievedReport(const QString &mercenaryArt, const QString &landName, const Time &time) noexcept
    : Report(ReportEnums::T_SignalRetrieved, time), m_mercenaryArt(mercenaryArt), m_landName(landName) {}

QString SignalRetrievedReport::text() const noexcept
{
    return "Finally I can hear you clearly.";
}

MissionEndReport::MissionEndReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(ReportEnums::T_MissionEnd, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString MissionEndReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" has successfully returned to the base.";
}

MissionStartReport::MissionStartReport(const QString &mercenaryArt, int stress, int stressLimit, const Time &time) noexcept
    : Report(ReportEnums::T_MissionStart, time), m_mercenaryArt(mercenaryArt), m_stress(stress), m_stressLimit(stressLimit) {}

QString MissionStartReport::text() const noexcept
{
    if (m_stressLimit == -1)
        return "Order understood.";
    int perc = m_stress*10/m_stressLimit;
    switch (perc) {
    case 0:
        return "Finally! A new mission! I thought I would have died of boredom.";
    case 1:
        return "Well, I've been looking forward to go on mission.";
    case 2:
        return "A new mission? I think I can handle it.";
    case 3:
        return "I'm not too happy about going on the mission, but I guess I have to.";
    case 4:
        return "I'm not sure if I am the right person for this task.";
    case 5:
        return "Couldn't anyone go instead of me?";
    case 6:
        return "I don't feel well, it's too much for me.";
    case 7:
        return "Please! Don't make me go back to these horrors!";
    case 8:
        return "You must be crazy! I'm not ready for this shit! I'm going to fucking die!";
    default:
        return "Are you insane?! It's a fucking suicide mission! I'm gonna die there and my fucking body will be eaten by some shitworms!";
    }
}
