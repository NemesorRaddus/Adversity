#include "mission.h"

#include <QDataStream>

#include "base/base.h"
#include "base/managers/equipmentmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/missionsmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/missionend.h"
#include "equipment/equipment.h"
#include "general/game.h"
#include "general/randomizer.h"
#include "logging/loggershandler.h"
#include "mercenaries/mercenariescontainer.h"
#include "mercenaries/mercenary.h"
#include "missions/encounter.h"
#include "missions/events/event.h"
#include "missions/land.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

void Mission::handleNewDay() noexcept
{
    ++m_daysSpent;
}

void Mission::assignMercenary(Mercenary *mercenary) noexcept
{
    m_assignedMercenary = mercenary;
}

void Mission::start() noexcept
{
    m_assignedMercenary->base()->reports()->addReport(new UnifiedReport(new MissionStartReport(m_assignedMercenary->pathToArt(), m_assignedMercenary->stress(), m_assignedMercenary->stressLimit(), m_assignedMercenary->base()->gameClock()->currentTime())));
    m_assignedMercenary->base()->reports()->registerLatestReportInMission(this);
    planEverything();

    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Mission started: (mercenary: {}, length: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString(), MissionEnums::fromLengthEnumToQString(m_length).toStdString());
    for (const auto &e : m_encounters)
        Game::gameInstance()->loggers()->missionsLogger()->trace("Day {}: {}",e.first,e.second->name().toStdString());
    Game::gameInstance()->loggers()->missionsLogger()->trace("Mission ends in {}",remainingDays());
}

EncounterReport *Mission::doEncounter(const Time &now) noexcept
{
    m_timeOfCurrentEncounter = now;

    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Doing encounter: {} (mercenary: {})",now.toQString().toStdString(),m_encounters[m_nextEncounter].second->name().toStdString(), m_assignedMercenary->name().toStdString());

    return m_encounters[m_nextEncounter++].second->execute(m_assignedMercenary, now);
}

void Mission::end() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Ending mission (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->returnToBase();
}

void Mission::forceEndSuccessfully() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    auto ms = m_assignedMercenary->base()->missions();
    end();
    ms->removeMission(this);
}

void Mission::forceEndSilently() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end silently (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
}

void Mission::forceEndBecauseOfDeath() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end because of death or sth like that (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    m_assignedMercenary->assignMission(nullptr);
    m_assignedMercenary->base()->missions()->removeMission(this);
}

void Mission::abort() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Aborting mission (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    m_assignedMercenary->assignMission(nullptr);
    auto ms = m_assignedMercenary->base()->missions();
    m_assignedMercenary->die(1,0);
    ms->removeMission(this);
}

void Mission::addRelatedReport(UnifiedReport *report) noexcept
{
    m_relatedReports+=report;
}

void Mission::prepareReport(unsigned index) noexcept
{
    if (index < m_relatedReports.size())
        m_preparedRelatedReport = m_relatedReports[index];
}

Mission::Mission() noexcept
    : m_land(nullptr), m_length(MissionEnums::L_END), m_duration(1), m_daysSpent(0), m_nextEncounter(0), m_minutesSinceMidnightOfLastEncounter(-1), m_assignedMercenary(nullptr), m_preparedRelatedReport(nullptr) {}

void Mission::planEverything() noexcept
{
    planAllEncounters();
    planEnd();
}

void Mission::planAllEncounters() noexcept
{
    auto clock = m_assignedMercenary->base()->gameClock();
    for (int i=0;i < m_encounters.size();++i)
    {
        unsigned missionDayOfPlannedEncounter = m_encounters[i].first;
        unsigned daysToAdd = i == 0 ? missionDayOfPlannedEncounter : missionDayOfPlannedEncounter-m_encounters[0].first;
        unsigned dayOfPlannedEncounter = clock->currentDay() + daysToAdd;
        unsigned maxMinutes = 24*60-(m_encounters.size()-1-i);// minutes since midnight
        unsigned minMinutes;
        if (i == 0)
            minMinutes = clock->currentHour()*60 + clock->currentMin() + 1;
        else
        {
            if (daysToAdd == 0)
                minMinutes = m_minutesSinceMidnightOfLastEncounter + 1;
            else
                minMinutes = 0;
        }
        unsigned minutesResult = Randomizer::randomBetweenAAndB(minMinutes, maxMinutes);
        unsigned hourOfPlannedEncounter = minutesResult/60;
        unsigned minOfPlannedEncounter = minutesResult%60;
        Time timeResult={dayOfPlannedEncounter, hourOfPlannedEncounter, minOfPlannedEncounter};
        m_minutesSinceMidnightOfLastEncounter = minutesResult;

        clock->addMissionAlarm(timeResult, this);
    }
}

void Mission::planEnd() noexcept
{
    m_assignedMercenary->base()->gameClock()->addAlarm(m_duration, new MissionEndTimerAlarm(m_assignedMercenary->base(),this));
}

void Mission::setLand(Land *land) noexcept
{
    m_land = land;
}

void Mission::setLength(MissionEnums::Length length) noexcept
{
    m_length = length;
}

void Mission::setDuration(unsigned days) noexcept
{
    if (days < 1)
        return;
    m_duration = days;
    m_daysSpent = 0;
}

void Mission::addEncounter(MissionDay day, Encounter *encounter) noexcept
{
    m_encounters+={day,encounter};
}

QDataStream &operator<<(QDataStream &stream, const MissionDataHelper &mission) noexcept
{
    stream<<mission.land;
    stream<<static_cast<quint8>(mission.length);
    stream<<static_cast<qint16>(mission.duration);
    stream<<static_cast<qint16>(mission.daysSpent);
    QVector <QPair <qint16, QString> > encounters;
    for (auto e : mission.encounters)
        encounters+={static_cast<qint16>(e.first),e.second};
    stream<<encounters;
    stream<<static_cast<qint16>(mission.nextEncounter);
    stream<<static_cast<qint16>(mission.minutesSinceMidnightOfLastEncounter);
    stream<<mission.mercenary;
    stream<<mission.relatedReportsIDs;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, MissionDataHelper &mission) noexcept
{
    quint8 n;
    qint16 ii;

    stream>>mission.land;

    stream>>n;
    mission.length = static_cast<MissionEnums::Length>(n);

    stream>>ii;
    mission.duration = ii;

    stream>>ii;
    mission.daysSpent = ii;

    QVector <QPair <qint16, QString> > encounters;
    stream>>encounters;
    for (auto e : encounters)
        mission.encounters+={e.first,e.second};

    stream>>ii;
    mission.nextEncounter = ii;

    stream>>ii;
    mission.minutesSinceMidnightOfLastEncounter = ii;

    stream>>mission.mercenary;

    stream>>mission.relatedReportsIDs;

    return stream;
}

MissionBuilder::MissionBuilder(Base *base) noexcept
    : m_base(base)
{
    m_mission = new Mission();
}

MissionBuilder::~MissionBuilder() noexcept
{
    delete m_mission;
}

Mission *MissionBuilder::getMission() noexcept
{
    qSort(m_mission->m_encounters.begin(), m_mission->m_encounters.end(), lessThanEncounterSorting);
    Mission *ret = m_mission;
    m_mission = new Mission();
    return ret;
}

Mission *MissionBuilder::generateMission(Land *land, MissionEnums::Length length) noexcept
{
    resetMission();
    setLand(land);
    setLength(length);
    unsigned duration = generateDuration(length);
    setDuration(duration);
    m_mission->m_encounters = generateEncounters(land, length, duration);
    Mission *ret = m_mission;
    m_mission = new Mission();
    return ret;
}

void MissionBuilder::resetMission() noexcept
{
    delete m_mission;
    m_mission = new Mission();
}

Mission *MissionBuilder::qobjectifyMissionData(const MissionDataHelper &mission, Base *base) noexcept
{
    Mission *r = new Mission();

    for (auto e : Game::gameInstance()->assetsPool().lands())
        if (e->name() == mission.land)
        {
            r->m_land = e;
            break;
        }
    if (r->m_land == nullptr)
        return r;
    r->m_length = mission.length;
    r->m_duration = mission.duration;
    r->m_daysSpent = mission.daysSpent;
    for (int i=0;i < mission.encounters.size();++i)
        for (auto e : r->m_land->encounters()->encounters())
            if (e->name() == mission.encounters[i].second)
            {
                r->m_encounters+={mission.encounters[i].first, e};
                break;
            }
    r->m_nextEncounter = mission.nextEncounter;
    r->m_minutesSinceMidnightOfLastEncounter = mission.minutesSinceMidnightOfLastEncounter;
    for (auto e : base->mercenaries()->mercenaries()->mercenaries())
        if (e->name() == mission.mercenary)
        {
            r->assignMercenary(e);
            e->assignMission(r);
            break;
        }

    for (const auto &e : mission.relatedReportsIDs)
        for (auto &f : base->reports()->reports())
            if (f->id() == e)
            {
                r->addRelatedReport(f);
                break;
            }

    return r;
}

MissionDataHelper MissionBuilder::deqobjectifyMission(Mission *mission) noexcept
{
    if (mission == nullptr)
        return {};

    MissionDataHelper r;

    r.land = mission->land()->name();
    r.length = mission->length();
    r.duration = mission->fullDuration();
    r.daysSpent = mission->daysSpent();
    QVector <QPair <unsigned, QString> > encs;
    for (auto e : mission->m_encounters)
        encs+={e.first,e.second->name()};
    r.encounters = encs;
    r.nextEncounter = mission->m_nextEncounter;
    r.minutesSinceMidnightOfLastEncounter = mission->m_minutesSinceMidnightOfLastEncounter;
    r.mercenary = mission->assignedMercenary()->name();
    for (const auto &e : mission->reports())
        r.relatedReportsIDs+=e->id();

    return r;
}

void MissionBuilder::setLand(Land *land) noexcept
{
    m_mission->setLand(land);
}

void MissionBuilder::setLength(MissionEnums::Length length) noexcept
{
    m_mission->setLength(length);
}

void MissionBuilder::setDuration(unsigned duration) noexcept
{
    m_mission->setDuration(duration);
}

void MissionBuilder::addRandomEncounter() noexcept
{
    addEncounter(Randomizer::randomBetweenAAndB(0,m_mission->fullDuration()-1),m_mission->land()->makeRandomEncounter());
}

void MissionBuilder::addEncounter(Mission::MissionDay day, Encounter *encounter) noexcept
{
    m_mission->addEncounter(day,encounter);
}

unsigned MissionBuilder::generateDuration(MissionEnums::Length length) const noexcept
{
    switch (length)
    {
    case MissionEnums::L_Short:
        [[fallthrough]];
    case MissionEnums::L_Veteran:
        return Randomizer::randomBetweenAAndB(2,4);
    case MissionEnums::L_Medium:
        [[fallthrough]];
    case MissionEnums::L_Master:
        return Randomizer::randomBetweenAAndB(6,8);
    case MissionEnums::L_Long:
        [[fallthrough]];
    case MissionEnums::L_Heroic:
        return Randomizer::randomBetweenAAndB(11,17);
    case MissionEnums::L_Extreme:
        return Randomizer::randomBetweenAAndB(28,34);
    default:
        return 0;
    }
}

unsigned MissionBuilder::generateAmountOfEncountersPerDay(MissionEnums::Length length) const noexcept
{
    switch (length)
    {
    case MissionEnums::L_Short:
        return Randomizer::randomBetweenAAndB(0,3,Randomizer::RandomizationMethods::bentRand);
    case MissionEnums::L_Medium:
        [[fallthrough]];
    case MissionEnums::L_Long:
        [[fallthrough]];
    case MissionEnums::L_Extreme:
        return Randomizer::randomBetweenAAndB(0,4,Randomizer::RandomizationMethods::bentRand);
    case MissionEnums::L_Veteran:
        [[fallthrough]];
    case MissionEnums::L_Master:
        return Randomizer::randomBetweenAAndB(2,5,Randomizer::RandomizationMethods::bentRand);
    case MissionEnums::L_Heroic:
        return Randomizer::randomBetweenAAndB(2,6,Randomizer::RandomizationMethods::bentRand);
    default:
        return 0;
    }
}

QVector<QPair < Mission::MissionDay, Encounter *> > MissionBuilder::generateEncounters(Land *land, MissionEnums::Length length, unsigned duration) const noexcept
{
    QVector <QPair <Mission::MissionDay, Encounter *> > r;
    for (int i=0;i < duration;++i)
    {
        unsigned am = generateAmountOfEncountersPerDay(length);
        while (am--)
            r+={i,land->makeRandomEncounter()};
    }
    return r;
}

bool MissionBuilder::lessThanEncounterSorting(const QPair<Mission::MissionDay, Encounter *> &first, const QPair < Mission::MissionDay, Encounter *> &second) noexcept
{
    return first.first < second.first;
}

MissionInitializer::MissionInitializer(Base *base) noexcept
    : m_basePtr(base), m_missionBuilder(base), m_land(nullptr), m_length(MissionEnums::L_END), m_mercenary(nullptr), m_armor(nullptr), m_weaponTool({nullptr,nullptr}), m_aetherite(0), m_energy(0), m_bm(0), m_food(0) {}

void MissionInitializer::reset() noexcept
{
    if (m_mercenary != nullptr)
        unprepareMercenary();
    m_land = nullptr;
    m_length = MissionEnums::L_END;
    m_mercenary = nullptr;
    m_armor = nullptr;
    for (int i=0;i < Mercenary::amountOfWeaponToolSlots();++i)
        m_weaponTool[i]=nullptr;
    m_aetherite = 0;
    m_energy = 0;
    m_bm = 0;
    m_food = 0;
}

bool MissionInitializer::start() noexcept
{
    if (!(m_basePtr->resources()->canDecreaseAetheriteAmount(m_aetherite) && m_basePtr->resources()->canDecreaseEnergyAmount(m_energy) && m_basePtr->resources()->canDecreaseBuildingMaterialsAmount(m_bm) && m_basePtr->resources()->canDecreaseFoodSuppliesAmount(m_food)) && m_land != nullptr && m_length != MissionEnums::L_END)
        return 0;

    auto &eqs = m_basePtr->equipment()->availableEquipment();
    if (m_armor != nullptr)
        eqs.remove(eqs.indexOf(m_armor));
    for (int i=0;i < Mercenary::amountOfWeaponToolSlots();++i)
        if (m_weaponTool[i] != nullptr)
            eqs.remove(eqs.indexOf(m_weaponTool[i]));

    m_basePtr->resources()->decreaseAetheriteAmount(m_aetherite);
    m_basePtr->resources()->decreaseEnergyAmount(m_energy);
    m_basePtr->resources()->decreaseBuildingMaterialsAmount(m_bm);
    m_basePtr->resources()->decreaseFoodSuppliesAmount(m_food);

    m_mercenary->setCarriedAetheriteOre(m_aetherite);
    m_mercenary->setCarriedEnergy(m_energy);
    m_mercenary->setCarriedBuildingMaterials(m_bm);
    m_mercenary->setCarriedFoodSupplies(m_food);

    m_mercenary->setCurrentActivity(MercenaryEnums::CA_OnMission);

    Mission *m = m_missionBuilder.generateMission(m_land, m_length);

    m_mercenary->assignMission(m);
    m->assignMercenary(m_mercenary);

    m_basePtr->missions()->startMission(m);

    reset();
    return 1;
}

void MissionInitializer::setLand(const QString &name) noexcept
{
    if (name.isEmpty())
    {
        m_land = nullptr;
        return;
    }
    auto ls = Game::gameInstance()->assetsPool().lands();
    for (auto e : ls)
        if (e->name() == name)
        {
            m_land = e;
            return;
        }
    m_land = nullptr;
}

void MissionInitializer::setLength(const QString & length) noexcept
{
    m_length = MissionEnums::fromQStringToLengthEnum(length);
}

QString MissionInitializer::length() const noexcept
{
    return MissionEnums::fromLengthEnumToQString(m_length);
}

void MissionInitializer::setMercenary(const QString &name) noexcept
{
    if (m_mercenary != nullptr)
        unprepareMercenary();
    if (name.isEmpty())
    {
        m_mercenary = nullptr;
        return;
    }
    auto hs = m_basePtr->mercenaries()->mercenaries()->mercenaries();
    for (int i=0;i < hs.size();++i)
        if (hs[i]->name() == name)
        {
            m_mercenary = m_basePtr->mercenaries()->mercenaries()->getMercenary(i);
            prepareMercenary();
            return;
        }
    m_mercenary = nullptr;
}

void MissionInitializer::setArmor(const QString &name) noexcept
{
    if (name.isEmpty())
    {
        if (m_armor != nullptr)
        {
            m_armor = nullptr;
            if (m_mercenary != nullptr)
                prepareMercenary();
        }
        return;
    }
    auto eqs = m_basePtr->equipment()->availableEquipment();
    for (int i=0;i < eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_armor = eqs[i];
            if (m_mercenary != nullptr)
                prepareMercenary();
            return;
        }
    if (m_armor != nullptr)
    {
        m_armor = nullptr;
        if (m_mercenary != nullptr)
            prepareMercenary();
    }
}

void MissionInitializer::setWeaponTool(const QString &name, unsigned slot) noexcept
{
    if (name.isEmpty() || slot >= Mercenary::amountOfWeaponToolSlots())
    {
        if (m_weaponTool[slot] != nullptr)
        {
            m_weaponTool[slot]=nullptr;
            if (m_mercenary != nullptr)
                prepareMercenary();
        }
        return;
    }
    auto eqs = m_basePtr->equipment()->availableEquipment();
    for (int i=0;i < eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_weaponTool[slot]=eqs[i];
            if (m_mercenary != nullptr)
                prepareMercenary();
            return;
        }
    if (m_weaponTool[slot] != nullptr)
    {
        m_weaponTool[slot]=nullptr;
        if (m_mercenary != nullptr)
            prepareMercenary();
    }
}

void MissionInitializer::setAetherite(unsigned amount) noexcept
{
    m_aetherite = amount;
}

void MissionInitializer::setEnergy(unsigned amount) noexcept
{
    m_energy = amount;
}

void MissionInitializer::setBuildingMaterials(unsigned amount) noexcept
{
    m_bm = amount;
}

void MissionInitializer::setFoodSupplies(unsigned amount) noexcept
{
    m_food = amount;
}

void MissionInitializer::prepareMercenary() noexcept
{
    m_mercenary->removeArmor();
    m_mercenary->equipArmor(m_armor);
    for (int i=0;i < Mercenary::amountOfWeaponToolSlots();++i)
    {
        m_mercenary->removeWeaponTool(i);
        m_mercenary->equipWeaponTool(m_weaponTool[i],i);
    }
}

void MissionInitializer::unprepareMercenary() noexcept
{
    m_mercenary->removeArmor();
    for (int i=0;i < Mercenary::amountOfWeaponToolSlots();++i)
        m_mercenary->removeWeaponTool(i);
}
