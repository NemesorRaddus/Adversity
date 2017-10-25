#include "otherevents.h"

#include "general/randomizer.h"
#include "mercenaries/mercenary.h"
#include "reports/missionreports.h"

MultiEvent::~MultiEvent() noexcept
{
    for (auto &e : m_eventsToExecute)
        delete e;
}

QVector<EventReport> MultiEvent::executeSpecificOps(Mercenary *context) noexcept
{
    QVector <EventReport> r={eventText()};
    for (auto e : m_eventsToExecute)
    {
        if (context!=nullptr && !context->isDead())
            r+=e->execute(context);
        else
            break;
    }
    return r;
}

PossibilityEvent::PossibilityEvent(Chance chance, Event *event, QString text, const QVector<QString> &dbEntries) noexcept
    : Event(EventEnums::T_Possibility, text, dbEntries), m_chance(chance), m_event(event) {}

PossibilityEvent::~PossibilityEvent() noexcept
{
    delete m_event;
}

QVector<EventReport> PossibilityEvent::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (mercenary==nullptr || m_event==nullptr)
        return {};

    if (static_cast<unsigned>(m_chance)>=Randomizer::randomBetweenAAndB(1,100))
        return QVector<EventReport>{eventText()} + m_event->execute(mercenary);
    return {eventText()};
}
