#ifndef HERO_H
#define HERO_H

#include <QString>
#include <QVector>

#include "equipment.h"

#include <QDebug>

class Mission;

struct HeroEnums
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
        CA_END
    };
    enum DyingReason
    {
        DR_NoReason,
        DR_AttributeCheckFailed,
        DR_StressBorderAchieved,
        DR_END
    };
};

struct HeroStressBorderEffect
{
    HeroEnums::StressBorderEffect effectName;
    QVector <float> effectParams;
};

class Hero
{
    friend class HeroBuilder;
public:
    const QString &name() const noexcept
    {
        return m_name;
    }
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
    const HeroStressBorderEffect &stressBorderEffect() const noexcept
    {
        return m_stressBorderEffect;
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
    HeroEnums::Nature nature() const noexcept
    {
        return m_nature;
    }

    void setCombatEffectiveness(int combatEffectiveness) noexcept;
    void setProficiency(int proficiency) noexcept;
    void setCleverness(int cleverness) noexcept;
    void setLuck(float luck) noexcept;
    void setHealth(int health) noexcept;
    void setHealthLimit(int healthLimit) noexcept;
    void setDailyHealthRecovery(int dailyHealthRecovery) noexcept;
    void setStress(int stress) noexcept;
    void setStressResistance(float stressResistance) noexcept;
    void setStressLimit(int stressLimit) noexcept;
    void setStressBorder(int stressBorder) noexcept;
    void setDailyStressRecovery(int dailyStressRecovery) noexcept;
    void setSalary(int salary) noexcept;
    void setDailyFoodConsumption(int dailyFoodConsumption) noexcept;

    Equipment *armor() const noexcept
    {
        return m_armor;
    }
    Equipment *weaponTool(int slot) const noexcept
    {
        return m_weaponsTools.value(slot,NULL);
    }
    int amountOfWeaponToolSlots() const noexcept
    {
        return m_amountOfWeaponToolSlots;
    }

    void setArmor(Equipment *armor) noexcept;
    void setWeaponTool(Equipment *weaponTool, int slot) noexcept;

    bool isDead() const noexcept
    {
        return m_isDead;
    }
    void setIsDead(bool isDead) noexcept;

    int noSignalDaysRemaining() const noexcept
    {
        return m_noSignalDaysRemaining;
    }
    void setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept;

    int carriedEnergy() const noexcept
    {
        return m_carriedEnergy;
    }
    void setCarriedEnergy(int carriedEnergy) noexcept;

    int carriedFoodSupplies() const noexcept
    {
        return m_carriedFoodSupplies;
    }
    void setCarriedFoodSupplies(int carriedFoodSupplies) noexcept;

    int carriedBuildingMaterials() const noexcept
    {
        return m_carriedBuildingMaterials;
    }
    void setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept;

    int carriedAetheriteOre() const noexcept
    {
        return m_carriedAetheriteOre;
    }
    void setCarriedAetheriteOre(int carriedAetheriteOre) noexcept;

    Mission *assignedMission() noexcept
    {
        return m_assignedMission;
    }
    void assignMission(Mission *mission) noexcept;

    HeroEnums::CurrentActivity currentActivity() const noexcept
    {
        return m_currentActivity;
    }
    void setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept;

private:
    Hero() noexcept;

    void setName(const QString &name) noexcept;
    void setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept;
    void setNature(HeroEnums::Nature nature) noexcept;

    void activateStressBorderEffect() noexcept;
    void deactivateStressBorderEffect() noexcept;

    void die(HeroEnums::DyingReason reason = HeroEnums::DR_NoReason) noexcept;

    QString m_name;

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
    HeroStressBorderEffect m_stressBorderEffect;
    int m_dailyStressRecovery;
    int m_salary;
    int m_dailyFoodConsumption;
    HeroEnums::Nature m_nature;

    Equipment *m_armor;
    QVector <Equipment *> m_weaponsTools;
    const int m_amountOfWeaponToolSlots = 2;

    bool m_isDead;
    bool m_isStressBorderEffectActive;

    int m_noSignalDaysRemaining;

    int m_carriedEnergy;
    int m_carriedFoodSupplies;
    int m_carriedBuildingMaterials;
    int m_carriedAetheriteOre;

    Mission *m_assignedMission;
    HeroEnums::CurrentActivity m_currentActivity;
};

class HeroBuilder
{
public:
    Hero *getHero() noexcept;
    void resetHero() noexcept;

    void setName(const QString &name) noexcept;
    void setCombatEffectiveness(int combatEffectiveness) noexcept;
    void setProficiency(int proficiency) noexcept;
    void setCleverness(int cleverness) noexcept;
    void setLuck(float luck) noexcept;
    void setHealth(int health) noexcept;
    void setHealthLimit(int healthLimit) noexcept;
    void setDailyHealthRecovery(int dailyHealthRecovery) noexcept;
    void setStress(int stress) noexcept;
    void setStressResistance(float stressResistance) noexcept;
    void setStressLimit(int stressLimit) noexcept;
    void setStressBorder(int stressBorder) noexcept;
    void setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept;
    void setDailyStressRecovery(int dailyStressRecovery) noexcept;
    void setSalary(int salary) noexcept;
    void setDailyFoodConsumption(int dailyFoodConsumption) noexcept;

private:
    Hero *m_hero;
};

#endif // HERO_H
