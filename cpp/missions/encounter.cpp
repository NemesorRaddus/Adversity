#include "encounter.h"

#include "base/base.h"
#include "clock/time.h"
#include "mercenaries/mercenariescontainer.h"
#include "mercenaries/mercenary.h"
#include "missions/events/event.h"
#include "reports/missionreports.h"

Encounter::Encounter(const QString &name, Event *rootEvent, unsigned probability) noexcept
    : m_name(name), m_rootEvent(rootEvent), m_probability(probability) {}

EncounterReport *Encounter::execute(Mercenary *mercenary, const Time &currentTime) const noexcept
{
    auto b = mercenary->base();
    auto reps = m_rootEvent->execute(mercenary);
    for (int i=0;i<reps.size();)
    {
        if (reps[i].isEmpty())
            reps.remove(i);
        else
            ++i;
    }
    if (!b->mercenaries()->mercenaries().contains(mercenary))//TODO probably remove
        return static_cast<EncounterReport *>(static_cast<Report *>(new NullReport));//mercenary died during encounter
    return new EncounterReport{mercenary->pathToArt(), reps, currentTime};
}

EncountersContainer::~EncountersContainer() noexcept
{
    for (auto e : m_encounters)
        delete e;
}

void EncountersContainer::addEncounter(Encounter *enc) noexcept
{
    m_encounters+=enc;
}

void EncountersContainer::removeEncounter(unsigned index) noexcept
{
    if (index<m_encounters.size())
    {
        delete m_encounters[index];
        m_encounters.remove(index);
    }
}
