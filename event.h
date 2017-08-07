#ifndef EVENT_H
#define EVENT_H

#include <QMap>
#include <QVector>
#include <QJSEngine>

#include "hero.h"
#include "equipment.h"
#include "base.h"

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
        A_ModifyAttribute,
        A_KillHero,
        A_AddEquipment,
        A_RemoveEquipment,
        A_CollectResource,
        A_NoSignal,
        A_ProlongMission,
        A_END
    };
    enum Check
    {
        C_AttributeCheck,
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
    explicit Expression(const Expression &other) noexcept;

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

class Chance// int with <0;100> range
{
public:
    Chance() noexcept
        : m_chance(0) {}
    Chance(int chance) noexcept
        : m_chance(0)
    {
        if (chance >= 0 && chance<=100)
            m_chance=chance;
    }

    operator int() const noexcept
    {
        return m_chance;
    }

    void operator =(int chance) noexcept
    {
        if (chance >= 0 && chance<=100)
            m_chance=chance;
    }

private:
    int m_chance;
};

class Event
{
public:
    EventEnums::Type eventType() const noexcept
    {
        return m_eventType;
    }
    virtual void execute(Hero *context) noexcept = 0;

protected:
    explicit Event(EventEnums::Type eventType) noexcept
        : m_eventType(eventType) {}

private:
    EventEnums::Type m_eventType;
};

class MultiEvent final : public Event
{
public:
    MultiEvent(const QVector <Event *> &events) noexcept
        : Event(EventEnums::T_Multi), m_eventsToExecute(events) {}

    void execute(Hero *context) noexcept final;

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
    virtual void execute(Hero *hero) noexcept = 0;
    EventEnums::Action eventSubtype() const noexcept
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

    void execute(Hero *hero) noexcept final {}
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

    void execute(Hero *hero) noexcept final;

private:
    AttributeModification m_modification;
};

class KillHeroEventResult final : public ActionEvent
{
public:
    KillHeroEventResult() noexcept
        : ActionEvent(EventEnums::A_KillHero) {}

    void execute(Hero *hero) noexcept final;
};

class AddEquipmentEventResult final : public ActionEvent
{
public:
    explicit AddEquipmentEventResult(Equipment *equipment) noexcept
        : ActionEvent(EventEnums::A_AddEquipment), m_equipmentToAdd(equipment) {}

    void execute(Hero *hero) noexcept final;

    Equipment *equipmentToAdd() const noexcept
    {
        return m_equipmentToAdd;
    }

private:
    Equipment *m_equipmentToAdd;
};

class RemoveEquipmentEventResult final : public ActionEvent
{
public:
    explicit RemoveEquipmentEventResult(EquipmentEnums::Type type, int slot) noexcept
        : ActionEvent(EventEnums::A_RemoveEquipment), m_equipmentType(type), m_equipmentSlot(slot) {}

    void execute(Hero *hero) noexcept final;

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

class CollectResourceEventResult final : public ActionEvent
{
public:
    explicit CollectResourceEventResult(const QMap<BaseEnums::Resource, int> &resources) noexcept;

    void execute(Hero *hero) noexcept final;

    int energy() const noexcept
    {
        return m_energy;
    }
    int foodSupplies() const noexcept
    {
        return m_foodSupplies;
    }
    int buildingMaterials() const noexcept
    {
        return m_buildingMaterials;
    }
    int aetheriteOre() const noexcept
    {
        return m_aetheriteOre;
    }

private:
    int m_energy;
    int m_foodSupplies;
    int m_buildingMaterials;
    int m_aetheriteOre;
};

class NoSignalEventResult final : public ActionEvent
{
public:
    explicit NoSignalEventResult(int durationInDays) noexcept
        : ActionEvent(EventEnums::A_NoSignal), m_durationInDays(durationInDays) {}

    void execute(Hero *hero) noexcept final;

    int durationInDays() const noexcept
    {
        return m_durationInDays;
    }

private:
    int m_durationInDays;
};

class ProlongMissionEventResult final : public ActionEvent
{
public:
    explicit ProlongMissionEventResult(int days) noexcept
        : ActionEvent(EventEnums::A_ProlongMission), m_additionalDays(days) {}

    void execute(Hero *hero) noexcept final;

    int additionalDays() const noexcept
    {
        return m_additionalDays;
    }

private:
    int m_additionalDays;
};

class CheckEventResults
{
    friend class CheckEventResultsBuilder;

public:
    CheckEventResults(const CheckEventResults &other) noexcept;

    QVector <QPair <Event *, Chance> > positive() const noexcept
    {
        return m_positive;
    }
    QVector <QPair <Event *, Chance> > negative() const noexcept
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
    auto eventResultType() const noexcept
    {
        return m_eventSubtype;
    }
    virtual void execute(Hero *hero) noexcept = 0;

protected:
    explicit CheckEvent(EventEnums::Check eventSubtype, const CheckEventResults &results) noexcept;

    CheckEventResults m_results;

private:
    EventEnums::Check m_eventSubtype;
};

class AttributeCheckEvent final : public CheckEvent
{
public:
    explicit AttributeCheckEvent(const Expression &condition, const CheckEventResults &results) noexcept;
    void execute(Hero *hero) noexcept final;

private:
    Expression m_condition;
};

class EquipmentCheckEvent final : public CheckEvent
{
public:
    explicit EquipmentCheckEvent(EquipmentEnums::Category neededEq, const CheckEventResults &results) noexcept;
    void execute(Hero *hero) noexcept final;

private:
    EquipmentEnums::Category m_neededEquipment;
};

class PossibilityEvent final : public Event
{
public:
    explicit PossibilityEvent(Chance chance, Event *event) noexcept;
    void execute(Hero *hero) noexcept final;

private:
    Chance m_chance;
    Event *m_event;
};

class Encounter
{
public:
    Encounter(QString name, QVector <Event *> events) noexcept;

private:
    QString m_name;
    QVector <Event *> m_events;
};

class Mission
{
    friend class MissionBuilder;
public:
    Event *takeRandomEvent() noexcept;

    int duration() const noexcept
    {
        return m_duration;
    }
    void decrementDuration() noexcept;
    void prolongDuration(int additionalDays) noexcept;

    void assignHero(Hero *hero) noexcept;
    Hero *assignedHero() const noexcept
    {
        return m_assignedHero;
    }

private:
    Mission() noexcept {}

    void reset() noexcept;

    void setDuration(int days) noexcept;
    void addEvent(Event *event) noexcept;

    int m_duration;
    QVector <Event *> m_events;
    Hero *m_assignedHero;
};

class MissionBuilder
{
public:
    MissionBuilder() noexcept;
    ~MissionBuilder() noexcept;

    Mission *getMission() const noexcept;
    void resetMission() noexcept;

    void setDuration(int duration) noexcept;
    void addEvent(Event *event) noexcept;

private:
    Mission *m_mission;
};

#endif // EVENT_H
