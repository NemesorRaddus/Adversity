#ifndef EVENT_H
#define EVENT_H

#include <QMap>
#include <QVector>
#include <QJSEngine>

#include "hero.h"
#include "equipment.h"
#include "base.h"
#include "timer.h"

#include <QDebug>

namespace Randomizer
{
    static void initialize() noexcept
    {
        qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    }
    static unsigned randomBetweenAAndB(unsigned a, unsigned b) noexcept
    {
        return {qrand() % ((b + 1) - a) + a};
    }
}

struct EventEnums
{
    enum Action
    {
        A_Null,
        A_GiveHealth,
        A_GiveStress,
        A_ModifyAttribute,
        A_KillHero,
        A_AddEquipment,
        A_RemoveEquipment,
        A_GiveResource,
        A_NoSignal,
        A_ProlongMission,
        A_END
    };
    enum Check
    {
        C_ValueCheck,
        C_EquipmentCheck,
        C_END
    };
    enum Type
    {
        T_Multi,
        T_Action,
        T_Check,
        T_Possibility,
        T_END
    };
};

class Expression
{
public:
    Expression() noexcept;
    explicit Expression(const QString &expr) noexcept;
    Expression(const Expression &other) noexcept;

    inline explicit operator QString() const noexcept
    {
        return m_expr;
    }

    void set(const QString &expr) noexcept;

    bool isValid() const noexcept;

    QVariant evaluate(const Hero *context) const noexcept;

private:
    void validateExpr() noexcept;
    void handleEngine() noexcept;

    QString m_expr;
    bool m_isExprValid;
    QJSEngine *m_engine;
};

class ValueRange
{
public:
    ValueRange(const Expression &min, const Expression &max) noexcept;
    ValueRange(const Expression &value) noexcept;

    inline Expression min() const noexcept
    {
        return m_min;
    }
    inline Expression max() const noexcept
    {
        return m_max;
    }

    inline bool singleValue() const noexcept
    {
        return static_cast<QString>(m_min)==static_cast<QString>(m_max);
    }

private:
    Expression m_min, m_max;
};

typedef RBoundedValue<int, 0, 100, false> Chance;

typedef QString EventReport;

class Event
{
public:
    inline EventEnums::Type eventType() const noexcept
    {
        return m_eventType;
    }
    inline QString eventText() const noexcept
    {
        return m_eventText;
    }
    inline QVector <QString> unlockedDatabaseEntries() const noexcept
    {
        return m_unlockedDatabaseEntries;
    }

    QVector <EventReport> execute(Hero *context) noexcept;

protected:
    explicit Event(EventEnums::Type eventType) noexcept
        : m_eventType(eventType) {}

    void setEventText(const QString &text) noexcept;

private:
    void unlockDatabaseEntries(Hero *context) noexcept;
    virtual QVector <EventReport> executeSpecificOps(Hero *context) noexcept = 0;

    EventEnums::Type m_eventType;
    QString m_eventText;
    QVector <QString> m_unlockedDatabaseEntries;
};

class MultiEvent final : public Event
{
public:
    MultiEvent(const QVector <Event *> &events) noexcept
        : Event(EventEnums::T_Multi), m_eventsToExecute(events) {}

    QVector <EventReport> executeSpecificOps(Hero *context) noexcept final;

private:
    QVector <Event *> m_eventsToExecute;
};

class ActionEvent : public Event
{
public:
    auto eventResultType() const noexcept
    {
        return m_eventSubtype;
    }
    virtual QVector <EventReport> executeSpecificOps(Hero *hero) noexcept = 0;
    inline EventEnums::Action eventSubtype() const noexcept
    {
        return m_eventSubtype;
    }

protected:
    explicit ActionEvent(EventEnums::Action eventSubtype) noexcept
        : Event(EventEnums::T_Action), m_eventSubtype(eventSubtype) {}

private:
    EventEnums::Action m_eventSubtype;
};

class NullEventResult final : public ActionEvent
{
public:
    NullEventResult() noexcept
        : ActionEvent(EventEnums::A_Null) {}

    inline QVector <EventReport> executeSpecificOps(Hero *) noexcept final
    {
        return {eventText()};
    }
};

class GiveHealthEventResult final : public ActionEvent
{
public:
    explicit GiveHealthEventResult(const Expression &addedValue) noexcept;

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    Expression m_value;
};

class GiveStressEventResult final : public ActionEvent
{
public:
    explicit GiveStressEventResult(const Expression &addedValue) noexcept;

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    Expression m_value;
};

struct AttributeModification
{
    enum Type
    {
        T_Add,
        T_Subtract,
        T_Multiply,
        T_Divide,
        T_Set,
        T_END
    };

    HeroEnums::Attribute attribute;
    Type type;
    Expression expression;
    int duration;
};

class ModifyAttributeEventResult final : public ActionEvent
{
public:
    explicit ModifyAttributeEventResult(const AttributeModification &modification) noexcept;

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    AttributeModification m_modification;
};

class KillHeroEventResult final : public ActionEvent
{
public:
    KillHeroEventResult() noexcept
        : ActionEvent(EventEnums::A_KillHero) {}

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;
};

class AddEquipmentEventResult : public ActionEvent
{
public:
    explicit AddEquipmentEventResult(Equipment *equipment) noexcept
        : ActionEvent(EventEnums::A_AddEquipment), m_equipmentToAdd(equipment) {}

    virtual QVector <EventReport> executeSpecificOps(Hero *hero) noexcept override;

    Equipment *equipmentToAdd() const noexcept
    {
        return m_equipmentToAdd;
    }

protected:
    Equipment *m_equipmentToAdd;
};

class AddEquipmentRandomEventResult final : public AddEquipmentEventResult
{
public:
    AddEquipmentRandomEventResult(ValueRange tier, int equipmentTypeFlags) noexcept;

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    ValueRange m_tier;
    int m_eqTypes;
};

class RemoveEquipmentEventResult final : public ActionEvent
{
public:
    explicit RemoveEquipmentEventResult(EquipmentEnums::Type type, int slot) noexcept
        : ActionEvent(EventEnums::A_RemoveEquipment), m_equipmentType(type), m_equipmentSlot(slot) {}

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

    auto equipmentType() const noexcept
    {
        return m_equipmentType;
    }
    int equipmentSlot() const noexcept
    {
        return m_equipmentSlot;
    }

private:
    EquipmentEnums::Type m_equipmentType;
    int m_equipmentSlot;
};

class GiveResourceEventResult : public ActionEvent
{
public:
    explicit GiveResourceEventResult(BaseEnums::Resource resource, const Expression &amount) noexcept;

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

    inline BaseEnums::Resource resource() const noexcept
    {
        return m_resource;
    }
    inline Expression addedAmount() const noexcept
    {
        return m_amount;
    }

protected:
    BaseEnums::Resource m_resource;
    Expression m_amount;
};

class GiveResourceRandomEventResult final : public GiveResourceEventResult
{
public:
    explicit GiveResourceRandomEventResult(const Expression &amount) noexcept;
};

class NoSignalEventResult final : public ActionEvent
{
public:
    explicit NoSignalEventResult(const Expression &durationInDays) noexcept
        : ActionEvent(EventEnums::A_NoSignal), m_durationInDays(durationInDays) {}

    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

    inline Expression durationInDays() const noexcept
    {
        return m_durationInDays;
    }

private:
    Expression m_durationInDays;
};

class CheckEventResults
{
    friend class CheckEventResultsBuilder;

public:
    CheckEventResults(const CheckEventResults &other) noexcept;

    inline QVector <QPair <Event *, Chance> > positive() const noexcept
    {
        return m_positive;
    }
    inline QVector <QPair <Event *, Chance> > negative() const noexcept
    {
        return m_negative;
    }

private:
    CheckEventResults() noexcept {}

    QVector <QPair <Event *, Chance> > m_positive;
    QVector <QPair <Event *, Chance> > m_negative;
};

class CheckEventResultsBuilder
{
public:
    CheckEventResults get() noexcept;
    void reset() noexcept;

    void addPositive(const QPair <Event *, Chance> &result) noexcept;
    void addNegative(const QPair <Event *, Chance> &result) noexcept;

private:
    void validateJustBeforeReturning() noexcept;

    CheckEventResults m_results;
};

class CheckEvent : public Event
{
public:
    inline auto eventResultType() const noexcept
    {
        return m_eventSubtype;
    }
    virtual QVector <EventReport> executeSpecificOps(Hero *hero) noexcept override = 0;

protected:
    explicit CheckEvent(EventEnums::Check eventSubtype, const CheckEventResults &results) noexcept;

    CheckEventResults m_results;

private:
    EventEnums::Check m_eventSubtype;
};

class ValueCheckEvent final : public CheckEvent
{
public:
    explicit ValueCheckEvent(const Expression &condition, const CheckEventResults &results) noexcept;
    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    Expression m_condition;
};

class EquipmentCheckEvent final : public CheckEvent
{
public:
    explicit EquipmentCheckEvent(EquipmentEnums::Category neededEq, const CheckEventResults &results) noexcept;
    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    EquipmentEnums::Category m_neededEquipment;
};

class PossibilityEvent final : public Event
{
public:
    explicit PossibilityEvent(Chance chance, Event *event) noexcept;
    QVector <EventReport> executeSpecificOps(Hero *hero) noexcept final;

private:
    Chance m_chance;
    Event *m_event;
};

class EncounterReport
{
public:
    EncounterReport(const QString &encName, const QVector <EventReport> &events, const Time &time) noexcept;

    inline const QVector <QString> &text() const noexcept
    {
        return m_events;
    }
    inline const Time &timestamp() const noexcept
    {
        return m_time;
    }

private:
    QString m_encounterName;
    QVector <EventReport> m_events;
    Time m_time;
};

class Encounter
{
public:
    explicit Encounter(const QString &name, Event *rootEvent) noexcept;

    EncounterReport execute(Hero *hero, const Time &currentTime) const noexcept;

private:
    QString m_name;
    Event *m_rootEvent;
};

class EncountersContainer
{
public:
    EncountersContainer() noexcept;
    ~EncountersContainer() noexcept;

    void addEncounter(Encounter *enc) noexcept;
    void removeEncounter(unsigned index) noexcept;
    inline const QVector <Encounter *> &encounters() const noexcept
    {
        return m_encounters;
    }

private:
    QVector <Encounter *> m_encounters;
};

class Land
{
    friend class LandBuilder;

public:
    explicit Land(const QString &name, const QString &description) noexcept;

    void setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept;

    Q_INVOKABLE inline QString name() const noexcept
    {
        return m_name;
    }
    Q_INVOKABLE inline QString description() const noexcept
    {
        return m_description;
    }

    Encounter *getRandomEncounter() const noexcept;

private:
    void setName(const QString &name) noexcept;
    void setDescription(const QString &desc) noexcept;

    QString m_name;
    QString m_description;
    EncountersContainer *m_encounters;
};

class LandBuilder
{
public:
    LandBuilder() noexcept;
    ~LandBuilder() noexcept;

    Land getLand() noexcept;
    void resetLand() noexcept;

    void setName(const QString &name) noexcept;
    void setDescription(const QString &desc) noexcept;

private:
    Land *m_land;
};

class Mission
{
    friend class MissionBuilder;
public:
    Encounter *takeRandomEncounter() noexcept;

    inline const Land *land() const noexcept
    {
        return m_land;
    }
    inline unsigned fullDuration() const noexcept
    {
        return m_duration;
    }
    inline unsigned remainingDays() const noexcept
    {
        return m_remainingDays;
    }
    void decrementDuration() noexcept;

    void assignHero(Hero *hero) noexcept;
    inline const Hero *assignedHero() const noexcept
    {
        return m_assignedHero;
    }

    void start() noexcept;
    void continueToNextEncounter() noexcept;

private:
    Mission() noexcept;

    void setLand(Land *land) noexcept;
    void setDuration(unsigned days) noexcept;
    void addEncounter(Encounter *encounter) noexcept;

    Land *m_land;
    unsigned m_duration;
    unsigned m_remainingDays;
    QVector <Encounter *> m_encounters;
    Hero *m_assignedHero;
};

class MissionBuilder
{
public:
    MissionBuilder() noexcept;
    ~MissionBuilder() noexcept;

    Mission *getMission() noexcept; // resets
    Mission *generateMission(Land *land, unsigned duration) noexcept; // resets
    void resetMission() noexcept;

    void setLand(Land *land) noexcept;
    void setDuration(unsigned duration) noexcept;
    void addRandomEncounter() noexcept;
    void addEncounter(Encounter *encounter) noexcept;

private:
    Mission *m_mission;
};

#endif // EVENT_H
