#ifndef EVENT_H
#define EVENT_H

#include <QMap>
#include <QVector>

#include "hero.h"
#include "equipment.h"
#include "base.h"

#include <QDebug>

namespace Randomizer
{
    static void initialize() noexcept
    {
        qsrand(qrand());
    }
    static unsigned randomBetweenAAndB(unsigned a, unsigned b) noexcept
    {
        return {qrand() % ((b + 1) - a) + a};
    }
}

struct EventEnums
{
    enum Result
    {
        R_Null,
        R_ModifyAttribute,
        R_KillHero,
        R_AddEquipment,
        R_RemoveEquipment,
        R_CollectResource,
        R_NoSignal,
        R_ProlongMission,
        R_END
    };
    enum Type
    {
        T_AttributeCheck,
        T_END
    };
};

class EventResult
{
public:
    auto eventResultType() const noexcept
    {
        return m_eventResultType;
    }
    virtual void affectHero(Hero *hero) const noexcept = 0;

protected:
    explicit EventResult(EventEnums::Result eventResultType) noexcept
        : m_eventResultType(eventResultType) {}

private:
    EventEnums::Result m_eventResultType;
};

class NullEventResult final : public EventResult
{
public:
    NullEventResult() noexcept
        : EventResult(EventEnums::R_Null) {}

    void affectHero(Hero *hero) const noexcept {}
};

class ModifyAttributeEventResult final : public EventResult
{
public:
    explicit ModifyAttributeEventResult(const QMap <HeroEnums::Attribute, float> &modifications) noexcept;

    void affectHero(Hero *hero) const noexcept;

    int combatEffectiveness() const noexcept
    {
        return m_combatEffectiveness;
    }
    int proficiency() const noexcept
    {
        return m_proficiency;
    }
    int cleverness() const noexcept
    {
        return m_cleverness;
    }
    float luck() const noexcept
    {
        return m_luck;
    }
    int health() const noexcept
    {
        return m_health;
    }
    int healthLimit() const noexcept
    {
        return m_healthLimit;
    }
    int dailyHealthRecovery() const noexcept
    {
        return m_dailyHealthRecovery;
    }
    int stress() const noexcept
    {
        return m_stress;
    }
    float stressResistance() const noexcept
    {
        return m_stressResistance;
    }
    int stressLimit() const noexcept
    {
        return m_stressLimit;
    }
    int stressBorder() const noexcept
    {
        return m_stressBorder;
    }
    int dailyStressRecovery() const noexcept
    {
        return m_dailyStressRecovery;
    }
    int salary() const noexcept
    {
        return m_salary;
    }
    int dailyFoodConsumption() const noexcept
    {
        return m_dailyFoodConsumption;
    }

private:
    int m_combatEffectiveness;
    int m_proficiency;
    int m_cleverness;
    float m_luck;
    int m_health;
    int m_healthLimit;
    int m_dailyHealthRecovery;
    int m_stress;
    float m_stressResistance;
    int m_stressLimit;
    int m_stressBorder;
    int m_dailyStressRecovery;
    int m_salary;
    int m_dailyFoodConsumption;
};

class KillHeroEventResult final : public EventResult
{
public:
    KillHeroEventResult() noexcept
        : EventResult(EventEnums::R_KillHero) {}

    void affectHero(Hero *hero) const noexcept;
};

class AddEquipmentEventResult final : public EventResult
{
public:
    explicit AddEquipmentEventResult(Equipment *equipment) noexcept
        : EventResult(EventEnums::R_AddEquipment), m_equipmentToAdd(equipment) {}

    void affectHero(Hero *hero) const noexcept;

    Equipment *equipmentToAdd() const noexcept
    {
        return m_equipmentToAdd;
    }

private:
    Equipment *m_equipmentToAdd;
};

class RemoveEquipmentEventResult final : public EventResult
{
public:
    explicit RemoveEquipmentEventResult(EquipmentEnums::Type type, int slot) noexcept
        : EventResult(EventEnums::R_RemoveEquipment), m_equipmentType(type), m_equipmentSlot(slot) {}

    void affectHero(Hero *hero) const noexcept;

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

class CollectResourceEventResult final : public EventResult
{
public:
    explicit CollectResourceEventResult(const QMap<BaseEnums::Resource, int> &resources) noexcept;

    void affectHero(Hero *hero) const noexcept;

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

class NoSignalEventResult final : public EventResult
{
public:
    explicit NoSignalEventResult(int durationInDays) noexcept
        : EventResult(EventEnums::R_NoSignal), m_durationInDays(durationInDays) {}

    void affectHero(Hero *hero) const noexcept;

    int durationInDays() const noexcept
    {
        return m_durationInDays;
    }

private:
    int m_durationInDays;
};

class ProlongMissionEventResult final : public EventResult
{
public:
    explicit ProlongMissionEventResult(int days) noexcept
        : EventResult(EventEnums::R_ProlongMission), m_additionalDays(days) {}

    void affectHero(Hero *hero) const noexcept;

    int additionalDays() const noexcept
    {
        return m_additionalDays;
    }

private:
    int m_additionalDays;
};

class Event
{
public:
    auto eventType() const noexcept
    {
        return m_eventType;
    }
    EventResult *eventResult(int index) const noexcept
    {
        return m_eventResults.value(index,nullptr);
    }
    int amountOfEventResults() const noexcept
    {
        return m_eventResults.size();
    }
    virtual void execute(Hero *hero) const noexcept = 0;

protected:
    explicit Event(EventEnums::Type eventType, const QVector <EventResult *> &eventResults) noexcept
        : m_eventType(eventType), m_eventResults(eventResults) {}

private:
    EventEnums::Type m_eventType;
    QVector <EventResult *> m_eventResults;
};

class AttributeCheckEvent final : public Event
{
public:
    explicit AttributeCheckEvent(const QMap <HeroEnums::Attribute, float> &attributeChecks, float chancePositive, float chanceNegative, EventResult *eventResultPositivePositive, EventResult *eventResultPositiveNegative, EventResult *eventResultNegativePositive, EventResult *eventResultNegativeNegative) noexcept;
    void execute(Hero *hero) const noexcept final;

private:
    bool checkIfResultPositive(Hero *hero) const noexcept;

    int m_combatEffectiveness;
    int m_proficiency;
    int m_cleverness;
    float m_luck;
    int m_health;
    int m_healthLimit;
    int m_dailyHealthRecovery;
    int m_stress;
    float m_stressResistance;
    int m_stressLimit;
    int m_stressBorder;
    int m_dailyStressRecovery;
    int m_salary;
    int m_dailyFoodConsumption;

    float m_chancePositive, m_chanceNegative;//chance that when attrCheck's result is [...], result will be [...]Positive
};

class Mission
{
    friend class MissionBuilder;
public:
    Event *takeRandomEvent() noexcept;

    QString name() const noexcept
    {
        return m_name;
    }
    QString description() const noexcept
    {
        return m_description;
    }

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

    void setName(const QString &name) noexcept;
    void setDescription(const QString &description) noexcept;
    void setDuration(int days) noexcept;
    void addEvent(Event *event) noexcept;

    QString m_name;
    QString m_description;
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

    void setName(const QString &name) noexcept;
    void setDescription(const QString &description) noexcept;
    void setDuration(int duration) noexcept;
    void addEvent(Event *event) noexcept;

private:
    Mission *m_mission;
};

#endif // EVENT_H
