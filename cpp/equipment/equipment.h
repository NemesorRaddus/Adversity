#pragma once

#include <QObject>
#include <QVector>
#include <QMap>

#include "enums.h"

class Equipment : public QObject
{
    Q_OBJECT

    friend class EquipmentBuilder;
    template <typename T>
    friend class QVector;
    friend class QDataStream;

public:
    Q_INVOKABLE inline QString name() const noexcept
    {
        return m_name;
    }
    inline EquipmentEnums::Type type() const noexcept
    {
        return m_type;
    }
    Q_INVOKABLE inline QString typeString() const noexcept
    {
        return EquipmentEnums::fromTypeEnumToQString(m_type);
    }
    Q_INVOKABLE inline int tier() const
    {
        return m_tier;
    }

    Q_INVOKABLE int combatEffectivenessBonus() const noexcept;
    Q_INVOKABLE int proficiencyBonus() const noexcept;
    Q_INVOKABLE int clevernessBonus() const noexcept;

    Q_INVOKABLE float luckBonus() const noexcept;

    Q_INVOKABLE int healthLimitBonus() const noexcept;
    Q_INVOKABLE int dailyHealthRecoveryBonus() const noexcept;

    Q_INVOKABLE float stressResistanceBonus() const noexcept;
    Q_INVOKABLE int stressLimitBonus() const noexcept;
    Q_INVOKABLE int stressBorderBonus() const noexcept;
    Q_INVOKABLE int dailyStressRecoveryBonus() const noexcept;

    Q_INVOKABLE int salaryBonus() const noexcept;
    Q_INVOKABLE int dailyFoodConsumptionBonus() const noexcept;

    Q_INVOKABLE unsigned amountOfBonuses() const noexcept;
    Q_INVOKABLE QString bonusAtPosName(unsigned pos) const noexcept;
    Q_INVOKABLE float bonusAtPosValue(unsigned pos) const noexcept;

    inline QVector <EquipmentEnums::Category> categories() const noexcept
    {
        return m_categories;
    }

    Q_INVOKABLE unsigned buyingAetheriteCost() const noexcept;
    Q_INVOKABLE unsigned maintenanceEnergyCost() const noexcept;
    Q_INVOKABLE unsigned maintenanceBuildingMaterialsCost() const noexcept;

    Q_INVOKABLE QString pathToArt() const noexcept;

private:
    Equipment() noexcept;

    void setName(const QString &name) noexcept;
    void setType(EquipmentEnums::Type type) noexcept;
    void setTier(int tier) noexcept;
    void setCategories(const QVector <EquipmentEnums::Category> &cats) noexcept
    {
        m_categories = cats;
    }

    void setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept;
    void setProficiencyBonus(int proficiencyBonus) noexcept;
    void setClevernessBonus(int clevernessBonus) noexcept;
    void setLuckBonus(float luckBonus) noexcept;
    void setHealthLimitBonus(int healthLimitBonus) noexcept;
    void setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept;
    void setStressResistanceBonus(float stressResistanceBonus) noexcept;
    void setStressLimitBonus(int stressLimitBonus) noexcept;
    void setStressBorderBonus(int stressBorderBonus) noexcept;
    void setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept;
    void setSalaryBonus(int salaryBonus) noexcept;
    void setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept;

    QString m_name;
    EquipmentEnums::Type m_type;
    int m_tier;
    QVector <EquipmentEnums::Category> m_categories;
    QMap <EquipmentEnums::Bonus, float> m_bonuses;
};

class EquipmentBuilder
{
public:
    EquipmentBuilder() noexcept;
    ~EquipmentBuilder() noexcept;

    Equipment *getEquipment() noexcept;
    void resetEquiment() noexcept;
    static Equipment *copyEquipment(const Equipment *equipment) noexcept;

    void setName(const QString &name) noexcept;
    void setType(EquipmentEnums::Type type) noexcept;
    void setTier(int tier) noexcept;
    void addCategory(EquipmentEnums::Category cat) noexcept;

    void setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept;
    void setProficiencyBonus(int proficiencyBonus) noexcept;
    void setClevernessBonus(int clevernessBonus) noexcept;
    void setLuckBonus(float luckBonus) noexcept;
    void setHealthLimitBonus(int healthLimitBonus) noexcept;
    void setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept;
    void setStressResistanceBonus(float stressResistanceBonus) noexcept;
    void setStressLimitBonus(int stressLimitBonus) noexcept;
    void setStressBorderBonus(int stressBorderBonus) noexcept;
    void setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept;
    void setSalaryBonus(int salaryBonus) noexcept;
    void setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept;

private:
    Equipment *m_equipment;
};
