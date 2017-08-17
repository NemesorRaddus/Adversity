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
        P_Archeologist,
        P_Criminal,
        P_Cyborg,
        P_Specialist,
        P_Doomsayer,
        P_END
    };

    static Nature fromQStringToNatureEnum(const QString &nature) noexcept;
    static QString fromNatureEnumToQString(Nature nature) noexcept;

    static StressBorderEffect fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept;
    static QString fromStressBorderEffectEnumToQString(StressBorderEffect stressBorderEffect) noexcept;

    static Attribute fromQStringToAttributeEnum(const QString &attribute) noexcept;
    static QString fromAttributeEnumToQString(Attribute attribute) noexcept;

    static CurrentActivity fromQStringToCurrentActivityEnum(const QString &currentActivity) noexcept;
    static QString fromCurrentActivityEnumToQString(CurrentActivity currentActivity) noexcept;

    static Profession fromQStringToProfessionEnum(const QString &profession) noexcept;
    static QString fromProfessionEnumToQString(Profession profession) noexcept;
};

struct HeroStressBorderEffect
{
    HeroStressBorderEffect() noexcept
        : effectName(HeroEnums::SBE_None) {}
    HeroStressBorderEffect(HeroEnums::StressBorderEffect effectName_) noexcept
        : effectName(effectName_) {}

    HeroEnums::StressBorderEffect effectName;

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;
};

QDataStream &operator<<(QDataStream &stream, const HeroStressBorderEffect &effect) noexcept;
QDataStream &operator>>(QDataStream &stream, HeroStressBorderEffect &effect) noexcept;

struct HeroAttributesSet
{
    HeroAttributesSet() noexcept
        : combatEffectiveness(0), proficiency(0), cleverness(0), luck(0), health(1), healthLimit(1), dailyHealthRecovery(0), stress(0), stressResistance(0), stressLimit(1), stressBorder(1), dailyStressRecovery(0), salary(0), dailyFoodConsumption(0) {}

    int combatEffectiveness;
    int proficiency;
    int cleverness;

    float luck;

    int health;
    int healthLimit;
    int dailyHealthRecovery;

    int stress;
    float stressResistance;
    int stressLimit;
    int stressBorder;
    int dailyStressRecovery;

    int salary;
    int dailyFoodConsumption;
};

QDataStream &operator<<(QDataStream &stream, const HeroAttributesSet &attrs) noexcept;
QDataStream &operator>>(QDataStream &stream, HeroAttributesSet &attrs) noexcept;

struct AttributeModification;

class Base;

class Hero : public QObject
{
    Q_OBJECT

    friend class HeroBuilder;
    friend class KillHeroEventResult;
    friend class QDataStream;
    friend class H4X;

public:
    Q_INVOKABLE QString name() const noexcept
    {
        return m_name;
    }

    Q_INVOKABLE int combatEffectiveness() const noexcept
    {
        return m_currentAttributesValues.combatEffectiveness;
    }
    Q_INVOKABLE int proficiency() const noexcept
    {
        return m_currentAttributesValues.proficiency;
    }
    Q_INVOKABLE int cleverness() const noexcept
    {
        return m_currentAttributesValues.cleverness;
    }

    Q_INVOKABLE float luck() const noexcept
    {
        return m_currentAttributesValues.luck;
    }

    Q_INVOKABLE int health() const noexcept
    {
        return m_currentAttributesValues.health;
    }
    Q_INVOKABLE int healthLimit() const noexcept
    {
        return m_currentAttributesValues.healthLimit;
    }
    Q_INVOKABLE int dailyHealthRecovery() const noexcept
    {
        return m_currentAttributesValues.dailyHealthRecovery;
    }

    Q_INVOKABLE int stress() const noexcept
    {
        return m_currentAttributesValues.stress;
    }
    Q_INVOKABLE float stressResistance() const noexcept
    {
        return m_currentAttributesValues.stressResistance;
    }
    Q_INVOKABLE int stressLimit() const noexcept
    {
        return m_baseAttributesValues.stressLimit!=-1 ? m_currentAttributesValues.stressLimit : -1;
    }
    Q_INVOKABLE int stressBorder() const noexcept
    {
        return m_currentAttributesValues.stressBorder;
    }

    const QVector <HeroStressBorderEffect> &stressBorderEffects() const noexcept
    {
        return m_stressBorderEffects;
    }
    const HeroStressBorderEffect *currentSBE() const noexcept;
    Q_INVOKABLE int amountOfSBEs() const noexcept
    {
        return m_stressBorderEffects.size();
    }
    Q_INVOKABLE QString currentStressBorderEffectNameString() const noexcept;
    Q_INVOKABLE int indexOfCurrentSBE() const noexcept
    {
        return m_indexOfCurrentSBE;
    }
    Q_INVOKABLE bool isStressBorderEffectActive() const noexcept
    {
        return m_indexOfCurrentSBE!=-1;
    }
    Q_INVOKABLE int dailyStressRecovery() const noexcept
    {
        return m_currentAttributesValues.dailyStressRecovery;
    }

    QVector <QPair <HeroStressBorderEffect, unsigned> > diverseSBEs() const noexcept;//with amount of copies
    Q_INVOKABLE int amountOfDiverseSBEs() const noexcept;
    Q_INVOKABLE QString nameOfSBESummed(unsigned index) const noexcept;
    Q_INVOKABLE float chanceOfSBESummed(unsigned index) const noexcept;

    Q_INVOKABLE int salary() const noexcept
    {
        return m_currentAttributesValues.salary;
    }

    Q_INVOKABLE int dailyFoodConsumption() const noexcept
    {
        return m_currentAttributesValues.dailyFoodConsumption;
    }

    HeroEnums::Nature nature() const noexcept
    {
        return m_nature;
    }
    Q_INVOKABLE QString natureString() const noexcept;

    HeroEnums::Profession profession() const noexcept
    {
        return m_profession;
    }
    Q_INVOKABLE QString professionString() const noexcept;

    Q_INVOKABLE int baseHealthLimit() const noexcept
    {
        return m_baseAttributesValues.healthLimit;
    }
    Q_INVOKABLE int baseStressLimit() const noexcept
    {
        return m_baseAttributesValues.stressLimit;
    }
    Q_INVOKABLE float baseStressResistance() const noexcept
    {
        return m_baseAttributesValues.stressResistance;
    }
    Q_INVOKABLE int baseCombatEffectiveness() const noexcept
    {
        return m_baseAttributesValues.combatEffectiveness;
    }
    Q_INVOKABLE int baseProficiency() const noexcept
    {
        return m_baseAttributesValues.proficiency;
    }
    Q_INVOKABLE int baseCleverness() const noexcept
    {
        return m_baseAttributesValues.cleverness;
    }
    Q_INVOKABLE int baseDailyHealthRecovery() const noexcept
    {
        return m_baseAttributesValues.dailyHealthRecovery;
    }
    Q_INVOKABLE int baseDailyStressRecovery() const noexcept
    {
        return m_baseAttributesValues.dailyStressRecovery;
    }
    Q_INVOKABLE int baseDailyFoodConsumption() const noexcept
    {
        return m_baseAttributesValues.dailyFoodConsumption;
    }
    Q_INVOKABLE int baseSalary() const noexcept
    {
        return m_baseAttributesValues.salary;
    }

    Q_INVOKABLE bool canTrainCombatEffectiveness() const noexcept;
    Q_INVOKABLE bool canTrainProficiency() const noexcept;
    Q_INVOKABLE bool canTrainCleverness() const noexcept;

    void trainCombatEffectiveness() noexcept;
    void trainProficiency() noexcept;
    void trainCleverness() noexcept;

    void changeCombatEffectiveness(int amount) noexcept;//change by amount so increase or decrease by amount, not set amount!
    void changeProficiency(int amount) noexcept;
    void changeCleverness(int amount) noexcept;

    void changeLuck(float amount) noexcept;

    void changeHealth(int amount) noexcept;
    void changeHealthLimit(int amount) noexcept;
    void changeDailyHealthRecovery(int amount) noexcept;

    void increaseStress(unsigned amount) noexcept;//use that
    void decreaseStress(unsigned amount) noexcept;//and that when changing value during playtime
    void changeStressResistance(float amount) noexcept;
    void changeStressLimit(int amount) noexcept;
    void changeStressBorder(int amount) noexcept;
    void changeDailyStressRecovery(int amount) noexcept;
    Q_INVOKABLE bool isImmuneToStress() const noexcept
    {
        return m_baseAttributesValues.stressLimit==-1;
    }

    void changeSalary(int amount) noexcept;

    void changeDailyFoodConsumption(int amount) noexcept;

    void setDailyHealthRecoveryBuildingBonus(int bonus) noexcept;
    void setDailyStressRecoveryBuildingBonus(int bonus) noexcept;

    void addAttributeModification(AttributeModification *mod) noexcept;
    void decrementModificationsDuration() noexcept;

    Equipment *armor() const noexcept
    {
        return m_armor;
    }
    Equipment *weaponTool(int slot) const noexcept;
    Q_INVOKABLE int amountOfWeaponToolSlots() const noexcept
    {
        return m_amountOfWeaponToolSlots;
    }

    void equipArmor(Equipment *armor) noexcept;
    void unequipArmor() noexcept;
    void equipWeaponTool(Equipment *weaponTool, int slot) noexcept;
    void unequipWeaponTool(int slot) noexcept;

    inline bool isEquipmentActive() const noexcept
    {
        return m_isEquipmentActive;
    }

    QVector <EquipmentEnums::Category> currentEquipmentCategories() const noexcept;
    bool hasEquipmentFromCategory(EquipmentEnums::Category cat) const noexcept;

    void addCarriedEquipment(Equipment *eq) noexcept;
    QVector <Equipment *> carriedEquipment() const noexcept;
    void clearCarriedEquipment() noexcept;

    Q_INVOKABLE bool isDead() const noexcept
    {
        return m_isDead;
    }
    void setIsDead(bool isDead) noexcept
    {
        m_isDead = isDead;
    }

    Q_INVOKABLE int noSignalDaysRemaining() const noexcept
    {
        return m_noSignalDaysRemaining;
    }
    void setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept
    {
        m_noSignalDaysRemaining = noSignalDaysRemaining;
    }
    Q_INVOKABLE bool isCommunicationAvailable() const noexcept
    {
        return m_noSignalDaysRemaining==0;
    }

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
    Q_INVOKABLE QString currentActivityString() const noexcept;
    void setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept;

    void dismiss(unsigned banDays) noexcept;

    void handleNewDay(Base *base) noexcept;
    void handleNewWeek(Base *base) noexcept;

signals:
    void died(QString name);
    void ranAway(QString name, unsigned daysOfDoStBan);

private:
    Hero() noexcept;

    void setName(const QString &name) noexcept
    {
        m_name=name;
    }
    void setStressBorderEffects(const QVector <HeroStressBorderEffect> &stressBorderEffects) noexcept
    {
        m_stressBorderEffects=stressBorderEffects;
    }
    void setNature(HeroEnums::Nature nature) noexcept
    {
        m_nature=nature;
    }
    void setProfession(HeroEnums::Profession profession) noexcept
    {
        m_profession=profession;
    }

    void activateStressBorderEffect() noexcept;
    void deactivateStressBorderEffect() noexcept;

    void die() noexcept;
    void setArmor(Equipment *armor) noexcept;
    void setWeaponTool(Equipment *weaponTool, int slot) noexcept;

    void applyEquipmentEffect() noexcept;
    void unapplyEquipmentEffect() noexcept
    {
        applyEquipmentEffect();
    }

    void calculateCurrentAttributeValue(HeroEnums::Attribute attributeName) noexcept;//shouldn't be used in most situations (big NO when calc. CE, PR or CL)
    void calculateCurrentAttributeValues() noexcept;//use this instead

    void sumEquipmentCategories() noexcept;

    void setAttributeValue(HeroEnums::Attribute attrName, float val) noexcept;//only for H4X

    void activateEquipment() noexcept;
    void deactivateEquipment() noexcept;

    void handleSBEAtDayEnd() noexcept;
    void handleEquipmentCosts(Base *base) noexcept;
    void handleHunger(Base *base) noexcept;

    void handleSalary(Base *base) noexcept;

    QString m_name;

    HeroAttributesSet m_baseAttributesValues;
    HeroAttributesSet m_currentAttributesValues;//including eq bonuses, SBE impact

    int m_stockCE;
    int m_stockPR;
    int m_stockCL;

    QVector <HeroStressBorderEffect> m_stressBorderEffects;
    HeroEnums::Nature m_nature;
    HeroEnums::Profession m_profession;

    Equipment *m_armor;
    QVector <Equipment *> m_weaponsTools;
    const int m_amountOfWeaponToolSlots = 2;
    QVector <EquipmentEnums::Category> m_currentEquipmentCategories;
    QVector <Equipment *> m_carriedEquipment;
    bool m_isEquipmentActive;

    int m_dhrBuildingBonus;
    int m_dsrBuildingBonus;

    QVector <AttributeModification *> m_attributeModifications;

    bool m_isDead;
    int m_indexOfCurrentSBE;

    int m_noSignalDaysRemaining;//if -1, it doesn't end on its own after some time

    int m_carriedEnergy;
    int m_carriedFoodSupplies;
    int m_carriedBuildingMaterials;
    int m_carriedAetheriteOre;

    int m_noSalaryWeeks;

    Mission *m_assignedMission;
    HeroEnums::CurrentActivity m_currentActivity;
};

struct HeroDataHelper
{
    HeroDataHelper()
        : stockCE(0), stockPR(0), stockCL(0), nature(HeroEnums::N_Active), profession(HeroEnums::P_Archeologist), isEquipmentActive(true), dhrBuildingBonus(0), dsrBuildingBonus(0), isDead(false), indexOfCurrentSBE(-1), noSignalDaysRemaining(0), carriedEnergy(0), carriedFoodSupplies(0), carriedBuildingMaterials(0), carriedAetheriteOre(0), noSalaryWeeks(0), assignedMission(nullptr), currentActivity(HeroEnums::CA_Idle) {}

    QString name;

    HeroAttributesSet baseAttributesValues;
    HeroAttributesSet currentAttributesValues;

    int stockCE;
    int stockPR;
    int stockCL;

    QVector <HeroStressBorderEffect> stressBorderEffects;
    HeroEnums::Nature nature;
    HeroEnums::Profession profession;

    QString armor;
    QVector <QString> weaponsTools;
    QVector <EquipmentEnums::Category> equipmentCategories;
    QVector <QString> carriedEquipment;
    bool isEquipmentActive;

    int dhrBuildingBonus;
    int dsrBuildingBonus;

    bool isDead;
    int indexOfCurrentSBE;

    int noSignalDaysRemaining;

    int carriedEnergy;
    int carriedFoodSupplies;
    int carriedBuildingMaterials;
    int carriedAetheriteOre;

    int noSalaryWeeks;

    Mission *assignedMission;//TODO missions
    HeroEnums::CurrentActivity currentActivity;
};

QDataStream &operator<<(QDataStream &stream, const HeroDataHelper &hero) noexcept;
QDataStream &operator>>(QDataStream &stream, HeroDataHelper &hero) noexcept;

class HeroBuilder
{
public:
    HeroBuilder() noexcept;
    ~HeroBuilder() noexcept;

    Hero *getHero() noexcept;

    static Hero *qobjectifyHeroData(const HeroDataHelper &hero) noexcept;
    static HeroDataHelper deqobjectifyHero(Hero *hero) noexcept;

    void resetHero() noexcept;

    void setName(const QString &name) noexcept
    {
        m_hero->setName(name);
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
    void setStressBorderEffects(const QVector <HeroStressBorderEffect> &stressBorderEffects) noexcept
    {
        m_hero->setStressBorderEffects(stressBorderEffects);
    }
    void setDailyStressRecovery(int dailyStressRecovery) noexcept;

    void setSalary(int salary) noexcept;

    void setDailyFoodConsumption(int dailyFoodConsumption) noexcept;

    void setNature(HeroEnums::Nature nature) noexcept
    {
        m_hero->m_nature=nature;
    }

    void setProfession(HeroEnums::Profession profession) noexcept
    {
        m_hero->m_profession=profession;
    }

    void setAndEquipArmor(Equipment *armor) noexcept
    {
        m_hero->equipArmor(armor);
    }
    void setAndEquipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept;
    void setCarriedEquipment(const QVector <Equipment *> &eqs) noexcept
    {
        m_hero->m_carriedEquipment=eqs;
    }

    void setIsDead(bool dead) noexcept
    {
        m_hero->m_isDead=dead;
    }
    void setIndexOfCurrentSBE(int index) noexcept
    {
        m_hero->m_indexOfCurrentSBE=index;
    }

    void setNoSignalDaysRemaining(int amount) noexcept
    {
        m_hero->m_noSignalDaysRemaining=amount;
    }

    void setCarriedEnergy(int amount) noexcept;
    void setCarriedFoodSupplies(int amount) noexcept;
    void setCarriedBuildingMaterials(int amount) noexcept;
    void setCarriedAetheriteOre(int amount) noexcept;

    void setNoSalaryWeeks(unsigned amount) noexcept;

    void setAssignedMission(Mission *mission) noexcept
    {
        m_hero->m_assignedMission=mission;
    }
    void setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept
    {
        m_hero->m_currentActivity=activity;
    }

private:
    Hero *m_hero;
};

class HeroesContainer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Hero* preparedHero MEMBER m_preparedHero)

public:
    HeroesContainer(Base *base) noexcept;
    ~HeroesContainer() noexcept;

    Q_INVOKABLE bool prepareHeroAt(unsigned index) noexcept;
    void addHero(Hero *hero) noexcept;
    void removeHero(unsigned index) noexcept;
    const QVector <Hero *> &heroes() noexcept
    {
        return m_heroes;
    }
    Q_INVOKABLE int amountOfHeroes() const noexcept
    {
        return m_heroes.size();
    }
    Q_INVOKABLE int findHero(const QString &name) const noexcept;
    Hero *getHero(unsigned index) noexcept
    {
        return m_heroes.value(index,nullptr);
    }
    void setAmountOfSlots(unsigned amount) noexcept
    {
        m_amountOfSlots=amount;
    }
    Q_INVOKABLE unsigned amountOfSlots() const noexcept
    {
        return m_amountOfSlots;
    }
    bool canAddHero() const noexcept
    {
        return m_heroes.size() < m_amountOfSlots;
    }
    Q_INVOKABLE void dismissHero(const QString &name) noexcept
    {
        addDoStBan(name,m_durationOfBanAfterDismiss);
    }

    void handleNewDay() noexcept;
    void handleNewWeek() noexcept;

public slots:
    void addDoStBan(QString name, unsigned daysAmount) noexcept;
    void addDoStBan(QString name) noexcept;//permanent :c

private:
    void connectHeroToBanSystem(const QString &name) noexcept;
    void disconnectHeroFromBanSystem(const QString &name) noexcept;

    QVector <Hero *> m_heroes;
    Hero *m_preparedHero;
    unsigned m_amountOfSlots;
    const unsigned m_durationOfBanAfterDismiss = 21;
    Base *m_basePtr;
};

#endif // HERO_H
