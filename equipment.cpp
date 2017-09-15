#include "equipment.h"

#include "game.h"

#include <QDebug>

EquipmentEnums::Type EquipmentEnums::fromQStringToTypeEnum(const QString &type) noexcept
{
    if (type == "Armor")
        return T_Armor;
    if (type == "Weapon/Tool")
        return T_WeaponTool;
    qWarning()<<"QString->enum conversion failed for "<<type;
}

QString EquipmentEnums::fromTypeEnumToQString(EquipmentEnums::Type type) noexcept
{
    if (type == T_Armor)
        return "Armor";
    if (type == T_WeaponTool)
        return "Weapon/Tool";
    qWarning()<<"QString->enum conversion failed for "<<type;
}

EquipmentEnums::Category EquipmentEnums::fromQStringToCategoryEnum(const QString &category) noexcept
{
    if (category == "Biohazard Protection")
        return C_BiohazardProtection;
    if (category == "Climbing")
        return C_Climbing;
    if (category == "Light Source")
        return C_LightSource;
    qWarning()<<"QString->enum conversion failed for "<<category;
}

QString EquipmentEnums::fromCategoryEnumToQString(EquipmentEnums::Category category) noexcept
{
    if (category == C_BiohazardProtection)
        return "Biohazard Protection";
    if (category == C_Climbing)
        return "Climbing";
    if (category == C_LightSource)
        return "Light Source";
    qWarning()<<"QString->enum conversion failed for "<<category;
}

EquipmentEnums::Bonus EquipmentEnums::fromQStringToBonusEnum(const QString &bonus) noexcept
{
    if (bonus == "Combat Effectiveness")
        return B_CombatEffectiveness;
    if (bonus == "Proficiency")
        return B_Proficiency;
    if (bonus == "Cleverness")
        return B_Cleverness;
    if (bonus == "Luck")
        return B_Luck;
    if (bonus == "Health Limit")
        return B_HealthLimit;
    if (bonus == "Daily Health Recovery")
        return B_DailyHealthRecovery;
    if (bonus == "Stress Resistance")
        return B_StressResistance;
    if (bonus == "Stress Limit")
        return B_StressLimit;
    if (bonus == "Stress Border")
        return B_StressBorder;
    if (bonus == "Daily Stress Recovery")
        return B_DailyStressRecovery;
    if (bonus == "Salary")
        return B_Salary;
    if (bonus == "Daily Food Consumption")
        return B_DailyFoodConsumption;
    qWarning()<<"QString->enum conversion failed for "<<bonus;
}

QString EquipmentEnums::fromBonusEnumToQString(EquipmentEnums::Bonus bonus) noexcept
{
    if (bonus == B_CombatEffectiveness)
        return "Combat Effectiveness";
    if (bonus == B_Proficiency)
        return "Proficiency";
    if (bonus == B_Cleverness)
        return "Cleverness";
    if (bonus == B_Luck)
        return "Luck";
    if (bonus == B_HealthLimit)
        return "Health Limit";
    if (bonus == B_DailyHealthRecovery)
        return "Daily Health Recovery";
    if (bonus == B_StressResistance)
        return "Stress Resistance";
    if (bonus == B_StressLimit)
        return "Stress Limit";
    if (bonus == B_StressBorder)
        return "Stress Border";
    if (bonus == B_DailyStressRecovery)
        return "Daily Stress Recovery";
    if (bonus == B_Salary)
        return "Salary";
    if (bonus == B_DailyFoodConsumption)
        return "Daily Food Consumption";
    qWarning()<<"enum->QString conversion failed for "<<bonus;
}

int Equipment::combatEffectivenessBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_CombatEffectiveness, 0);
}

int Equipment::proficiencyBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_Proficiency, 0);
}

int Equipment::clevernessBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_Cleverness, 0);
}

float Equipment::luckBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_Luck, 0);
}

int Equipment::healthLimitBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_HealthLimit, 0);
}

int Equipment::dailyHealthRecoveryBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_DailyHealthRecovery, 0);
}

float Equipment::stressResistanceBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_StressResistance, 0);
}

int Equipment::stressLimitBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_StressLimit, 0);
}

int Equipment::stressBorderBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_StressBorder, 0);
}

int Equipment::dailyStressRecoveryBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_DailyStressRecovery, 0);
}

int Equipment::salaryBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_Salary, 0);
}

int Equipment::dailyFoodConsumptionBonus() const noexcept
{
    return m_bonuses.value(EquipmentEnums::B_DailyFoodConsumption, 0);
}

unsigned Equipment::amountOfBonuses() const noexcept
{
    unsigned a=0;
    for (int i=0;i<static_cast<int>(EquipmentEnums::B_END);++i)
        if (m_bonuses.contains(static_cast<EquipmentEnums::Bonus>(i)))
            ++a;
    return a;
}

QString Equipment::bonusAtPosName(unsigned pos) const noexcept
{
    for (auto b : m_bonuses.keys())
    {
        if (pos)
            --pos;
        else
            return EquipmentEnums::fromBonusEnumToQString(b);
    }
}

float Equipment::bonusAtPosValue(unsigned pos) const noexcept
{
    for (auto b : m_bonuses.keys())
    {
        if (pos)
            --pos;
        else
            return m_bonuses.value(b);
    }
}

unsigned Equipment::buyingAetheriteCost() const noexcept
{
    switch (m_tier) {
    case 1:
        return 150;
    case 2:
        return 400;
    case 3:
        return 800;
    }
}

unsigned Equipment::maintenanceEnergyCost() const noexcept
{
    if (m_type == EquipmentEnums::T_Armor)
    {
        switch (m_tier) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 4;
        }
    }
    else
    {
        switch (m_tier) {
        case 1:
            return 1;
        case 2:
        case 3:
            return 2;
        }
    }
}

unsigned Equipment::maintenanceBuildingMaterialsCost() const noexcept
{
    if (m_type == EquipmentEnums::T_Armor)
    {
        switch (m_tier) {
        case 1:
        case 2:
        case 3:
            return 1;
        }
    }
    else
    {
        switch (m_tier) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        }
    }
}

QString Equipment::pathToArt() const noexcept
{
    QString r = "qrc:/graphics/Equipment/";
    if (m_type == EquipmentEnums::T_Armor)
        r+="Armor";
    else
        r+="WeaponTool";
    r+="/Tier_";
    r+=QString::number(m_tier);
    r+=Global::alterNormalTextToInternal(m_name);
    r+=".png";
    return r;
}

Equipment::Equipment() noexcept
    : m_type(EquipmentEnums::T_WeaponTool), m_tier(1)
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
    if (tier>=1)
        m_tier = tier;
}

void Equipment::setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_CombatEffectiveness,combatEffectivenessBonus);
}

void Equipment::setProficiencyBonus(int proficiencyBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_Proficiency,proficiencyBonus);
}

void Equipment::setClevernessBonus(int clevernessBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_Cleverness,clevernessBonus);
}

void Equipment::setLuckBonus(float luckBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_Luck,luckBonus);
}

void Equipment::setHealthLimitBonus(int healthLimitBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_HealthLimit,healthLimitBonus);
}

void Equipment::setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_DailyHealthRecovery,dailyHealthRecoveryBonus);
}

void Equipment::setStressResistanceBonus(float stressResistanceBonus) noexcept
{
   m_bonuses.insert(EquipmentEnums::B_StressResistance,stressResistanceBonus);
}

void Equipment::setStressLimitBonus(int stressLimitBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_StressLimit,stressLimitBonus);
}

void Equipment::setStressBorderBonus(int stressBorderBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_StressBorder,stressBorderBonus);
}

void Equipment::setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_DailyStressRecovery,dailyStressRecoveryBonus);
}

void Equipment::setSalaryBonus(int salaryBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_Salary,salaryBonus);
}

void Equipment::setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept
{
    m_bonuses.insert(EquipmentEnums::B_DailyFoodConsumption,dailyFoodConsumptionBonus);
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
    Equipment *ret;
    ret=m_equipment;
    m_equipment=new Equipment();
    return ret;
}

void EquipmentBuilder::resetEquiment() noexcept
{
    delete m_equipment;
    m_equipment=new Equipment();
}

Equipment *EquipmentBuilder::copyEquipment(const Equipment *equipment) noexcept
{
    Equipment *r=new Equipment;
    r->m_name=equipment->m_name;
    r->m_type=equipment->m_type;
    r->m_tier=equipment->m_tier;
    r->m_categories=equipment->m_categories;
    r->m_bonuses=equipment->m_bonuses;
    return r;
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

void EquipmentBuilder::addCategory(EquipmentEnums::Category cat) noexcept
{
    m_equipment->m_categories+=cat;
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

void EquipmentBuilder::setHealthLimitBonus(int healthLimitBonus) noexcept
{
    m_equipment->setHealthLimitBonus(healthLimitBonus);
}

void EquipmentBuilder::setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept
{
    m_equipment->setDailyHealthRecoveryBonus(dailyHealthRecoveryBonus);
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
