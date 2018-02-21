#pragma once

#include <QObject>

#include "enums.h"
#include "clock/time.h"
#include "missions/events/event.h"

class Mercenary;
class Land;
class UnifiedReport;
class EncounterReport;
class Encounter;
class Base;
class Equipment;

class Mission : public QObject
{
    friend class MissionBuilder;

    Q_OBJECT

    Q_PROPERTY(Mercenary* mercenary MEMBER m_assignedMercenary)
    Q_PROPERTY(Land* land MEMBER m_land)
    Q_PROPERTY(UnifiedReport* preparedReport MEMBER m_preparedRelatedReport)

public:
    typedef unsigned MissionDay;

    inline const Land *land() const noexcept
    {
        return m_land;
    }
    inline MissionEnums::Length length() const noexcept
    {
        return m_length;
    }
    Q_INVOKABLE inline QString lengthString() const noexcept
    {
        return MissionEnums::fromLengthEnumToQString(length());
    }
    Q_INVOKABLE inline unsigned fullDuration() const noexcept
    {
        return m_duration;
    }
    Q_INVOKABLE inline unsigned remainingDays() const noexcept
    {
        return m_duration-m_daysSpent > 0 ? m_duration-m_daysSpent : 0;
    }
    Q_INVOKABLE inline unsigned daysSpent() const noexcept
    {
        return m_daysSpent;
    }
    void handleNewDay() noexcept;

    void assignMercenary(Mercenary *mercenary) noexcept;
    inline const Mercenary *assignedMercenary() const noexcept
    {
        return m_assignedMercenary;
    }
    inline Mercenary *assignedMercenary() noexcept
    {
        return m_assignedMercenary;
    }

    void start() noexcept;
    EncounterReport *doEncounter(const Time &now) noexcept;
    inline Time timeOfCurrentEncounter() const noexcept
    {
        return m_timeOfCurrentEncounter;
    }

    void end() noexcept;
    void forceEndSuccessfully() noexcept;
    void forceEndSilently() noexcept;
    void forceEndBecauseOfDeath() noexcept;
    Q_INVOKABLE void abort() noexcept;

    void addRelatedReport(UnifiedReport *report) noexcept;
    Q_INVOKABLE void prepareReport(unsigned index) noexcept;
    Q_INVOKABLE inline unsigned amountOfReports() const noexcept
    {
        return m_relatedReports.size();
    }
    inline QVector <UnifiedReport *> &reports() noexcept
    {
        return m_relatedReports;
    }

private:
    Mission() noexcept;

    void planEverything() noexcept;
    void planAllEncounters() noexcept;
    void planEnd() noexcept;

    void setLand(Land *land) noexcept;
    void setLength(MissionEnums::Length length) noexcept;
    void setDuration(unsigned days) noexcept;
    void addEncounter(MissionDay day, Encounter *encounter) noexcept;

    Land *m_land;
    MissionEnums::Length m_length;
    unsigned m_duration;
    unsigned m_daysSpent;
    QVector <QPair <MissionDay, Encounter *> > m_encounters;
    unsigned m_nextEncounter;
    Time m_timeOfCurrentEncounter;
    int m_minutesSinceMidnightOfLastEncounter;
    Mercenary *m_assignedMercenary;
    QVector <UnifiedReport *> m_relatedReports;
    UnifiedReport *m_preparedRelatedReport;
};

struct MissionDataHelper
{
    QString land;
    MissionEnums::Length length;
    unsigned duration, daysSpent;
    QVector <QPair <unsigned, QString> > encounters;
    unsigned nextEncounter;
    int minutesSinceMidnightOfLastEncounter;
    QString mercenary;
    QVector <unsigned> relatedReportsIDs;
};

QDataStream &operator<<(QDataStream &stream, const MissionDataHelper &mission) noexcept;
QDataStream &operator>>(QDataStream &stream, MissionDataHelper &mission) noexcept;

class MissionBuilder
{
public:
    MissionBuilder(Base *base) noexcept;
    ~MissionBuilder() noexcept;

    Mission *getMission() noexcept; // resets
    Mission *generateMission(Land *land, MissionEnums::Length length) noexcept; // resets
    void resetMission() noexcept;

    static Mission *qobjectifyMissionData(const MissionDataHelper &mission, Base *base) noexcept;
    static MissionDataHelper deqobjectifyMission(Mission *mission) noexcept;

    void setLand(Land *land) noexcept;
    void setLength(MissionEnums::Length length) noexcept;
    void setDuration(unsigned duration) noexcept;
    void addRandomEncounter() noexcept;
    void addEncounter(Mission::MissionDay day, Encounter *encounter) noexcept;

private:
    unsigned generateDuration(MissionEnums::Length length) const noexcept;
    unsigned generateAmountOfEncountersPerDay(MissionEnums::Length length) const noexcept;
    QVector <QPair <Mission::MissionDay, Encounter *> > generateEncounters(Land *land, MissionEnums::Length length, unsigned duration) const noexcept;

    static bool lessThanEncounterSorting(const QPair <Mission::MissionDay, Encounter *> &first, const QPair <Mission::MissionDay, Encounter *> &second) noexcept;

    Mission *m_mission;
    Base *m_base;
};

class MissionInitializer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* selectedMercenary MEMBER m_mercenary)

public:
    explicit MissionInitializer(Base *base) noexcept;

    Q_INVOKABLE void reset() noexcept;
    Q_INVOKABLE bool start() noexcept;

    Q_INVOKABLE void setLand(const QString &name) noexcept;
    Q_INVOKABLE void setLength(const QString &length) noexcept;
    Q_INVOKABLE QString length() const noexcept;

    Q_INVOKABLE void setMercenary(const QString &name) noexcept;
    Q_INVOKABLE inline bool isMercenarySelected() const noexcept
    {
        return m_mercenary != nullptr;
    }

    Q_INVOKABLE void setArmor(const QString &name) noexcept;
    Q_INVOKABLE void setWeaponTool(const QString &name, unsigned slot) noexcept;

    Q_INVOKABLE void setAetherite(unsigned amount) noexcept;
    Q_INVOKABLE void setEnergy(unsigned amount) noexcept;
    Q_INVOKABLE void setBuildingMaterials(unsigned amount) noexcept;
    Q_INVOKABLE void setFoodSupplies(unsigned amount) noexcept;

private:
    void prepareMercenary() noexcept;
    void unprepareMercenary() noexcept;

    Base *m_basePtr;
    MissionBuilder m_missionBuilder;
    Land *m_land;
    MissionEnums::Length m_length;
    Mercenary *m_mercenary;
    Equipment *m_armor;
    Equipment *m_weaponTool[2];
    unsigned m_aetherite, m_energy, m_bm, m_food;
};
