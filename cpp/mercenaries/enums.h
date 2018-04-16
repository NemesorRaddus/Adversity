#pragma once

class QString;

namespace MercenaryEnums
{
    enum Nature
    {
        N_Active,
        N_Convivial,
        N_Religious,
        N_Recluse,
        N_END
    };
    enum StressBorderEffect
    {
        SBE_None,
        SBE_Faint,
        SBE_Desertion,
        SBE_Fear,
        SBE_Rage,
        SBE_FanaticWrath,
        SBE_Paranoia,
        SBE_Bravery,
        SBE_Hopeless,
        SBE_Confusion,
        SBE_Masochism,
        SBE_Abandonce,
        SBE_Restive,
        SBE_Madness,
        SBE_Restlessness,
        SBE_Stupor,
        SBE_Consciousness,
        SBE_Caution,
        SBE_Awareness,
        SBE_StoneSkin,
        SBE_Multitasking,
        SBE_Equilibrium,
        SBE_StressResistant,
        SBE_TheLuckyOne,
        SBE_Doombringer,
        SBE_Excellence,
        SBE_Absolute,
        SBE_END
    };
    enum Attribute
    {
        A_CombatEffectiveness,
        A_Proficiency,
        A_Cleverness,
        A_Luck,
        A_Health,
        A_HealthLimit,
        A_DailyHealthRecovery,
        A_Stress,
        A_StressResistance,
        A_StressLimit,
        A_StressBorder,
        A_DailyStressRecovery,
        A_Salary,
        A_DailyFoodConsumption,
        A_END
    };
    enum CurrentActivity
    {
        CA_Idle,
        CA_OnMission,
        CA_InHospital,
        CA_OnTrainingGround,
        CA_InGym,
        CA_InLaboratory,
        CA_InPlayingField,
        CA_InBar,
        CA_InShrine,
        CA_InSeclusion,
        CA_Arriving,
        CA_END
    };
    enum Profession
    {
        P_BountyHunter,
        P_Gunzerker,
        P_PriestOfTheUniverse,
        P_PriestessOfTheUniverse,
        P_BattleDroid,
        P_SpaceNomad,
		P_Archaeologist,
        P_Criminal,
        P_Cyborg,
        P_Specialist,
        P_Doomsayer,
        P_END
    };

    Nature fromQStringToNatureEnum(const QString &nature) noexcept;
    QString fromNatureEnumToQString(Nature nature) noexcept;

    StressBorderEffect fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept;
    QString fromStressBorderEffectEnumToQString(StressBorderEffect stressBorderEffect) noexcept;

    Attribute fromQStringToAttributeEnum(const QString &attribute) noexcept;
    QString fromAttributeEnumToQString(Attribute attribute) noexcept;

    CurrentActivity fromQStringToCurrentActivityEnum(const QString &currentActivity) noexcept;
    QString fromCurrentActivityEnumToQString(CurrentActivity currentActivity) noexcept;

    Profession fromQStringToProfessionEnum(const QString &profession) noexcept;
    QString fromProfessionEnumToQString(Profession profession) noexcept;
}
