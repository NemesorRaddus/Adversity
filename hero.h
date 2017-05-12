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
        DR_StressLimitAchieved,
        DR_END
    };

    static Nature fromQStringToNatureEnum(const QString &nature) noexcept;
    static QString fromNatureEnumToQString(Nature nature) noexcept;

    static StressBorderEffect fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept;
    static QString fromStressBorderEffectEnumToQString(StressBorderEffect stressBorderEffect) noexcept;

    static Attribute fromQStringToAttributeEnum(const QString &attribute) noexcept;
    static QString fromAttributeEnumToQString(Attribute attribute) noexcept;
};

struct HeroStressBorderEffect
{
    HeroStressBorderEffect() noexcept
        : effectName(HeroEnums::SBE_None) {}
    HeroStressBorderEffect(HeroEnums::StressBorderEffect effectName_, const QVector <float> &effectParams_) noexcept
        : effectName(effectName_), effectParams(effectParams_) {}

    HeroEnums::StressBorderEffect effectName;
    QVector <float> effectParams;

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;
};

QDataStream &operator<<(QDataStream &stream, const HeroStressBorderEffect &effect) noexcept;
QDataStream &operator>>(QDataStream &stream, HeroStressBorderEffect &effect) noexcept;

class Hero : public QObject
{
    Q_OBJECT

    friend class HeroBuilder;
public:
    unsigned id() const noexcept
    {
        return m_id;
    }
    Q_INVOKABLE const QString &name() const noexcept
    {
        return m_name;
    }

    Q_INVOKABLE int combatEffectiveness() const noexcept
    {
        return m_combatEffectiveness;
    }
    Q_INVOKABLE int proficiency() const noexcept
    {
        return m_proficiency;
    }
    Q_INVOKABLE int cleverness() const noexcept
    {
        return m_cleverness;
    }

    Q_INVOKABLE float luck() const noexcept
    {
        return m_luck;
    }

    Q_INVOKABLE int health() const noexcept
    {
        return m_health;
    }
    Q_INVOKABLE int healthLimit() const noexcept
    {
        return m_healthLimit;
    }
    Q_INVOKABLE int dailyHealthRecovery() const noexcept
    {
        return m_dailyHealthRecovery;
    }

    Q_INVOKABLE int stress() const noexcept
    {
        return m_stress;
    }
    Q_INVOKABLE float stressResistance() const noexcept
    {
        return m_stressResistance;
    }
    Q_INVOKABLE int stressLimit() const noexcept
    {
        return m_stressLimit;
    }
    Q_INVOKABLE int stressBorder() const noexcept
    {
        return m_stressBorder;
    }
    const HeroStressBorderEffect &stressBorderEffect() const noexcept
    {
        return m_stressBorderEffect;
    }
    Q_INVOKABLE QString stressBorderEffectNameString() const noexcept
    {
        return HeroEnums::fromStressBorderEffectEnumToQString(m_stressBorderEffect.effectName);
    }
    Q_INVOKABLE int dailyStressRecovery() const noexcept
    {
        return m_dailyStressRecovery;
    }

    Q_INVOKABLE int salary() const noexcept
    {
        return m_salary;
    }

    Q_INVOKABLE int dailyFoodConsumption() const noexcept
    {
        return m_dailyFoodConsumption;
    }

    HeroEnums::Nature nature() const noexcept
    {
        return m_nature;
    }
    Q_INVOKABLE QString natureString() const noexcept
    {
        return HeroEnums::fromNatureEnumToQString(m_nature);
    }

    void setCombatEffectiveness(int combatEffectiveness) noexcept;
    void setProficiency(int proficiency) noexcept;
    void setCleverness(int cleverness) noexcept;

    void setLuck(float luck) noexcept;

    void setHealth(int health) noexcept;
    void setHealthLimit(int healthLimit) noexcept;
    void setDailyHealthRecovery(int dailyHealthRecovery) noexcept;

    void setStress(int stress) noexcept;//use that when loading from save
    void increaseStress(int amount) noexcept;//use that
    void decreaseStress(int amount) noexcept;//and that when changing value during playtime
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
    Q_INVOKABLE int amountOfWeaponToolSlots() const noexcept
    {
        return m_amountOfWeaponToolSlots;
    }

    void equipArmor(Equipment *armor) noexcept;
    void unequipArmor() noexcept;
    void equipWeaponTool(Equipment *weaponTool, int slot) noexcept;
    void unequipWeaponTool(int slot) noexcept;

    Q_INVOKABLE bool isDead() const noexcept
    {
        return m_isDead;
    }
    void setIsDead(bool isDead) noexcept;

    Q_INVOKABLE int noSignalDaysRemaining() const noexcept
    {
        return m_noSignalDaysRemaining;
    }
    void setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept;

    Q_INVOKABLE int carriedEnergy() const noexcept
    {
        return m_carriedEnergy;
    }
    void setCarriedEnergy(int carriedEnergy) noexcept;

    Q_INVOKABLE int carriedFoodSupplies() const noexcept
    {
        return m_carriedFoodSupplies;
    }
    void setCarriedFoodSupplies(int carriedFoodSupplies) noexcept;

    Q_INVOKABLE int carriedBuildingMaterials() const noexcept
    {
        return m_carriedBuildingMaterials;
    }
    void setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept;

    Q_INVOKABLE int carriedAetheriteOre() const noexcept
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

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    Hero() noexcept;

    void setID(unsigned id) noexcept;
    void setName(const QString &name) noexcept;
    void setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept;
    void setNature(HeroEnums::Nature nature) noexcept;

    void activateStressBorderEffect() noexcept;
    void deactivateStressBorderEffect() noexcept;

    void die(HeroEnums::DyingReason reason = HeroEnums::DR_NoReason) noexcept;

    void setArmor(Equipment *armor) noexcept;
    void setWeaponTool(Equipment *weaponTool, int slot) noexcept;
    void applyArmorEffect(Equipment *armor) noexcept;
    void unapplyArmorEffect(Equipment *armor) noexcept;
    void applyWeaponToolEffect(Equipment *weaponTool) noexcept;
    void unapplyWeaponToolEffect(Equipment *weaponTool) noexcept;

    unsigned m_id;
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

QDataStream &operator<<(QDataStream &stream, const Hero &hero) noexcept;
QDataStream &operator>>(QDataStream &stream, Hero &hero) noexcept;

class HeroBuilder
{
public:
    HeroBuilder() noexcept;
    ~HeroBuilder() noexcept;

    Hero *getHero() noexcept;
    void resetHero() noexcept;

    void setID(unsigned id) noexcept
    {
        m_hero->setID(id);
    }
    void setName(const QString &name) noexcept
    {
        m_hero->setName(name);
    }

    void setCombatEffectiveness(int combatEffectiveness) noexcept
    {
        m_hero->setCombatEffectiveness(combatEffectiveness);
    }
    void setProficiency(int proficiency) noexcept
    {
        m_hero->setProficiency(proficiency);
    }
    void setCleverness(int cleverness) noexcept
    {
        m_hero->setCleverness(cleverness);
    }

    void setLuck(float luck) noexcept
    {
        m_hero->setLuck(luck);
    }

    void setHealth(int health) noexcept
    {
        m_hero->setHealth(health);
    }
    void setHealthLimit(int healthLimit) noexcept
    {
        m_hero->setHealthLimit(healthLimit);
    }
    void setDailyHealthRecovery(int dailyHealthRecovery) noexcept
    {
        m_hero->setDailyHealthRecovery(dailyHealthRecovery);
    }

    void setStress(int stress) noexcept
    {
        m_hero->setStress(stress);
    }
    void setStressResistance(float stressResistance) noexcept
    {
        m_hero->setStressResistance(stressResistance);
    }
    void setStressLimit(int stressLimit) noexcept
    {
        m_hero->setStressLimit(stressLimit);
    }
    void setStressBorder(int stressBorder) noexcept
    {
        m_hero->setStressBorder(stressBorder);
    }
    void setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept
    {
        m_hero->setStressBorderEffect(stressBorderEffect);
    }
    void setDailyStressRecovery(int dailyStressRecovery) noexcept
    {
        m_hero->setDailyStressRecovery(dailyStressRecovery);
    }

    void setSalary(int salary) noexcept
    {
        m_hero->setSalary(salary);
    }

    void setDailyFoodConsumption(int dailyFoodConsumption) noexcept
    {
        m_hero->setDailyFoodConsumption(dailyFoodConsumption);
    }

private:
    Hero *m_hero;
};

class HeroesContainer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Hero* preparedHero MEMBER m_preparedHero)

public:
    HeroesContainer() noexcept;
    ~HeroesContainer() noexcept;

    Q_INVOKABLE bool prepareHeroAt(unsigned id) noexcept;
    unsigned availableID() const noexcept;
    void addHero(Hero *hero) noexcept;
    void removeHero(unsigned id) noexcept;
    const QVector <Hero *> &heroes() noexcept
    {
        return m_heroes;
    }

private:
    int findHero(unsigned id) const noexcept;

    QVector <Hero *> m_heroes;
    Hero *m_preparedHero;
};

#endif // HERO_H
