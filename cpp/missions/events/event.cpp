#include "event.h"

#include "base/base.h"
#include "database/database.h"
#include "mercenaries/mercenary.h"
#include "missions/land.h"
#include "missions/mission.h"

QVector<EventReport> Event::execute(Mercenary *context) noexcept
{
    auto r = executeSpecificOps(context);
    if (!context->isDead())
    {
        if (context->isCommunicationAvailable())
            unlockDatabaseEntries(context);
        else
        {
            for (const auto &e : m_unlockedDatabaseEntries)
                context->addWaitingDBEntry(e);
        }
    }
    return r;
}

void Event::setEventText(const QString &text) noexcept
{
    m_eventText=text;
}

void Event::unlockDatabaseEntries(Mercenary *context) noexcept
{
    for (auto e : m_unlockedDatabaseEntries)
        if (!context->base()->database()->isEntryUnlocked(e, context->assignedMission()->land()->name()))
            context->base()->database()->unlockEntry(e,context->assignedMission()->land()->name());
}
