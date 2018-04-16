#include "enums.h"

#include <QString>

#include "logging/loggersprovider.h"

EquipmentEnums::Type EquipmentEnums::fromQStringToTypeEnum(const QString &type) noexcept
{
    if (type == "Armor")
        return T_Armor;
    if (type == "Weapon/Tool")
        return T_WeaponTool;
    LoggersProvider::mainLogger()->warn("QString->Equipment::Type enum conversion failed for {}",type.toStdString());
}

QString EquipmentEnums::fromTypeEnumToQString(EquipmentEnums::Type type) noexcept
{
    if (type == T_Armor)
        return "Armor";
    if (type == T_WeaponTool)
        return "Weapon/Tool";
    LoggersProvider::mainLogger()->warn("Equipment::Type enum->QString conversion failed for {}",static_cast<unsigned>(type));
}

EquipmentEnums::Category EquipmentEnums::fromQStringToCategoryEnum(const QString &category) noexcept
{
    if (category == "Biohazard Protection")
        return C_BiohazardProtection;
    if (category == "Climbing")
        return C_Climbing;
    if (category == "Light Source")
        return C_LightSource;
    LoggersProvider::mainLogger()->warn("QString->Equipment::Category enum conversion failed for {}",category.toStdString());
}

QString EquipmentEnums::fromCategoryEnumToQString(EquipmentEnums::Category category) noexcept
{
    if (category == C_BiohazardProtection)
        return "Biohazard Protection";
    if (category == C_Climbing)
        return "Climbing";
    if (category == C_LightSource)
        return "Light Source";
    LoggersProvider::mainLogger()->warn("Equipment::Category enum->QString conversion failed for {}",static_cast<unsigned>(category));
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
    LoggersProvider::mainLogger()->warn("QString->Equipment::Bonus enum conversion failed for {}",bonus.toStdString());
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
    LoggersProvider::mainLogger()->warn("Equipment::Bonus enum->QString conversion failed for {}",static_cast<unsigned>(bonus));
}
