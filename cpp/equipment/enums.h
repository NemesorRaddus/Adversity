#pragma once

class QString;

namespace EquipmentEnums
{
    enum Type
    {
        T_WeaponTool,
        T_Armor
    };
    enum Category
    {
        C_BiohazardProtection,
        C_Climbing,
        C_LightSource,
        C_END
    };
    enum Bonus
    {
        B_CombatEffectiveness,
        B_Proficiency,
        B_Cleverness,
        B_Luck,
        B_HealthLimit,
        B_DailyHealthRecovery,
        B_StressResistance,
        B_StressLimit,
        B_StressBorder,
        B_DailyStressRecovery,
        B_Salary,
        B_DailyFoodConsumption,
        B_END
    };

    Type fromQStringToTypeEnum(const QString &type) noexcept;
    QString fromTypeEnumToQString(Type type) noexcept;

    Category fromQStringToCategoryEnum(const QString &category) noexcept;
    QString fromCategoryEnumToQString(Category category) noexcept;

    Bonus fromQStringToBonusEnum(const QString &bonus) noexcept;
    QString fromBonusEnumToQString(Bonus bonus) noexcept;
}
