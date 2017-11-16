#pragma once

class QDataStream;

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
