#include "hero.h"

#include <QDebug>

void Hero::setCombatEffectiveness(int combatEffectiveness) noexcept
{
    if (combatEffectiveness>=0)
        m_combatEffectiveness=combatEffectiveness;
    else
        m_combatEffectiveness=0;
}

void Hero::setProficiency(int proficiency) noexcept
{
    if (proficiency>=0)
        m_proficiency=proficiency;
    else
        m_proficiency=0;
}

void Hero::setCleverness(int cleverness) noexcept
{
    if (cleverness>=0)
        m_cleverness=cleverness;
    else
        m_cleverness=0;
}

void Hero::setLuck(float luck) noexcept
{
    m_luck=luck;
}

void Hero::setHealth(int health) noexcept
{
    if (health>=0)
    {
        if (health<=m_healthLimit)
            m_health=health;
        else
            m_health=m_healthLimit;
    }
    else
        m_health=0;
}

void Hero::setHealthLimit(int healthLimit) noexcept
{
    if (healthLimit>0)
    {
        m_healthLimit=healthLimit;
        if (m_health>m_healthLimit)
            m_health=m_healthLimit;
    }
    else
    {
        m_healthLimit=1;
        if (m_health>1)
            m_health=1;
    }
}

void Hero::setDailyHealthRecovery(int dailyHealthRecovery) noexcept
{
    m_dailyHealthRecovery=dailyHealthRecovery;
}

void Hero::setStress(int stress) noexcept
{
    if (stress>=0)
    {
        m_stress=stress;
        //if (stress>=)
    }
    else
        m_stress=0;
}

void Hero::setStressResistance(float stressResistance) noexcept
{
    m_stressResistance=stressResistance;
}

void Hero::setStressLimit(int stressLimit) noexcept
{
    if (stressLimit>0)
    {
        m_stressLimit=stressLimit;
        if (m_stress>m_stressLimit)
            m_stress=m_stressLimit;
    }
    else
    {
        m_stressLimit=1;
        if (m_stress>1)
            m_stress=1;
    }
}

void Hero::setStressBorder(int stressBorder) noexcept
{
    if (stressBorder<0)//TODO activate effect
        stressBorder=0;
    else
    {
        if (stressBorder<m_stressLimit)
            m_stressBorder=stressBorder;
        else
            m_stressBorder=m_stressLimit;
    }
}

void Hero::setDailyStressRecovery(int dailyStressRecovery) noexcept
{
    m_dailyStressRecovery=dailyStressRecovery;
}

void Hero::setSalary(int salary) noexcept
{
    m_salary=salary;
}

void Hero::setDailyFoodConsumption(int dailyFoodConsumption) noexcept
{
    m_dailyFoodConsumption=dailyFoodConsumption;
}

void Hero::setArmor(Equipment *armor) noexcept
{
    m_armor=armor;
}

void Hero::setWeaponTool(Equipment *weaponTool, int slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots)
        m_weaponsTools[slot]=weaponTool;
}

Hero::Hero() noexcept
{

}

void Hero::setCarriedEnergy(int carriedEnergy) noexcept
{
    m_carriedEnergy = carriedEnergy;
}

void Hero::setCarriedFoodSupplies(int carriedFoodSupplies) noexcept
{
    m_carriedFoodSupplies = carriedFoodSupplies;
}

void Hero::setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept
{
    m_carriedBuildingMaterials = carriedBuildingMaterials;
}

void Hero::setCarriedAetheriteOre(int carriedAetheriteOre) noexcept
{
    m_carriedAetheriteOre = carriedAetheriteOre;
}

void Hero::assignMission(Mission *mission) noexcept
{
    m_assignedMission=mission;
    m_currentActivity=HeroEnums::CA_OnMission;
}

void Hero::setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept
{
    m_currentActivity=activity;
    if (activity==HeroEnums::CA_OnMission)
        m_assignedMission=NULL;
}

void Hero::setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept
{
    m_noSignalDaysRemaining = noSignalDaysRemaining;
}

void Hero::setIsDead(bool isDead) noexcept
{
    m_isDead = isDead;
}

void Hero::setName(const QString &name) noexcept
{
    m_name=name;
}

void Hero::setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept
{
    m_stressBorderEffect=stressBorderEffect;
}

void Hero::setNature(HeroEnums::Nature nature) noexcept
{
    m_nature=nature;
}

void Hero::activateStressBorderEffect() noexcept
{
    //TODO
}

void Hero::deactivateStressBorderEffect() noexcept
{
    //TODO
}

