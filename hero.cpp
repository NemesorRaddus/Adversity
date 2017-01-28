#include "hero.h"

void Hero::setCombatEffectiveness(int combatEffectiveness) noexcept
{
    m_combatEffectiveness=combatEffectiveness;
}

void Hero::setProficiency(int proficiency) noexcept
{
    m_proficiency=proficiency;
}

void Hero::setCleverness(int cleverness) noexcept
{
    m_cleverness=cleverness;
}

void Hero::setLuck(float luck) noexcept
{
    m_luck=luck;
}

void Hero::setHealth(int health) noexcept
{
    m_health=health;
}

void Hero::setHealthLimit(int healthLimit) noexcept
{
    m_healthLimit=healthLimit;
}

void Hero::setDailyHealthRecovery(int dailyHealthRecovery) noexcept
{
    m_dailyHealthRecovery=dailyHealthRecovery;
}

void Hero::setStress(int stress) noexcept
{
    m_stress=stress;
}

void Hero::setStressResistance(float stressResistance) noexcept
{
    m_stressResistance=stressResistance;
}

void Hero::setStressLimit(int stressLimit) noexcept
{
    m_stressLimit=stressLimit;
}

void Hero::setStressBorder(int stressBorder) noexcept
{
    m_stressBorder=stressBorder;
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
