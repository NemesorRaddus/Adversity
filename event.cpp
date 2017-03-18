#include "event.h"

#include <QDebug>

ModifyAttributeEventResult::ModifyAttributeEventResult(const QMap<HeroEnums::Attribute, float> &modifications) noexcept
    : EventResult(EventEnums::R_ModifyAttribute)
{
    m_combatEffectiveness=modifications.value(HeroEnums::A_CombatEffectiveness,0);
    m_proficiency=modifications.value(HeroEnums::A_Proficiency,0);
    m_cleverness=modifications.value(HeroEnums::A_Cleverness,0);
    m_luck=modifications.value(HeroEnums::A_Luck,0);
    m_health=modifications.value(HeroEnums::A_Health,0);
    m_healthLimit=modifications.value(HeroEnums::A_HealthLimit,0);
    m_dailyHealthRecovery=modifications.value(HeroEnums::A_DailyHealthRecovery,0);
    m_stress=modifications.value(HeroEnums::A_Stress,0);
    m_stressResistance=modifications.value(HeroEnums::A_StressResistance,0);
    m_stressLimit=modifications.value(HeroEnums::A_StressLimit,0);
    m_stressBorder=modifications.value(HeroEnums::A_StressBorder,0);
    m_dailyStressRecovery=modifications.value(HeroEnums::A_DailyStressRecovery,0);
    m_salary=modifications.value(HeroEnums::A_Salary,0);
    m_dailyFoodConsumption=modifications.value(HeroEnums::A_DailyFoodConsumption,0);
}

void ModifyAttributeEventResult::affectHero(Hero *hero) const noexcept
{
    hero->setCombatEffectiveness(hero->combatEffectiveness()+combatEffectiveness());
    hero->setProficiency(hero->proficiency()+proficiency());
    hero->setCleverness(hero->cleverness()+cleverness());
    hero->setLuck(hero->luck()+luck());
    hero->setHealth(hero->health()+health());
    hero->setHealthLimit(hero->healthLimit()+healthLimit());
    hero->setDailyHealthRecovery(hero->dailyHealthRecovery()+dailyHealthRecovery());
    hero->setStress(hero->stress()+stress());
    hero->setStressResistance(hero->stressResistance()+stressResistance());
    hero->setStressLimit(hero->stressLimit()+stressLimit());
    hero->setStressBorder(hero->stressBorder()+stressBorder());
    hero->setDailyStressRecovery(hero->dailyStressRecovery()+dailyStressRecovery());
    hero->setDailyFoodConsumption(hero->dailyFoodConsumption()+dailyFoodConsumption());
}

void KillHeroEventResult::affectHero(Hero *hero) const noexcept
{
    hero->setIsDead(1);
}

void AddEquipmentEventResult::affectHero(Hero *hero) const noexcept
{

}

void RemoveEquipmentEventResult::affectHero(Hero *hero) const noexcept
{
    if (m_equipmentType==EquipmentEnums::Armor)
        hero->setArmor(NULL);
    else
        hero->setWeaponTool(NULL,m_equipmentSlot);
}

CollectResourceEventResult::CollectResourceEventResult(const QMap<BaseEnums::Resource, int> &resources) noexcept
    : EventResult(EventEnums::R_CollectResource)
{
    m_energy=resources.value(BaseEnums::R_Energy,0);
    m_foodSupplies=resources.value(BaseEnums::R_FoodSupplies,0);
    m_buildingMaterials=resources.value(BaseEnums::R_BuildingMaterials,0);
    m_aetheriteOre=resources.value(BaseEnums::R_AetheriteOre,0);
}

void CollectResourceEventResult::affectHero(Hero *hero) const noexcept
{
    hero->setCarriedEnergy(hero->carriedEnergy()+m_energy);
    hero->setCarriedFoodSupplies(hero->carriedFoodSupplies()+m_foodSupplies);
    hero->setCarriedBuildingMaterials(hero->carriedBuildingMaterials()+m_buildingMaterials);
    hero->setCarriedAetheriteOre(hero->carriedAetheriteOre()+m_aetheriteOre);
}

void NoSignalEventResult::affectHero(Hero *hero) const noexcept
{
    hero->setNoSignalDaysRemaining(hero->noSignalDaysRemaining()+m_durationInDays);
}

void ProlongMissionEventResult::affectHero(Hero *hero) const noexcept
{

}

AttributeCheckEvent::AttributeCheckEvent(const QMap<HeroEnums::Attribute, float> &attributeChecks, float chancePositive, float chanceNegative, EventResult *eventResultPositivePositive, EventResult *eventResultPositiveNegative, EventResult *eventResultNegativePositive, EventResult *eventResultNegativeNegative) noexcept
    : Event(EventEnums::T_AttributeCheck, QVector <EventResult *>(std::initializer_list <EventResult *>{eventResultPositivePositive, eventResultPositiveNegative, eventResultNegativePositive, eventResultNegativeNegative}))
{
    m_combatEffectiveness=attributeChecks.value(HeroEnums::A_CombatEffectiveness,0);
    m_proficiency=attributeChecks.value(HeroEnums::A_Proficiency,0);
    m_cleverness=attributeChecks.value(HeroEnums::A_Cleverness,0);
    m_luck=attributeChecks.value(HeroEnums::A_Luck,0);
    m_health=attributeChecks.value(HeroEnums::A_Health,0);
    m_healthLimit=attributeChecks.value(HeroEnums::A_HealthLimit,0);
    m_dailyHealthRecovery=attributeChecks.value(HeroEnums::A_DailyHealthRecovery,0);
    m_stress=attributeChecks.value(HeroEnums::A_Stress,0);
    m_stressResistance=attributeChecks.value(HeroEnums::A_StressResistance,0);
    m_stressLimit=attributeChecks.value(HeroEnums::A_StressLimit,0);
    m_stressBorder=attributeChecks.value(HeroEnums::A_StressBorder,0);
    m_dailyStressRecovery=attributeChecks.value(HeroEnums::A_DailyStressRecovery,0);
    m_salary=attributeChecks.value(HeroEnums::A_Salary,0);
    m_dailyFoodConsumption=attributeChecks.value(HeroEnums::A_DailyFoodConsumption,0);
}

void AttributeCheckEvent::execute(Hero *hero) const noexcept
{
    if (hero==0)
        return;

    EventResult *result;
    if (checkIfResultPositive(hero))
    {
        if (Randomizer::randomBetweenAAndB(0,100)<=m_chancePositive*100)
            result=eventResult(0);
        else
            result=eventResult(1);
    }
    else
    {
        if ((Randomizer::randomBetweenAAndB(0,100)<=m_chanceNegative*100))
            result=eventResult(2);
        else
            result=eventResult(3);
    }

    if (result->eventResultType()==EventEnums::R_Null)
        static_cast<NullEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_ModifyAttribute)
        static_cast<ModifyAttributeEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_KillHero)
        static_cast<KillHeroEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_AddEquipment)
        static_cast<AddEquipmentEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_RemoveEquipment)
        static_cast<RemoveEquipmentEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_CollectResource)
        static_cast<CollectResourceEventResult *>(result)->affectHero(hero);
    else if (result->eventResultType()==EventEnums::R_NoSignal)
        static_cast<NoSignalEventResult *>(result)->affectHero(hero);
    else
        static_cast<ProlongMissionEventResult *>(result)->affectHero(hero);
}

bool AttributeCheckEvent::checkIfResultPositive(Hero *hero) const noexcept
{
    if (hero->combatEffectiveness()<m_combatEffectiveness)
        return 0;
    if (hero->proficiency()<m_proficiency)
        return 0;
    if (hero->cleverness()<m_cleverness)
        return 0;
    if (hero->luck()<m_luck)
        return 0;
    if (hero->health()<m_health)
        return 0;
    if (hero->healthLimit()<m_healthLimit)
        return 0;
    if (hero->dailyHealthRecovery()<m_dailyHealthRecovery)
        return 0;
    if (hero->stress()<m_stress)
        return 0;
    if (hero->stressResistance()<m_stressResistance)
        return 0;
    if (hero->stressLimit()<m_stressLimit)
        return 0;
    if (hero->stressBorder()<m_stressBorder)
        return 0;
    if (hero->dailyStressRecovery()<m_dailyStressRecovery)
        return 0;
    if (hero->salary()<m_salary)
        return 0;
    if (hero->dailyFoodConsumption()<m_dailyFoodConsumption)
        return 0;
}

Event *Mission::takeRandomEvent() noexcept
{
    return m_events.takeAt(Randomizer::randomBetweenAAndB(0,m_events.size()-1));
}

void Mission::decrementDuration() noexcept
{
    --m_duration;
}

void Mission::prolongDuration(int additionalDays) noexcept
{
    if (additionalDays<1)
        return;
    m_duration+=additionalDays;
}

void Mission::assignHero(Hero *hero) noexcept
{
    m_assignedHero=hero;
}

void Mission::reset() noexcept
{
    m_name.clear();
    m_description.clear();
    m_duration=1;
    m_events.clear();
    m_assignedHero=NULL;
}

void Mission::setName(const QString &name) noexcept
{
    m_name=name;
}

void Mission::setDescription(const QString &description) noexcept
{
    m_description=description;
}

void Mission::setDuration(int days) noexcept
{
    if (days<1)
        return;
    m_duration=days;
}

void Mission::addEvent(Event *event) noexcept
{
    m_events+=event;
}

MissionBuilder::MissionBuilder() noexcept
{
    m_mission=new Mission();
}

MissionBuilder::~MissionBuilder() noexcept
{
    delete m_mission;
}

Mission *MissionBuilder::getMission() const noexcept
{
    Mission *ret=new Mission();
    *ret=*m_mission;
    return ret;
}

void MissionBuilder::resetMission() noexcept
{
    m_mission->reset();
}

void MissionBuilder::setName(const QString &name) noexcept
{
    m_mission->setName(name);
}

void MissionBuilder::setDescription(const QString &description) noexcept
{
    m_mission->setDescription(description);
}

void MissionBuilder::setDuration(int duration) noexcept
{
    m_mission->setDuration(duration);
}

void MissionBuilder::addEvent(Event *event) noexcept
{
    m_mission->addEvent(event);
}
