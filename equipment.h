#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QDataStream>

#include <QDebug>

struct EquipmentEnums
{
    enum Type
    {
        T_WeaponTool,
        T_Armor
    };
};

class Equipment
{
    friend class EquipmentBuilder;
public:
    void reset() noexcept;

    QString name() const
    {
        return m_name;
    }
    EquipmentEnums::Type type() const
    {
        return m_type;
    }
    int tier() const
    {
        return m_tier;
    }

    int combatEffectivenessBonus() const noexcept
    {
        return m_combatEffectivenessBonus;
    }
    int proficiencyBonus() const noexcept
    {
        return m_proficiencyBonus;
    }
    int clevernessBonus() const noexcept
    {
        return m_clevernessBonus;
    }
    float luckBonus() const noexcept
    {
        return m_luckBonus;
    }
    int healthBonus() const noexcept
    {
        return m_healthBonus;
    }
    int healthLimitBonus() const noexcept
    {
        return m_healthLimitBonus;
    }
    int dailyHealthRecoveryBonus() const noexcept
    {
        return m_dailyHealthRecoveryBonus;
    }
    int stressBonus() const noexcept
    {
        return m_stressBonus;
    }
    float stressResistanceBonus() const noexcept
    {
        return m_stressResistanceBonus;
    }
    int stressLimitBonus() const noexcept
    {
        return m_stressLimitBonus;
    }
    int stressBorderBonus() const noexcept
    {
        return m_stressBorderBonus;
    }
    int dailyStressRecoveryBonus() const noexcept
    {
        return m_dailyStressRecoveryBonus;
    }
    int salaryBonus() const noexcept
    {
        return m_salaryBonus;
    }
    int dailyFoodConsumptionBonus() const noexcept
    {
        return m_dailyFoodConsumptionBonus;
    }

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    Equipment() noexcept;

    void setName(const QString &name) noexcept;
    void setType(EquipmentEnums::Type type) noexcept;
    void setTier(int tier) noexcept;

    void setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept;
    void setProficiencyBonus(int proficiencyBonus) noexcept;
    void setClevernessBonus(int clevernessBonus) noexcept;
    void setLuckBonus(float luckBonus) noexcept;
    void setHealthBonus(int healthBonus) noexcept;
    void setHealthLimitBonus(int healthLimitBonus) noexcept;
    void setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept;
    void setStressBonus(int stressBonus) noexcept;
    void setStressResistanceBonus(float stressResistanceBonus) noexcept;
    void setStressLimitBonus(int stressLimitBonus) noexcept;
    void setStressBorderBonus(int stressBorderBonus) noexcept;
    void setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept;
    void setSalaryBonus(int salaryBonus) noexcept;
    void setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept;

    QString m_name;
    EquipmentEnums::Type m_type;
    int m_tier;

    int m_combatEffectivenessBonus;
    int m_proficiencyBonus;
    int m_clevernessBonus;
    float m_luckBonus;
    int m_healthBonus;
    int m_healthLimitBonus;
    int m_dailyHealthRecoveryBonus;
    int m_stressBonus;
    float m_stressResistanceBonus;
    int m_stressLimitBonus;
    int m_stressBorderBonus;
    int m_dailyStressRecoveryBonus;
    int m_salaryBonus;
    int m_dailyFoodConsumptionBonus;
};

QDataStream &operator<<(QDataStream &stream, const Equipment &equipment) noexcept;
QDataStream &operator>>(QDataStream &stream, Equipment &equipment) noexcept;

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

    void setCombatEffectivenessBonus(int combatEffectivenessBonus) noexcept;
    void setProficiencyBonus(int proficiencyBonus) noexcept;
    void setClevernessBonus(int clevernessBonus) noexcept;
    void setLuckBonus(float luckBonus) noexcept;
    void setHealthBonus(int healthBonus) noexcept;
    void setHealthLimitBonus(int healthLimitBonus) noexcept;
    void setDailyHealthRecoveryBonus(int dailyHealthRecoveryBonus) noexcept;
    void setStressBonus(int stressBonus) noexcept;
    void setStressResistanceBonus(float stressResistanceBonus) noexcept;
    void setStressLimitBonus(int stressLimitBonus) noexcept;
    void setStressBorderBonus(int stressBorderBonus) noexcept;
    void setDailyStressRecoveryBonus(int dailyStressRecoveryBonus) noexcept;
    void setSalaryBonus(int salaryBonus) noexcept;
    void setDailyFoodConsumptionBonus(int dailyFoodConsumptionBonus) noexcept;

private:
    Equipment *m_equipment;
};

#endif // EQUIPMENT_H
