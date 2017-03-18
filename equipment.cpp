#include "equipment.h"

#include <QDebug>

void Equipment::reset() noexcept
{
    m_name.clear();
    m_type=EquipmentEnums::WeaponTool;
    m_tier=1;
    m_combatEffectivenessBonus=0;
    m_proficiencyBonus=0;
    m_clevernessBonus=0;
    m_luckBonus=0;
    m_healthBonus=0;
    m_healthLimitBonus=0;
    m_dailyHealthRecoveryBonus=0;
    m_stressBonus=0;
    m_stressResistanceBonus=0;
    m_stressLimitBonus=0;
    m_stressBorderBonus=0;
    m_dailyStressRecoveryBonus=0;
    m_salaryBonus=0;
    m_dailyFoodConsumptionBonus=0;
}

Equipment::Equipment() noexcept
{

}

void Equipment::setName(const QString &name) noexcept
{
    m_name = name;
}

void Equipment::setType(EquipmentEnums::Type type) noexcept
{
    m_type = type;
}

void Equipment::setTier(int tier) noexcept
{
    if (tier<1)
        return;
    m_tier = tier;
}

void Equipment::setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept
{
    m_combatEffectivenessBonus = combatEffectivenessBonus;
}

void Equipment::setProficiencyBonus(int proficiencyBonus) noexcept
{
    m_proficiencyBonus = proficiencyBonus;
}

void Equipment::setClevernessBonus(int clevernessBonus) noexcept
{
    m_clevernessBonus = clevernessBonus;
}

void Equipment::setLuckBonus(float luckBonus) noexcept
{
    m_luckBonus = luckBonus;
}

void Equipment::setHealthBonus(int healthBonus) noexcept
{
    m_healthBonus = healthBonus;
}

void Equipment::setHealthLimitBonus(int healthLimitBonus) noexcept
{
    m_healthLimitBonus = healthLimitBonus;
}

void Equipment::setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept
{
    m_dailyHealthRecoveryBonus = dailyHealthRecoveryBonus;
}

void Equipment::setStressBonus(int stressBonus) noexcept
{
    m_stressBonus = stressBonus;
}

void Equipment::setStressResistanceBonus(float stressResistanceBonus) noexcept
{
    m_stressResistanceBonus = stressResistanceBonus;
}

void Equipment::setStressLimitBonus(int stressLimitBonus) noexcept
{
    m_stressLimitBonus = stressLimitBonus;
}

void Equipment::setStressBorderBonus(int stressBorderBonus) noexcept
{
    m_stressBorderBonus = stressBorderBonus;
}

void Equipment::setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept
{
    m_dailyStressRecoveryBonus = dailyStressRecoveryBonus;
}

void Equipment::setSalaryBonus(int salaryBonus) noexcept
{
    m_salaryBonus = salaryBonus;
}

void Equipment::setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept
{
    m_dailyFoodConsumptionBonus = dailyFoodConsumptionBonus;
}

EquipmentBuilder::EquipmentBuilder() noexcept
{
    m_equipment=new Equipment();
}

EquipmentBuilder::~EquipmentBuilder() noexcept
{
    delete m_equipment;
}

Equipment *EquipmentBuilder::getEquipment() noexcept
{
    Equipment *ret=new Equipment();
    *ret=*m_equipment;
    return ret;
}

void EquipmentBuilder::resetEquiment() noexcept
{
    m_equipment->reset();
}

void EquipmentBuilder::setName(const QString &name) noexcept
{
    m_equipment->setName(name);
}

void EquipmentBuilder::setType(EquipmentEnums::Type type) noexcept
{
    m_equipment->setType(type);
}

void EquipmentBuilder::setTier(int tier) noexcept
{
    m_equipment->setTier(tier);
}

void EquipmentBuilder::setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept
{
    m_equipment->setCombatEffectivenessBonus(combatEffectivenessBonus);
}

void EquipmentBuilder::setProficiencyBonus(int proficiencyBonus) noexcept
{
    m_equipment->setProficiencyBonus(proficiencyBonus);
}

void EquipmentBuilder::setClevernessBonus(int clevernessBonus) noexcept
{
    m_equipment->setClevernessBonus(clevernessBonus);
}

void EquipmentBuilder::setLuckBonus(float luckBonus) noexcept
{
    m_equipment->setLuckBonus(luckBonus);
}

void EquipmentBuilder::setHealthBonus(int healthBonus) noexcept
{
    m_equipment->setHealthBonus(healthBonus);
}

void EquipmentBuilder::setHealthLimitBonus(int healthLimitBonus) noexcept
{
    m_equipment->setHealthLimitBonus(healthLimitBonus);
}

void EquipmentBuilder::setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept
{
    m_equipment->setDailyHealthRecoveryBonus(dailyHealthRecoveryBonus);
}

void EquipmentBuilder::setStressBonus(int stressBonus) noexcept
{
    m_equipment->setStressBonus(stressBonus);
}

void EquipmentBuilder::setStressResistanceBonus(float stressResistanceBonus) noexcept
{
    m_equipment->setStressResistanceBonus(stressResistanceBonus);
}

void EquipmentBuilder::setStressLimitBonus(int stressLimitBonus) noexcept
{
    m_equipment->setStressLimitBonus(stressLimitBonus);
}

void EquipmentBuilder::setStressBorderBonus(int stressBorderBonus) noexcept
{
    m_equipment->setStressBorderBonus(stressBorderBonus);
}

void EquipmentBuilder::setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept
{
    m_equipment->setDailyStressRecoveryBonus(dailyStressRecoveryBonus);
}

void EquipmentBuilder::setSalaryBonus(int salaryBonus) noexcept
{
    m_equipment->setSalaryBonus(salaryBonus);
}

void EquipmentBuilder::setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept
{
    m_equipment->setDailyFoodConsumptionBonus(dailyFoodConsumptionBonus);
}
