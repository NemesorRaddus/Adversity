#pragma once

#include <QString>
#include <QVector>

#include "equipment.h"

#include <QDebug>

class Mission;

struct MercenaryEnums
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

struct MercenaryStressBorderEffect
{
    MercenaryStressBorderEffect() noexcept
        : effectName(MercenaryEnums::SBE_None) {}
    MercenaryStressBorderEffect(MercenaryEnums::StressBorderEffect effectName_) noexcept
        : effectName(effectName_) {}

    MercenaryEnums::StressBorderEffect effectName;

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;
};

QDataStream &operator<<(QDataStream &stream, const MercenaryStressBorderEffect &effect) noexcept;
QDataStream &operator>>(QDataStream &stream, MercenaryStressBorderEffect &effect) noexcept;

struct MercenaryAttributesSet
{
    MercenaryAttributesSet() noexcept
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

QDataStream &operator<<(QDataStream &stream, const MercenaryAttributesSet &attrs) noexcept;
QDataStream &operator>>(QDataStream &stream, MercenaryAttributesSet &attrs) noexcept;

struct AttributeModification;

class Base;
class UnifiedReport;

class Mercenary : public QObject
{
    Q_OBJECT

    friend class MercenaryBuilder;
    friend class H4X;

    Q_PROPERTY(Mission* assignedMission MEMBER m_assignedMission)
    Q_PROPERTY(Equipment* preparedArmor MEMBER m_armor)
    Q_PROPERTY(Equipment* preparedWeaponTool MEMBER m_preparedWeaponTool)
    Q_PROPERTY(Equipment* preparedCarriedEquipment MEMBER m_preparedCarriedEquipment)

public:
    Q_INVOKABLE inline QString name() const noexcept
    {
        return m_name;
    }

    Q_INVOKABLE inline int combatEffectiveness() const noexcept
    {
        return m_currentAttributesValues.combatEffectiveness;
    }
    Q_INVOKABLE inline int proficiency() const noexcept
    {
        return m_currentAttributesValues.proficiency;
    }
    Q_INVOKABLE inline int cleverness() const noexcept
    {
        return m_currentAttributesValues.cleverness;
    }

    Q_INVOKABLE inline float luck() const noexcept
    {
        return m_currentAttributesValues.luck;
    }

    Q_INVOKABLE inline int health() const noexcept
    {
        return m_currentAttributesValues.health;
    }
    Q_INVOKABLE inline int healthLimit() const noexcept
    {
        return m_currentAttributesValues.healthLimit;
    }
    Q_INVOKABLE inline int dailyHealthRecovery() const noexcept
    {
        return m_currentAttributesValues.dailyHealthRecovery;
    }

    Q_INVOKABLE inline int stress() const noexcept
    {
        return m_currentAttributesValues.stress;
    }
    Q_INVOKABLE inline float stressResistance() const noexcept
    {
        return m_currentAttributesValues.stressResistance;
    }
    Q_INVOKABLE inline int stressLimit() const noexcept
    {
        return m_baseAttributesValues.stressLimit!=-1 ? m_currentAttributesValues.stressLimit : -1;
    }
    Q_INVOKABLE inline int stressBorder() const noexcept
    {
        return m_currentAttributesValues.stressBorder;
    }

    inline const QVector <MercenaryStressBorderEffect> &stressBorderEffects() const noexcept
    {
        return m_stressBorderEffects;
    }
    const MercenaryStressBorderEffect *currentSBE() const noexcept;
    Q_INVOKABLE int amountOfSBEs() const noexcept
    {
        return m_stressBorderEffects.size();
    }
    Q_INVOKABLE QString currentStressBorderEffectNameString() const noexcept;
    Q_INVOKABLE inline int indexOfCurrentSBE() const noexcept
    {
        return m_indexOfCurrentSBE;
    }
    Q_INVOKABLE inline bool isStressBorderEffectActive() const noexcept
    {
        return m_indexOfCurrentSBE!=-1;
    }
    Q_INVOKABLE inline int dailyStressRecovery() const noexcept
    {
        return m_currentAttributesValues.dailyStressRecovery;
    }

    QVector <QPair <MercenaryStressBorderEffect, unsigned> > diverseSBEs() const noexcept;//with amount of copies
    Q_INVOKABLE int amountOfDiverseSBEs() const noexcept;
    Q_INVOKABLE QString nameOfSBESummed(unsigned index) const noexcept;
    Q_INVOKABLE float chanceOfSBESummed(unsigned index) const noexcept;

    Q_INVOKABLE inline int salary() const noexcept
    {
        return m_currentAttributesValues.salary;
    }

    Q_INVOKABLE inline int dailyFoodConsumption() const noexcept
    {
        return m_currentAttributesValues.dailyFoodConsumption;
    }

    MercenaryEnums::Nature inline nature() const noexcept
    {
        return m_nature;
    }
    Q_INVOKABLE QString natureString() const noexcept;

    MercenaryEnums::Profession inline profession() const noexcept
    {
        return m_profession;
    }
    Q_INVOKABLE QString professionString() const noexcept;

    Q_INVOKABLE inline int baseHealthLimit() const noexcept
    {
        return m_baseAttributesValues.healthLimit;
    }
    Q_INVOKABLE inline int baseStressLimit() const noexcept
    {
        return m_baseAttributesValues.stressLimit;
    }
    Q_INVOKABLE inline float baseStressResistance() const noexcept
    {
        return m_baseAttributesValues.stressResistance;
    }
    Q_INVOKABLE inline int baseCombatEffectiveness() const noexcept
    {
        return m_baseAttributesValues.combatEffectiveness;
    }
    Q_INVOKABLE inline int baseProficiency() const noexcept
    {
        return m_baseAttributesValues.proficiency;
    }
    Q_INVOKABLE inline int baseCleverness() const noexcept
    {
        return m_baseAttributesValues.cleverness;
    }
    Q_INVOKABLE inline int baseDailyHealthRecovery() const noexcept
    {
        return m_baseAttributesValues.dailyHealthRecovery;
    }
    Q_INVOKABLE inline int baseDailyStressRecovery() const noexcept
    {
        return m_baseAttributesValues.dailyStressRecovery;
    }
    Q_INVOKABLE inline int baseDailyFoodConsumption() const noexcept
    {
        return m_baseAttributesValues.dailyFoodConsumption;
    }
    Q_INVOKABLE inline int baseSalary() const noexcept
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
    Q_INVOKABLE inline bool isImmuneToStress() const noexcept
    {
        return m_baseAttributesValues.stressLimit==-1;
    }

    void changeSalary(int amount) noexcept;

    void changeDailyFoodConsumption(int amount) noexcept;

    void setDailyHealthRecoveryBuildingBonus(int bonus) noexcept;
    void setDailyStressRecoveryBuildingBonus(int bonus) noexcept;

    void addAttributeModification(AttributeModification *mod) noexcept;
    void decrementModificationsDuration() noexcept;

    inline const Equipment *armor() const noexcept
    {
        return m_armor;
    }
    const Equipment *weaponTool(unsigned slot) const noexcept;
    Q_INVOKABLE inline static unsigned amountOfWeaponToolSlots() noexcept
    {
        return m_amountOfWeaponToolSlots;
    }
    Q_INVOKABLE inline bool hasArmor() const noexcept
    {
        return m_armor!=nullptr;
    }
    Q_INVOKABLE bool hasWeaponToolInSlot(unsigned slot) const noexcept;
    Q_INVOKABLE void prepareWeaponTool(unsigned slot) noexcept;

    void equipArmor(Equipment *armor) noexcept;
    void unequipArmor() noexcept;
    void equipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept;
    void unequipWeaponTool(unsigned slot) noexcept;
    void removeArmor() noexcept;
    void removeWeaponTool(unsigned slot) noexcept;

    inline bool isEquipmentActive() const noexcept
    {
        return m_isEquipmentActive;
    }

    QVector <EquipmentEnums::Category> currentEquipmentCategories() const noexcept;
    bool hasEquipmentFromCategory(EquipmentEnums::Category cat) const noexcept;

    void addCarriedEquipment(Equipment *eq) noexcept;
    QVector <Equipment *> carriedEquipment() const noexcept;
    void clearCarriedEquipment() noexcept;
    Q_INVOKABLE inline unsigned carriedEquipmentAmount() const noexcept
    {
        return m_carriedEquipment.size();
    }
    Q_INVOKABLE void prepareCarriedEquipmentAt(unsigned index) noexcept;

    Q_INVOKABLE unsigned dailyEquipmentCostEnergy() noexcept;
    Q_INVOKABLE unsigned dailyEquipmentCostBM() noexcept;

    Q_INVOKABLE inline bool isDead() const noexcept
    {
        return m_isDead;
    }
    void setIsDead(bool isDead) noexcept
    {
        m_isDead = isDead;
    }

    Q_INVOKABLE inline int noSignalDaysRemaining() const noexcept
    {
        return m_noSignalDaysRemaining;
    }
    void setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept;
    Q_INVOKABLE inline bool isCommunicationAvailable() const noexcept
    {
        return m_noSignalDaysRemaining==0;
    }

    Q_INVOKABLE inline int carriedEnergy() const noexcept
    {
        return m_carriedEnergy;
    }
    void setCarriedEnergy(int carriedEnergy) noexcept;

    Q_INVOKABLE inline int carriedFoodSupplies() const noexcept
    {
        return m_carriedFoodSupplies;
    }
    void setCarriedFoodSupplies(int carriedFoodSupplies) noexcept;

    Q_INVOKABLE inline int carriedBuildingMaterials() const noexcept
    {
        return m_carriedBuildingMaterials;
    }
    void setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept;

    Q_INVOKABLE inline int carriedAetheriteOre() const noexcept
    {
        return m_carriedAetheriteOre;
    }
    void setCarriedAetheriteOre(int carriedAetheriteOre) noexcept;

    inline Mission *assignedMission() noexcept
    {
        return m_assignedMission;
    }
    inline const Mission *assignedMission() const noexcept
    {
        return m_assignedMission;
    }
    void assignMission(Mission *mission) noexcept;

    void trySendingReport(UnifiedReport *report, bool registerInMission) noexcept;
    void addWaitingReport(UnifiedReport *report) noexcept;
    void sendWaitingReports() noexcept;

    void addWaitingDBEntry(const QString &entryName) noexcept;
    void sendWaitingDBEntries() noexcept;

    inline MercenaryEnums::CurrentActivity currentActivity() const noexcept
    {
        return m_currentActivity;
    }
    Q_INVOKABLE QString currentActivityString() const noexcept;
    void setCurrentActivity(MercenaryEnums::CurrentActivity activity) noexcept;

    Q_INVOKABLE QString pathToArt() const noexcept;

    void dismiss(unsigned banDays) noexcept;

    void handleNewDay() noexcept;
    void handleNewWeek() noexcept;

    void returnToBase() noexcept;

    void die(bool playerKnowsIt = 0, bool showNotification = 1) noexcept;
    void becomeMIA() noexcept;

    inline Base *base() noexcept
    {
        return m_base;
    }

signals:
    void died(QString name);
    void ranAway(QString name, unsigned daysOfDoStBan);

private:
    Mercenary(Base *base) noexcept;

    void setName(const QString &name) noexcept
    {
        m_name=name;
    }
    void setStressBorderEffects(const QVector <MercenaryStressBorderEffect> &stressBorderEffects) noexcept
    {
        m_stressBorderEffects=stressBorderEffects;
    }
    void setNature(MercenaryEnums::Nature nature) noexcept
    {
        m_nature=nature;
    }
    void setProfession(MercenaryEnums::Profession profession) noexcept
    {
        m_profession=profession;
    }

    void activateStressBorderEffect() noexcept;
    void deactivateStressBorderEffect() noexcept;

    void setArmor(Equipment *armor) noexcept;
    void setWeaponTool(Equipment *weaponTool, int slot) noexcept;

    void applyEquipmentEffect() noexcept;
    void unapplyEquipmentEffect() noexcept
    {
        applyEquipmentEffect();
    }

    void calculateCurrentAttributeValue(MercenaryEnums::Attribute attributeName) noexcept;//shouldn't be used in most situations (big NO when calc. CE, PR or CL)
    void calculateCurrentAttributeValues() noexcept;//use this instead

    void sumEquipmentCategories() noexcept;

    void setAttributeValue(MercenaryEnums::Attribute attrName, QVariant val) noexcept;//only for H4X

    void activateEquipment() noexcept;
    void deactivateEquipment() noexcept;

    void handleSBEAtDayEnd() noexcept;
    void handleEquipmentCosts() noexcept;
    void handleHunger() noexcept;
    void handleRegeneration() noexcept;

    void handleSalary() noexcept;

    QString m_name;

    MercenaryAttributesSet m_baseAttributesValues;
    MercenaryAttributesSet m_currentAttributesValues;//including eq bonuses, SBE impact

    int m_stockCE;
    int m_stockPR;
    int m_stockCL;

    QVector <MercenaryStressBorderEffect> m_stressBorderEffects;
    MercenaryEnums::Nature m_nature;
    MercenaryEnums::Profession m_profession;

    Equipment *m_armor;
    QVector <Equipment *> m_weaponsTools;
    static const unsigned m_amountOfWeaponToolSlots = 2;
    Equipment *m_preparedWeaponTool;
    QVector <EquipmentEnums::Category> m_currentEquipmentCategories;
    QVector <Equipment *> m_carriedEquipment;
    Equipment *m_preparedCarriedEquipment;
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
    MercenaryEnums::CurrentActivity m_currentActivity;
    QString m_lastKnownLandName;

    QVector <UnifiedReport *> m_waitingReports;
    QVector <QString> m_waitingDBEntries;

    Base *m_base;
};

struct MercenaryDataHelper
{
    MercenaryDataHelper()
        : stockCE(0), stockPR(0), stockCL(0), nature(MercenaryEnums::N_Active), profession(MercenaryEnums::P_Archeologist), isEquipmentActive(true), dhrBuildingBonus(0), dsrBuildingBonus(0), isDead(false), indexOfCurrentSBE(-1), noSignalDaysRemaining(0), carriedEnergy(0), carriedFoodSupplies(0), carriedBuildingMaterials(0), carriedAetheriteOre(0), noSalaryWeeks(0), assignedMission(nullptr), currentActivity(MercenaryEnums::CA_Idle) {}

    QString name;

    MercenaryAttributesSet baseAttributesValues;
    MercenaryAttributesSet currentAttributesValues;

    int stockCE;
    int stockPR;
    int stockCL;

    QVector <MercenaryStressBorderEffect> stressBorderEffects;
    MercenaryEnums::Nature nature;
    MercenaryEnums::Profession profession;

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

    Mission *assignedMission;
    QString lastKnownLandName;
    QVector <UnifiedReport *> waitingReports;
    QVector <QString> waitingDBEntries;
    MercenaryEnums::CurrentActivity currentActivity;
};

QDataStream &operator<<(QDataStream &stream, const MercenaryDataHelper &mercenary) noexcept;
QDataStream &operator>>(QDataStream &stream, MercenaryDataHelper &mercenary) noexcept;

class MercenaryBuilder
{
public:
    MercenaryBuilder() noexcept;
    ~MercenaryBuilder() noexcept;

    static void init(Base *base) noexcept;

    Mercenary *getMercenary() noexcept;

    static Mercenary *qobjectifyMercenaryData(const MercenaryDataHelper &mercenary) noexcept;
    static MercenaryDataHelper deqobjectifyMercenary(Mercenary *mercenary) noexcept;

    void resetMercenary() noexcept;

    void setName(const QString &name) noexcept
    {
        m_mercenary->setName(name);
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
    void setStressBorderEffects(const QVector <MercenaryStressBorderEffect> &stressBorderEffects) noexcept
    {
        m_mercenary->setStressBorderEffects(stressBorderEffects);
    }
    void setDailyStressRecovery(int dailyStressRecovery) noexcept;

    void setSalary(int salary) noexcept;

    void setDailyFoodConsumption(int dailyFoodConsumption) noexcept;

    void setNature(MercenaryEnums::Nature nature) noexcept
    {
        m_mercenary->m_nature=nature;
    }

    void setProfession(MercenaryEnums::Profession profession) noexcept
    {
        m_mercenary->m_profession=profession;
    }

    void setAndEquipArmor(Equipment *armor) noexcept
    {
        m_mercenary->equipArmor(armor);
    }
    void setAndEquipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept;
    void setCarriedEquipment(const QVector <Equipment *> &eqs) noexcept
    {
        m_mercenary->m_carriedEquipment=eqs;
    }

    void setIsDead(bool dead) noexcept
    {
        m_mercenary->m_isDead=dead;
    }
    void setIndexOfCurrentSBE(int index) noexcept
    {
        m_mercenary->m_indexOfCurrentSBE=index;
    }

    void setNoSignalDaysRemaining(int amount) noexcept
    {
        m_mercenary->m_noSignalDaysRemaining=amount;
    }

    void setCarriedEnergy(int amount) noexcept;
    void setCarriedFoodSupplies(int amount) noexcept;
    void setCarriedBuildingMaterials(int amount) noexcept;
    void setCarriedAetheriteOre(int amount) noexcept;

    void setNoSalaryWeeks(unsigned amount) noexcept;

    void setAssignedMission(Mission *mission) noexcept
    {
        m_mercenary->m_assignedMission=mission;
    }
    void setCurrentActivity(MercenaryEnums::CurrentActivity activity) noexcept
    {
        m_mercenary->m_currentActivity=activity;
    }

private:
    Mercenary *m_mercenary;
    static Base *m_base;
};

class MercenariesContainer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* preparedMercenary MEMBER m_preparedMercenary)

public:
    MercenariesContainer(Base *base) noexcept;
    ~MercenariesContainer() noexcept = default;

    Q_INVOKABLE bool prepareMercenaryAt(unsigned index) noexcept;
    void addMercenary(Mercenary *mercenary) noexcept;
    void removeMercenary(unsigned index) noexcept;
    inline const QVector <Mercenary *> &mercenaries() const noexcept
    {
        return m_mercenaries;
    }
    Q_INVOKABLE int amountOfMercenaries() const noexcept
    {
        return m_mercenaries.size();
    }
    Q_INVOKABLE int findMercenary(const QString &name) const noexcept;
    Mercenary *getMercenary(unsigned index) noexcept
    {
        return m_mercenaries.value(index,nullptr);
    }
    void setAmountOfSlots(unsigned amount) noexcept
    {
        m_amountOfSlots=amount;
    }
    Q_INVOKABLE inline unsigned amountOfSlots() const noexcept
    {
        return m_amountOfSlots;
    }
    bool canAddMercenary() const noexcept
    {
        return m_mercenaries.size() < m_amountOfSlots;
    }
    Q_INVOKABLE void dismissMercenary(const QString &name) noexcept
    {
        addDoStBan(name,m_durationOfBanAfterDismiss);
    }

    void handleNewDay() noexcept;
    void handleNewWeek() noexcept;

public slots:
    void addDoStBan(QString name, unsigned daysAmount) noexcept;
    void addDoStBan(QString name) noexcept;//permanent :c

private:
    void connectMercenaryToBanSystem(const QString &name) noexcept;
    void disconnectMercenaryFromBanSystem(const QString &name) noexcept;

    QVector <Mercenary *> m_mercenaries;
    Mercenary *m_preparedMercenary;
    unsigned m_amountOfSlots;
    const unsigned m_durationOfBanAfterDismiss = 21;
    Base *m_basePtr;
};
