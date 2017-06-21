#include "hero.h"

#include "game.h"

#include <QDebug>

HeroEnums::Nature HeroEnums::fromQStringToNatureEnum(const QString &nature) noexcept
{
    if (nature == "Active")
        return N_Active;
    if (nature == "Convivial")
        return N_Convivial;
    if (nature == "Religious")
        return N_Religious;
    if (nature == "Recluse")
        return N_Recluse;
    qWarning()<<"QString->enum conversion failed for "<<nature;
}

QString HeroEnums::fromNatureEnumToQString(HeroEnums::Nature nature) noexcept
{
    if (nature == N_Active)
        return "Active";
    if (nature == N_Convivial)
        return "Convivial";
    if (nature == N_Religious)
        return "Religious";
    if (nature == N_Recluse)
        return "Recluse";
    qWarning()<<"enum->QString conversion failed for "<<nature;
}

HeroEnums::StressBorderEffect HeroEnums::fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept
{
    if (stressBorderEffect == "None")
        return SBE_None;
    if (stressBorderEffect == "Faint")
        return SBE_Faint;
    if (stressBorderEffect == "Desertion")
        return SBE_Desertion;
    if (stressBorderEffect == "Fear")
        return SBE_Fear;
    if (stressBorderEffect == "Rage")
        return SBE_Rage;
    if (stressBorderEffect == "Fanatic Wrath")
        return SBE_FanaticWrath;
    if (stressBorderEffect == "Paranoia")
        return SBE_Paranoia;
    if (stressBorderEffect == "Bravery")
        return SBE_Bravery;
    if (stressBorderEffect == "Hopeless")
        return SBE_Hopeless;
    if (stressBorderEffect == "Confusion")
        return SBE_Confusion;
    if (stressBorderEffect == "Masochism")
        return SBE_Masochism;
    if (stressBorderEffect == "Abandonce")
        return SBE_Abandonce;
    if (stressBorderEffect == "Restive")
        return SBE_Restive;
    if (stressBorderEffect == "Madness")
        return SBE_Madness;
    if (stressBorderEffect == "Restlessness")
        return SBE_Restlessness;
    if (stressBorderEffect == "Stupor")
        return SBE_Stupor;
    if (stressBorderEffect == "Consciousness")
        return SBE_Consciousness;
    if (stressBorderEffect == "Caution")
        return SBE_Caution;
    if (stressBorderEffect == "Awareness")
        return SBE_Awareness;
    if (stressBorderEffect == "StoneSkin")
        return SBE_StoneSkin;
    if (stressBorderEffect == "Multitasking")
        return SBE_Multitasking;
    if (stressBorderEffect == "Equilibrium")
        return SBE_Equilibrium;
    if (stressBorderEffect == "StressResistant")
        return SBE_StressResistant;
    if (stressBorderEffect == "TheLuckyOne")
        return SBE_TheLuckyOne;
    if (stressBorderEffect == "Doombringer")
        return SBE_Doombringer;
    if (stressBorderEffect == "Excellence")
        return SBE_Excellence;
    if (stressBorderEffect == "Absolute")
        return SBE_Absolute;
    qWarning()<<"QString->enum conversion failed for "<<stressBorderEffect;
}

QString HeroEnums::fromStressBorderEffectEnumToQString(HeroEnums::StressBorderEffect stressBorderEffect) noexcept
{
    if (stressBorderEffect == SBE_None)
        return "None";
    if (stressBorderEffect == SBE_Faint)
        return "Faint";
    if (stressBorderEffect == SBE_Desertion)
        return "Desertion";
    if (stressBorderEffect == SBE_Fear)
        return "Fear";
    if (stressBorderEffect == SBE_Rage)
        return "Rage";
    if (stressBorderEffect == SBE_FanaticWrath)
        return "Fanatic Wrath";
    if (stressBorderEffect == SBE_Paranoia)
        return "Paranoia";
    if (stressBorderEffect == SBE_Bravery)
        return "Bravery";
    if (stressBorderEffect == SBE_Hopeless)
        return "Hopeless";
    if (stressBorderEffect == SBE_Confusion)
        return "Confusion";
    if (stressBorderEffect == SBE_Masochism)
        return "Masochism";
    if (stressBorderEffect == SBE_Abandonce)
        return "Abandonce";
    if (stressBorderEffect == SBE_Restive)
        return "Restive";
    if (stressBorderEffect == SBE_Madness)
        return "Madness";
    if (stressBorderEffect == SBE_Restlessness)
        return "Restlessness";
    if (stressBorderEffect == SBE_Stupor)
        return "Stupor";
    if (stressBorderEffect == SBE_Consciousness)
        return "Consciousness";
    if (stressBorderEffect == SBE_Caution)
        return "Caution";
    if (stressBorderEffect == SBE_Awareness)
        return "Awareness";
    if (stressBorderEffect == SBE_StoneSkin)
        return "StoneSkin";
    if (stressBorderEffect == SBE_Multitasking)
        return "Multitasking";
    if (stressBorderEffect == SBE_Equilibrium)
        return "Equilibrium";
    if (stressBorderEffect == SBE_StressResistant)
        return "StressResistant";
    if (stressBorderEffect == SBE_TheLuckyOne)
        return "TheLuckyOne";
    if (stressBorderEffect == SBE_Doombringer)
        return "Doombringer";
    if (stressBorderEffect == SBE_Excellence)
        return "Excellence";
    if (stressBorderEffect == SBE_Absolute)
        return "Absolute";
    qWarning()<<"enum->QString conversion failed for "<<stressBorderEffect;
}

HeroEnums::Attribute HeroEnums::fromQStringToAttributeEnum(const QString &attribute) noexcept
{
    if (attribute == "Combat Effectiveness")
        return A_CombatEffectiveness;
    if (attribute == "Proficiency")
        return A_Proficiency;
    if (attribute == "Cleverness")
        return A_Cleverness;
    if (attribute == "Luck")
        return A_Luck;
    if (attribute == "Health")
        return A_Health;
    if (attribute == "Health Limit")
        return A_HealthLimit;
    if (attribute == "Daily Health Recovery")
        return A_DailyHealthRecovery;
    if (attribute == "Stress")
        return A_Stress;
    if (attribute == "Stress Resistance")
        return A_StressResistance;
    if (attribute == "Stress Limit")
        return A_StressLimit;
    if (attribute == "Stress Border")
        return A_StressBorder;
    if (attribute == "Daily Stress Recovery")
        return A_DailyStressRecovery;
    if (attribute == "Salary")
        return A_Salary;
    if (attribute == "Daily Food Consumption")
        return A_DailyFoodConsumption;
    qWarning()<<"QString->enum conversion failed for "<<attribute;
}

QString HeroEnums::fromAttributeEnumToQString(HeroEnums::Attribute attribute) noexcept
{
    if (attribute == A_CombatEffectiveness)
        return "Combat Effectiveness";
    if (attribute == A_Proficiency)
        return "Proficiency";
    if (attribute == A_Cleverness)
        return "Cleverness";
    if (attribute == A_Luck)
        return "Luck";
    if (attribute == A_Health)
        return "Health";
    if (attribute == A_HealthLimit)
        return "Health Limit";
    if (attribute == A_DailyHealthRecovery)
        return "Daily Health Recovery";
    if (attribute == A_Stress)
        return "Stress";
    if (attribute == A_StressResistance)
        return "Stress Resistance";
    if (attribute == A_StressLimit)
        return "Stress Limit";
    if (attribute == A_StressBorder)
        return "Stress Border";
    if (attribute == A_DailyStressRecovery)
        return "Daily Stress Recovery";
    if (attribute == A_Salary)
        return "Salary";
    if (attribute == A_DailyFoodConsumption)
        return "Daily Food Consumption";
    qWarning()<<"enum->QString conversion failed for "<<attribute;
}

HeroEnums::CurrentActivity HeroEnums::fromQStringToCurrentActivityEnum(const QString &currentActivity) noexcept
{
    if (currentActivity == "Idle")
        return CA_Idle;
    if (currentActivity == "On Mission")
        return CA_OnMission;
    if (currentActivity == "In Hospital")
        return CA_InHospital;
    if (currentActivity == "On Training Ground")
        return CA_OnTrainingGround;
    if (currentActivity == "In Gym")
        return CA_InGym;
    if (currentActivity == "In Laboratory")
        return CA_InLaboratory;
    if (currentActivity == "In Playing Field")
        return CA_InPlayingField;
    if (currentActivity == "In Bar")
        return CA_InBar;
    if (currentActivity == "In Shrine")
        return CA_InShrine;
    if (currentActivity == "In Seclusion")
        return CA_InSeclusion;
    if (currentActivity == "Arriving")
        return CA_Arriving;
    qWarning()<<"QString->enum conversion failed for "<<currentActivity;
}

QString HeroEnums::fromCurrentActivityEnumToQString(HeroEnums::CurrentActivity currentActivity) noexcept
{
    if (currentActivity == CA_Idle)
        return "Idle";
    if (currentActivity == CA_OnMission)
        return "On Mission";
    if (currentActivity == CA_InHospital)
        return "In Hospital";
    if (currentActivity == CA_OnTrainingGround)
        return "On Training Ground";
    if (currentActivity == CA_InGym)
        return "In Gym";
    if (currentActivity == CA_InLaboratory)
        return "In Laboratory";
    if (currentActivity == CA_InPlayingField)
        return "In Playing Field";
    if (currentActivity == CA_InBar)
        return "In Bar";
    if (currentActivity == CA_InShrine)
        return "In Shrine";
    if (currentActivity == CA_InSeclusion)
        return "In Seclusion";
    if (currentActivity == CA_Arriving)
        return "Arriving";
    qWarning()<<"enum->QString conversion failed for "<<currentActivity;
}

HeroEnums::Profession HeroEnums::fromQStringToProfessionEnum(const QString &profession) noexcept
{
    if (profession == "Bounty Hunter")
        return P_BountyHunter;
    if (profession == "Gunzerker")
        return P_Gunzerker;
    if (profession == "Priest Of The Universe")
        return P_PriestOfTheUniverse;
    if (profession == "Priestess Of The Universe")
        return P_PriestessOfTheUniverse;
    if (profession == "Battle Droid")
        return P_BattleDroid;
    if (profession == "Space Nomad")
        return P_SpaceNomad;
    if (profession == "Archeologist")
        return P_Archeologist;
    if (profession == "Criminal")
        return P_Criminal;
    if (profession == "Cyborg")
        return P_Cyborg;
    if (profession == "Specialist")
        return P_Specialist;
    if (profession == "Doomsayer")
        return P_Doomsayer;
    qWarning()<<"QString->enum conversion failed for "<<profession;
}

QString HeroEnums::fromProfessionEnumToQString(HeroEnums::Profession profession) noexcept
{
    if (profession == P_BountyHunter)
        return "Bounty Hunter";
    if (profession == P_Gunzerker)
        return "Gunzerker";
    if (profession == P_PriestOfTheUniverse)
        return "Priest Of The Universe";
    if (profession == P_PriestessOfTheUniverse)
        return "Priestess Of The Universe";
    if (profession == P_BattleDroid)
        return "Battle Droid";
    if (profession == P_SpaceNomad)
        return "Space Nomad";
    if (profession == P_Archeologist)
        return "Archeologist";
    if (profession == P_Criminal)
        return "Criminal";
    if (profession == P_Cyborg)
        return "Cyborg";
    if (profession == P_Specialist)
        return "Specialist";
    if (profession == P_Doomsayer)
        return "Doomsayer";
    qWarning()<<"enum->QString conversion failed for "<<profession;
}

QDataStream &HeroStressBorderEffect::read(QDataStream &stream) noexcept
{
    quint8 n;

    stream>>n;
    effectName = static_cast<HeroEnums::StressBorderEffect>(n);

    return stream;
}

QDataStream &HeroStressBorderEffect::write(QDataStream &stream) const noexcept
{
    stream<<static_cast<quint8>(effectName);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const HeroStressBorderEffect &effect) noexcept
{
    return effect.write(stream);
}

QDataStream &operator>>(QDataStream &stream, HeroStressBorderEffect &effect) noexcept
{
    return effect.read(stream);
}

QDataStream &operator<<(QDataStream &stream, const HeroAttributesSet &attrs) noexcept
{
    stream<<static_cast<qint16>(attrs.combatEffectiveness);
    stream<<static_cast<qint16>(attrs.proficiency);
    stream<<static_cast<qint16>(attrs.cleverness);
    stream<<static_cast<qreal>(attrs.luck);
    stream<<static_cast<qint16>(attrs.health);
    stream<<static_cast<qint16>(attrs.healthLimit);
    stream<<static_cast<qint16>(attrs.dailyHealthRecovery);
    stream<<static_cast<qint16>(attrs.stress);
    stream<<static_cast<qreal>(attrs.stressResistance);
    stream<<static_cast<qint16>(attrs.stressLimit);
    stream<<static_cast<qint16>(attrs.stressBorder);
    stream<<static_cast<qint16>(attrs.dailyStressRecovery);
    stream<<static_cast<qint16>(attrs.salary);
    stream<<static_cast<qint16>(attrs.dailyFoodConsumption);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, HeroAttributesSet &attrs) noexcept
{
    qint16 ii;
    qreal d;

    stream>>ii;
    attrs.combatEffectiveness=ii;

    stream>>ii;
    attrs.proficiency=ii;

    stream>>ii;
    attrs.cleverness=ii;

    stream>>d;
    attrs.luck=d;

    stream>>ii;
    attrs.health=ii;

    stream>>ii;
    attrs.healthLimit=ii;

    stream>>ii;
    attrs.dailyHealthRecovery=ii;

    stream>>ii;
    attrs.stress=ii;

    stream>>d;
    attrs.stressResistance=d;

    stream>>ii;
    attrs.stressLimit=ii;

    stream>>ii;
    attrs.stressBorder=ii;

    stream>>ii;
    attrs.dailyStressRecovery=ii;

    stream>>ii;
    attrs.salary=ii;

    stream>>ii;
    attrs.dailyFoodConsumption=ii;

    return stream;
}

const HeroStressBorderEffect *Hero::currentSBE() const noexcept
{
    return m_indexOfCurrentSBE==-1 ? nullptr : &(m_stressBorderEffects[m_indexOfCurrentSBE]);
}

QString Hero::stressBorderEffectNameString(unsigned index) const noexcept
{
    return index<m_stressBorderEffects.size() ? HeroEnums::fromStressBorderEffectEnumToQString(m_stressBorderEffects[index].effectName) : "";
}

void Hero::handleSBEAtDayEnd()  noexcept
{
    if (!isStressBorderEffectActive())
        return;

    if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Desertion)
    {
        int chance = 100*m_currentAttributesValues.stress/m_currentAttributesValues.stressLimit;

        if (chance >= Randomizer::randomBetweenAAndB(1,100))
        {
            ranAway(m_name,21);
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Confusion)
    {
        if (m_currentActivity == HeroEnums::CA_OnMission)
        {
            if (10 >= Randomizer::randomBetweenAAndB(1,100))
                m_noSignalDaysRemaining=-1;
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Masochism)
    {
        if (60 >= Randomizer::randomBetweenAAndB(1,100))
        {
            if (m_currentAttributesValues.health>2)
            {
                m_currentAttributesValues.health-=2;
                int amount = Randomizer::randomBetweenAAndB(0,20) - 10;
                if (amount<0)
                    decreaseStress(-amount);
                else if (amount>0)
                    increaseStress(amount);
            }
            else
            {
                m_currentAttributesValues.health=0;
                die(HeroEnums::DR_Masochism);
            }
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Restlessness)
    {
        increaseStress(m_currentAttributesValues.stressLimit/20);
    }
}

QString Hero::natureString() const noexcept
{
    return HeroEnums::fromNatureEnumToQString(m_nature);
}

QString Hero::professionString() const noexcept
{
    return HeroEnums::fromProfessionEnumToQString(m_profession);
}

void Hero::changeCombatEffectiveness(int amount) noexcept
{
    if (m_baseAttributesValues.combatEffectiveness+amount >= 0)
        m_baseAttributesValues.combatEffectiveness+=amount;
    else
        m_baseAttributesValues.combatEffectiveness=0;

    calculateCurrentAttributeValues();
}

void Hero::changeProficiency(int amount) noexcept
{
    if (m_baseAttributesValues.proficiency+amount >= 0)
        m_baseAttributesValues.proficiency+=amount;
    else
        m_baseAttributesValues.proficiency=0;

    calculateCurrentAttributeValues();
}

void Hero::changeCleverness(int amount) noexcept
{
    if (m_baseAttributesValues.cleverness+amount >= 0)
        m_baseAttributesValues.cleverness+=amount;
    else
        m_baseAttributesValues.cleverness=0;

    calculateCurrentAttributeValues();
}

void Hero::changeLuck(float amount) noexcept
{
    if (m_baseAttributesValues.luck+amount < 0)
        m_baseAttributesValues.luck=0;
    else if (m_baseAttributesValues.luck+amount > 1)
        m_baseAttributesValues.luck=1;
    else
        m_baseAttributesValues.luck+=amount;

    calculateCurrentAttributeValue(HeroEnums::A_Luck);
}

void Hero::changeHealth(int amount) noexcept
{
    if (m_currentAttributesValues.health+amount >= 0)
    {
        if (m_currentAttributesValues.health+amount<m_currentAttributesValues.healthLimit)
            m_currentAttributesValues.health+=amount;
        else
            m_currentAttributesValues.health=m_currentAttributesValues.healthLimit;
    }
    else
    {
        if (isStressBorderEffectActive() && m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Bravery && 10 >= Randomizer::randomBetweenAAndB(1,100))
        {
            m_currentAttributesValues.health=1;
            m_carriedAetheriteOre=0;
            m_carriedBuildingMaterials=0;
            m_carriedEnergy=0;
            m_carriedFoodSupplies=0;
        }
        else
            m_currentAttributesValues.health=0;//hero dies :c
    }
}

void Hero::changeHealthLimit(int amount) noexcept
{
    if (m_currentAttributesValues.healthLimit+amount > 0)
        m_currentAttributesValues.healthLimit+=amount;
    else
        m_currentAttributesValues.healthLimit=1;

    calculateCurrentAttributeValue(HeroEnums::A_HealthLimit);
}

void Hero::changeDailyHealthRecovery(int amount) noexcept
{
    m_baseAttributesValues.dailyHealthRecovery+=amount;

    calculateCurrentAttributeValue(HeroEnums::A_DailyHealthRecovery);
}

void Hero::increaseStress(unsigned amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stress+amount*m_currentAttributesValues.stressResistance>=m_currentAttributesValues.stressLimit)
        {
            m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
            die(HeroEnums::DR_StressLimitAchieved);
        }
        else if (m_currentAttributesValues.stress + amount * m_currentAttributesValues.stressResistance >= m_currentAttributesValues.stressBorder && !isStressBorderEffectActive())
        {
            m_currentAttributesValues.stress+=amount*m_currentAttributesValues.stressResistance;
            activateStressBorderEffect();
        }
        else
            m_currentAttributesValues.stress+=amount*m_currentAttributesValues.stressResistance;
    }
}

void Hero::decreaseStress(unsigned amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stress-amount<m_currentAttributesValues.stressBorder && isStressBorderEffectActive())
        {
            if (m_currentAttributesValues.stress-amount>0)
                m_currentAttributesValues.stress-=amount;
            else
                m_currentAttributesValues.stress=0;
            deactivateStressBorderEffect();
        }
        else
        {
            if (m_currentAttributesValues.stress-amount>0)
                m_currentAttributesValues.stress-=amount;
            else
                m_currentAttributesValues.stress=0;
        }
    }
}

void Hero::changeStressResistance(float amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stressResistance+amount>=0)
            m_currentAttributesValues.stressResistance+=amount;
    }
}

void Hero::changeStressLimit(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_baseAttributesValues.stressLimit+amount>1)
        {
            m_baseAttributesValues.stressLimit+=amount;

            calculateCurrentAttributeValue(HeroEnums::A_StressLimit);

            if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressLimit)
            {
                m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
                die(HeroEnums::DR_StressLimitAchieved);
            }
        }
        else
        {
            m_baseAttributesValues.stressLimit=1;

            calculateCurrentAttributeValue(HeroEnums::A_StressLimit);

            if (m_currentAttributesValues.stress>=1)
            {
                m_currentAttributesValues.stress=1;
                die(HeroEnums::DR_StressLimitAchieved);
            }
        }
    }
}

void Hero::changeStressBorder(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_baseAttributesValues.stressBorder+amount<1)
            m_baseAttributesValues.stressBorder=0;
        else
            m_baseAttributesValues.stressBorder+=amount;

        calculateCurrentAttributeValue(HeroEnums::A_StressBorder);

        if (m_currentAttributesValues.stress<m_currentAttributesValues.stressBorder && isStressBorderEffectActive())
            deactivateStressBorderEffect();
        else if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressBorder && !isStressBorderEffectActive())
            activateStressBorderEffect();
    }
}

void Hero::changeDailyStressRecovery(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        m_baseAttributesValues.dailyStressRecovery+=amount;

        calculateCurrentAttributeValue(HeroEnums::A_DailyStressRecovery);
    }
}

void Hero::changeSalary(int amount) noexcept
{
    m_baseAttributesValues.salary+=amount;

    calculateCurrentAttributeValue(HeroEnums::A_Salary);
}

void Hero::changeDailyFoodConsumption(int amount) noexcept
{
    if (m_baseAttributesValues.dailyFoodConsumption+amount>=0)
        m_baseAttributesValues.dailyFoodConsumption+=amount;
    else
        m_baseAttributesValues.dailyFoodConsumption=0;

    calculateCurrentAttributeValue(HeroEnums::A_DailyFoodConsumption);
}

Equipment *Hero::weaponTool(int slot) const noexcept
{
    return m_weaponsTools.value(slot,nullptr);
}

void Hero::equipArmor(Equipment *armor) noexcept
{
    if (armor!=nullptr)
    {
        if (m_armor!=nullptr)
            unequipArmor();

        applyEquipmentEffect();
        setArmor(armor);
    }
}

void Hero::unequipArmor() noexcept
{
    if (m_armor!=nullptr)
    {
        unapplyEquipmentEffect();
        setArmor(nullptr);
    }
}

void Hero::equipWeaponTool(Equipment *weaponTool, int slot) noexcept
{
    if (weaponTool!=nullptr && slot>=0 && slot<m_amountOfWeaponToolSlots)
    {
        if (m_weaponsTools[slot]!=nullptr)
            unequipWeaponTool(slot);

        applyEquipmentEffect();
        setWeaponTool(weaponTool,slot);
    }
}

void Hero::unequipWeaponTool(int slot) noexcept
{
    if (slot>=0 && slot<m_amountOfWeaponToolSlots && m_weaponsTools[slot]!=nullptr)
    {
        unapplyEquipmentEffect();
        setWeaponTool(nullptr,slot);
    }
}

Hero::Hero() noexcept
    : m_nature(HeroEnums::N_Active), m_armor(nullptr), m_isDead(0), m_indexOfCurrentSBE(-1), m_noSignalDaysRemaining(0), m_carriedEnergy(0), m_carriedFoodSupplies(0), m_carriedBuildingMaterials(0), m_carriedAetheriteOre(0), m_assignedMission(nullptr), m_currentActivity(HeroEnums::CA_Idle)
{
    m_stressBorderEffects.reserve(1);
    m_stressBorderEffects.push_back({HeroEnums::SBE_None});
    
    m_weaponsTools.reserve(2);
    m_weaponsTools.push_back(nullptr);
    m_weaponsTools.push_back(nullptr);
}

void Hero::setCarriedEnergy(int carriedEnergy) noexcept
{
    m_carriedEnergy = carriedEnergy;
}

void Hero::setCarriedFoodSupplies(int carriedFoodSupplies) noexcept
{
    m_carriedFoodSupplies = carriedFoodSupplies;
}

void Hero::setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept
{
    m_carriedBuildingMaterials = carriedBuildingMaterials;
}

void Hero::setCarriedAetheriteOre(int carriedAetheriteOre) noexcept
{
    m_carriedAetheriteOre = carriedAetheriteOre;
}

void Hero::assignMission(Mission *mission) noexcept
{
    m_assignedMission=mission;
    m_currentActivity=HeroEnums::CA_OnMission;
}

QString Hero::currentActivityString() const noexcept
{
    return HeroEnums::fromCurrentActivityEnumToQString(m_currentActivity);
}

void Hero::setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept
{
    m_currentActivity=activity;
    if (activity==HeroEnums::CA_OnMission)
        m_assignedMission=nullptr;
}

void Hero::dismiss(unsigned banDays) noexcept
{
    emit ranAway(name(),banDays);
    //TODO
}

void Hero::activateStressBorderEffect() noexcept
{
    if (!isImmuneToStress())
    {
        m_indexOfCurrentSBE = Randomizer::randomBetweenAAndB(0,m_stressBorderEffects.size()-1);

        if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Consciousness)
        {
            m_carriedBuildingMaterials = 0;
        }

        calculateCurrentAttributeValues();
    }
}

void Hero::deactivateStressBorderEffect() noexcept
{
    if (!isImmuneToStress())
    {
        m_indexOfCurrentSBE = -1;

        calculateCurrentAttributeValues();
    }
}

void Hero::die(HeroEnums::DyingReason reason) noexcept
{
    m_isDead=1;
    m_currentAttributesValues.health=0;
    emit died(name(),reason);
    //TODO
}

void Hero::setArmor(Equipment *armor) noexcept
{
    m_armor=armor;
}

void Hero::setWeaponTool(Equipment *weaponTool, int slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots)
        m_weaponsTools[slot]=weaponTool;
}

void Hero::applyEquipmentEffect() noexcept
{
    calculateCurrentAttributeValues();
}

void Hero::calculateCurrentAttributeValue(HeroEnums::Attribute attributeName) noexcept
{
    if (attributeName == HeroEnums::A_Cleverness)
    {
        int x=m_baseAttributesValues.cleverness;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Faint)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_FanaticWrath)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Rage)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Consciousness)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Caution)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Awareness)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Bravery)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Doombringer)
                x+=4;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->clevernessBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->clevernessBonus();
        }

        if (x>0)
            m_currentAttributesValues.cleverness=x;
        else
            m_currentAttributesValues.cleverness=0;
    }
    else if (attributeName == HeroEnums::A_CombatEffectiveness)
    {
        int x=m_baseAttributesValues.combatEffectiveness;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Faint)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Fear)
                x-=3;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_FanaticWrath)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Confusion)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Rage)
                x+=4;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Restive)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Consciousness)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Caution)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Awareness)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Bravery)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Doombringer)
                x+=6;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->combatEffectivenessBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->combatEffectivenessBonus();
        }

        if (x>0)
            m_currentAttributesValues.combatEffectiveness=x;
        else
            m_currentAttributesValues.combatEffectiveness=0;
    }
    else if (attributeName == HeroEnums::A_DailyFoodConsumption)
    {
        int x=m_baseAttributesValues.dailyFoodConsumption;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Awareness)
                x+=1;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->dailyFoodConsumptionBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->dailyFoodConsumptionBonus();
        }

        if (x>0)
            m_currentAttributesValues.dailyFoodConsumption=x;
        else
            m_currentAttributesValues.dailyFoodConsumption=0;
    }
    else if (attributeName == HeroEnums::A_DailyHealthRecovery)
    {
        int x=m_baseAttributesValues.dailyHealthRecovery;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_StoneSkin)
                x-=5;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->dailyHealthRecoveryBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->dailyHealthRecoveryBonus();
        }

        if (x>0)
            m_currentAttributesValues.dailyHealthRecovery=x;
        else
            m_currentAttributesValues.dailyHealthRecovery=0;
    }
    else if (attributeName == HeroEnums::A_DailyStressRecovery)
    {
        int x=m_baseAttributesValues.dailyStressRecovery;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_FanaticWrath)
                x+=10;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Doombringer)
                x+=10;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->dailyStressRecoveryBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->dailyStressRecoveryBonus();
        }

        if (x>0)
            m_currentAttributesValues.dailyStressRecovery=x;
        else
            m_currentAttributesValues.dailyStressRecovery=0;
    }
    else if (attributeName == HeroEnums::A_HealthLimit)
    {
        int x=m_baseAttributesValues.healthLimit;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_StoneSkin)
                x+=10;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->healthLimitBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->healthLimitBonus();
        }

        if (x>1)
            m_currentAttributesValues.healthLimit=x;
        else
            m_currentAttributesValues.healthLimit=1;

        if (m_currentAttributesValues.health>m_currentAttributesValues.healthLimit)
            m_currentAttributesValues.health=m_currentAttributesValues.healthLimit;
    }
    else if (attributeName == HeroEnums::A_Luck)
    {
        float x=m_baseAttributesValues.luck;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Hopeless)
                x-=0.35;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_TheLuckyOne)
                x+=1;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->luckBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->luckBonus();
        }

        if (x<0)
            m_currentAttributesValues.luck=0;
        else if (x>1)
            m_currentAttributesValues.luck=1;
        else
            m_currentAttributesValues.luck=x;
    }
    else if (attributeName == HeroEnums::A_Proficiency)
    {
        int x=m_baseAttributesValues.proficiency;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Faint)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_FanaticWrath)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Confusion)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Rage)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Caution)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Bravery)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Doombringer)
                x+=4;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->proficiencyBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->proficiencyBonus();
        }

        if (x>0)
            m_currentAttributesValues.proficiency=x;
        else
            m_currentAttributesValues.proficiency=0;
    }
    else if (attributeName == HeroEnums::A_Salary)
    {
        int x=m_baseAttributesValues.salary;
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->salaryBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->salaryBonus();
        }

        if (x>0)
            m_currentAttributesValues.salary=x;
        else
            m_currentAttributesValues.salary=0;
    }
    else if (attributeName == HeroEnums::A_StressBorder)
    {
        int x=m_baseAttributesValues.stressBorder;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_StressResistant)
                x-=30;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->stressBorderBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->stressBorderBonus();
        }

        if (x>0)
            m_currentAttributesValues.stressBorder=x;
        else
            m_currentAttributesValues.stressBorder=0;

        if (!isStressBorderEffectActive() && m_currentAttributesValues.stress>=m_currentAttributesValues.stressBorder)
            activateStressBorderEffect();
        if (isStressBorderEffectActive() && m_currentAttributesValues.stress<m_currentAttributesValues.stressBorder)
            deactivateStressBorderEffect();
    }
    else if (attributeName == HeroEnums::A_StressLimit)
    {
        int x=m_baseAttributesValues.stressLimit;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Abandonce)
                x-=30;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_StressResistant)
                x+=30;
        }
        if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
        {
            if (m_armor!=nullptr)
                x+=m_armor->stressLimitBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->stressLimitBonus();
        }

        if (x>1)
            m_currentAttributesValues.stressLimit=x;
        else
            m_currentAttributesValues.stressLimit=1;

        if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressLimit)
        {
            m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
            die(HeroEnums::DR_StressLimitAchieved);
        }
    }
    else if (attributeName == HeroEnums::A_StressResistance)
    {
        float x=m_baseAttributesValues.stressResistance;

        if (x==-1)//special value, N/A
            m_currentAttributesValues.stressResistance=-1;
        else
        {
            if (isStressBorderEffectActive())
            {
                if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Faint)
                    x+=0.2;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Paranoia)
                    x+=0.5;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Rage)
                    x-=0.3;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Restive)
                    x+=0.1;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Consciousness)
                    x-=0.2;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Absolute)
                    x+=0.2;
            }
            if (!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != HeroEnums::SBE_Madness)
            {
                if (m_armor!=nullptr)
                    x+=m_armor->stressResistanceBonus();
                for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                    if (m_weaponsTools[i]!=nullptr)
                        x+=m_weaponsTools[i]->stressResistanceBonus();
            }

            if (x>0)
                m_currentAttributesValues.stressResistance=x;
            else
                m_currentAttributesValues.stressResistance=0;
        }
    }
}

void Hero::calculateCurrentAttributeValues() noexcept
{
    calculateCurrentAttributeValue(HeroEnums::A_Cleverness);
    calculateCurrentAttributeValue(HeroEnums::A_CombatEffectiveness);
    calculateCurrentAttributeValue(HeroEnums::A_DailyFoodConsumption);
    calculateCurrentAttributeValue(HeroEnums::A_DailyHealthRecovery);
    if (!isImmuneToStress())
    {
        calculateCurrentAttributeValue(HeroEnums::A_DailyStressRecovery);
        calculateCurrentAttributeValue(HeroEnums::A_StressBorder);
        calculateCurrentAttributeValue(HeroEnums::A_StressLimit);
        calculateCurrentAttributeValue(HeroEnums::A_StressResistance);
    }
    calculateCurrentAttributeValue(HeroEnums::A_HealthLimit);
    calculateCurrentAttributeValue(HeroEnums::A_Luck);
    calculateCurrentAttributeValue(HeroEnums::A_Proficiency);
    calculateCurrentAttributeValue(HeroEnums::A_Salary);

    if (isStressBorderEffectActive())//calculate those effect results which are more "meta"-like
    {
        if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Stupor)
        {
            int minVal = qMin(m_currentAttributesValues.combatEffectiveness, qMin(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness));

            m_currentAttributesValues.combatEffectiveness = minVal;
            m_currentAttributesValues.proficiency = minVal;
            m_currentAttributesValues.cleverness = minVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Equilibrium)
        {
            int minVal = qMin(m_currentAttributesValues.combatEffectiveness, qMin(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness)) + 1;

            m_currentAttributesValues.combatEffectiveness = minVal;
            m_currentAttributesValues.proficiency = minVal;
            m_currentAttributesValues.cleverness = minVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Excellence)
        {
            int maxVal = qMax(m_currentAttributesValues.combatEffectiveness, qMax(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness));

            m_currentAttributesValues.combatEffectiveness = maxVal;
            m_currentAttributesValues.proficiency = maxVal;
            m_currentAttributesValues.cleverness = maxVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Absolute)
        {
            int maxVal = qMax(m_currentAttributesValues.combatEffectiveness, qMax(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness));

            QVector <int *> acceptedAttrs;
            if (m_currentAttributesValues.combatEffectiveness == maxVal)
                acceptedAttrs.push_back(&m_currentAttributesValues.combatEffectiveness);
            if (m_currentAttributesValues.proficiency == maxVal)
                acceptedAttrs.push_back(&m_currentAttributesValues.proficiency);
            if (m_currentAttributesValues.cleverness == maxVal)
                acceptedAttrs.push_back(&m_currentAttributesValues.cleverness);

            *(acceptedAttrs[Randomizer::randomBetweenAAndB(0,acceptedAttrs.size()-1)])+=3;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == HeroEnums::SBE_Multitasking)
        {
            int val = (m_currentAttributesValues.combatEffectiveness+m_currentAttributesValues.proficiency+m_currentAttributesValues.cleverness)/3;

            m_currentAttributesValues.combatEffectiveness=val;
            m_currentAttributesValues.proficiency=val;
            m_currentAttributesValues.cleverness=val;
        }
    }
}

void Hero::setAttributeValue(HeroEnums::Attribute attrName, float val) noexcept
{
    switch (attrName) {
    case HeroEnums::A_Cleverness:
        m_currentAttributesValues.cleverness=val;
        break;
    case HeroEnums::A_CombatEffectiveness:
        m_currentAttributesValues.combatEffectiveness=val;
        break;
    case HeroEnums::A_DailyFoodConsumption:
        m_currentAttributesValues.dailyFoodConsumption=val;
        break;
    case HeroEnums::A_DailyHealthRecovery:
        m_currentAttributesValues.dailyHealthRecovery=val;
        break;
    case HeroEnums::A_DailyStressRecovery:
        m_currentAttributesValues.dailyStressRecovery=val;
        break;
    case HeroEnums::A_Health:
        m_currentAttributesValues.health=val;
        break;
    case HeroEnums::A_HealthLimit:
        m_currentAttributesValues.healthLimit=val;
        break;
    case HeroEnums::A_Luck:
        m_currentAttributesValues.luck=val;
        break;
    case HeroEnums::A_Proficiency:
        m_currentAttributesValues.proficiency=val;
        break;
    case HeroEnums::A_Salary:
        m_currentAttributesValues.salary=val;
        break;
    case HeroEnums::A_Stress:
        m_currentAttributesValues.stress=val;
        break;
    case HeroEnums::A_StressBorder:
        m_currentAttributesValues.stressBorder=val;
        break;
    case HeroEnums::A_StressLimit:
        m_currentAttributesValues.stressLimit=val;
        break;
    case HeroEnums::A_StressResistance:
        m_currentAttributesValues.stressResistance=val;
        break;
    default:
        break;
    }
}

HeroBuilder::HeroBuilder() noexcept
{
    m_hero=new Hero;
}

HeroBuilder::~HeroBuilder() noexcept
{
    delete m_hero;
}

Hero *HeroBuilder::getHero() noexcept
{
    m_hero->calculateCurrentAttributeValues();
    Hero *r=m_hero;
    m_hero=new Hero;
    return r;
}

Hero *HeroBuilder::qobjectifyHeroData(const HeroDataHelper &hero) noexcept
{
    Hero *r=new Hero;
    r->m_name = hero.name;
    r->m_baseAttributesValues = hero.baseAttributesValues;
    r->m_currentAttributesValues = hero.currentAttributesValues;
    r->m_stressBorderEffects = hero.stressBorderEffects;
    r->m_nature = hero.nature;
    r->m_profession = hero.profession;
    if (!hero.armor.isEmpty())
        r->m_armor = Game::gameInstance()->assetsPool().makeEquipmentNamed(hero.armor);
    else
        r->m_armor = nullptr;
    for (int i=0;i<hero.weaponsTools.size();++i)
    {
        if (!hero.weaponsTools[i].isEmpty())
            r->m_weaponsTools[i]=Game::gameInstance()->assetsPool().makeEquipmentNamed(hero.weaponsTools[i]);
        else
            r->m_weaponsTools[i]=nullptr;
    }
    r->m_isDead = hero.isDead;
    r->m_indexOfCurrentSBE = hero.indexOfCurrentSBE;
    r->m_noSignalDaysRemaining = hero.noSignalDaysRemaining;
    r->m_carriedEnergy = hero.carriedEnergy;
    r->m_carriedFoodSupplies = hero.carriedFoodSupplies;
    r->m_carriedBuildingMaterials = hero.carriedBuildingMaterials;
    r->m_carriedAetheriteOre = hero.carriedAetheriteOre;
    //TODO mission
    r->m_currentActivity = hero.currentActivity;

    return r;
}

HeroDataHelper HeroBuilder::deqobjectifyHero(Hero *hero) noexcept
{
    HeroDataHelper r;

    r.name = hero->m_name;
    r.baseAttributesValues = hero->m_baseAttributesValues;
    r.currentAttributesValues = hero->m_currentAttributesValues;
    r.stressBorderEffects = hero->m_stressBorderEffects;
    r.nature = hero->m_nature;
    r.profession = hero->m_profession;
    if (hero->m_armor != nullptr)
        r.armor = hero->m_armor->name();
    else
        r.armor = "";
    for (int i=0;i<hero->amountOfWeaponToolSlots();++i)
    {
        if (hero->m_weaponsTools[i] != nullptr)
            r.weaponsTools.push_back(hero->m_weaponsTools[i]->name());
        else
            r.weaponsTools.push_back("");
    }
    r.isDead = hero->m_isDead;
    r.indexOfCurrentSBE = hero->m_indexOfCurrentSBE;
    r.noSignalDaysRemaining = hero->m_noSignalDaysRemaining;
    r.carriedEnergy = hero->m_carriedEnergy;
    r.carriedFoodSupplies = hero->m_carriedFoodSupplies;
    r.carriedBuildingMaterials = hero->m_carriedBuildingMaterials;
    r.carriedAetheriteOre = hero->m_carriedAetheriteOre;
    //TODO mission
    r.currentActivity = hero->m_currentActivity;

    return r;
}

QDataStream &operator<<(QDataStream &stream, const HeroDataHelper &hero) noexcept
{
    stream<<hero.name;

    stream<<hero.baseAttributesValues;

    stream<<hero.currentAttributesValues;

    stream<<hero.stressBorderEffects;

    stream<<static_cast<quint8>(hero.nature);

    stream<<static_cast<quint8>(hero.profession);

    stream<<hero.armor;

    stream<<hero.weaponsTools;

    stream<<hero.isDead;

    stream<<static_cast<qint16>(hero.indexOfCurrentSBE);

    stream<<static_cast<qint16>(hero.noSignalDaysRemaining);

    stream<<static_cast<qint16>(hero.carriedEnergy);

    stream<<static_cast<qint16>(hero.carriedFoodSupplies);

    stream<<static_cast<qint16>(hero.carriedBuildingMaterials);

    stream<<static_cast<qint16>(hero.carriedAetheriteOre);

    //TODO Mission saving

    stream<<static_cast<quint8>(hero.currentActivity);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, HeroDataHelper &hero) noexcept
{
    qint16 ii;
    quint8 n;

    stream>>hero.name;

    stream>>hero.baseAttributesValues;

    stream>>hero.currentAttributesValues;

    stream>>hero.stressBorderEffects;

    stream>>n;
    hero.nature=static_cast<HeroEnums::Nature>(n);

    stream>>n;
    hero.profession=static_cast<HeroEnums::Profession>(n);

    stream>>hero.armor;

    stream>>hero.weaponsTools;

    stream>>hero.isDead;

    stream>>ii;
    hero.indexOfCurrentSBE=ii;

    stream>>ii;
    hero.noSignalDaysRemaining=ii;

    stream>>ii;
    hero.carriedEnergy=ii;

    stream>>ii;
    hero.carriedFoodSupplies=ii;

    stream>>ii;
    hero.carriedBuildingMaterials=ii;

    stream>>ii;
    hero.carriedAetheriteOre=ii;

    //TODO Mission loading

    stream>>n;
    hero.currentActivity=static_cast<HeroEnums::CurrentActivity>(n);

    return stream;
}

void HeroBuilder::resetHero() noexcept
{
    delete m_hero;
    m_hero=new Hero;
}

void HeroBuilder::setCombatEffectiveness(int combatEffectiveness) noexcept
{
    if (combatEffectiveness>=0)
        m_hero->m_baseAttributesValues.combatEffectiveness=combatEffectiveness;
}

void HeroBuilder::setProficiency(int proficiency) noexcept
{
    if (proficiency>=0)
        m_hero->m_baseAttributesValues.proficiency=proficiency;
}

void HeroBuilder::setCleverness(int cleverness) noexcept
{
    if (cleverness>=0)
        m_hero->m_baseAttributesValues.cleverness=cleverness;
}

void HeroBuilder::setLuck(float luck) noexcept
{
    if (luck>=0 && luck<=1)
        m_hero->m_baseAttributesValues.luck=luck;
}

void HeroBuilder::setHealth(int health) noexcept
{
    if (health>=0)
        m_hero->m_currentAttributesValues.health=health;
}

void HeroBuilder::setHealthLimit(int healthLimit) noexcept
{
    if (healthLimit>0)
        m_hero->m_baseAttributesValues.healthLimit=healthLimit;
}

void HeroBuilder::setDailyHealthRecovery(int dailyHealthRecovery) noexcept
{
    m_hero->m_baseAttributesValues.dailyHealthRecovery=dailyHealthRecovery;
}

void HeroBuilder::setStress(int stress) noexcept
{
    if (stress>=0)
        m_hero->m_currentAttributesValues.stress=stress;
}

void HeroBuilder::setStressResistance(float stressResistance) noexcept
{
    if (stressResistance>=0)
        m_hero->m_baseAttributesValues.stressResistance=stressResistance;
}

void HeroBuilder::setStressLimit(int stressLimit) noexcept
{
    if (stressLimit!=0)
        m_hero->m_baseAttributesValues.stressLimit=stressLimit;
}

void HeroBuilder::setStressBorder(int stressBorder) noexcept
{
    if (stressBorder>=0)
        m_hero->m_baseAttributesValues.stressBorder=stressBorder;
}

void HeroBuilder::setDailyStressRecovery(int dailyStressRecovery) noexcept
{
    m_hero->m_baseAttributesValues.dailyStressRecovery=dailyStressRecovery;
}

void HeroBuilder::setSalary(int salary) noexcept
{
    m_hero->m_baseAttributesValues.salary=salary;
}

void HeroBuilder::setDailyFoodConsumption(int dailyFoodConsumption) noexcept
{
    if (dailyFoodConsumption>=0)
        m_hero->m_baseAttributesValues.dailyFoodConsumption=dailyFoodConsumption;
}

void HeroBuilder::setAndEquipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept
{
    if (slot<m_hero->amountOfWeaponToolSlots())
        m_hero->equipWeaponTool(weaponTool,slot);
}

void HeroBuilder::setCarriedEnergy(int amount) noexcept
{
    if (amount >= 0)
        m_hero->m_carriedEnergy=amount;
}

void HeroBuilder::setCarriedFoodSupplies(int amount) noexcept
{
    if (amount >= 0)
        m_hero->m_carriedFoodSupplies=amount;
}

void HeroBuilder::setCarriedBuildingMaterials(int amount) noexcept
{
    if (amount >= 0)
        m_hero->m_carriedBuildingMaterials=amount;
}

void HeroBuilder::setCarriedAetheriteOre(int amount) noexcept
{
    if (amount >= 0)
        m_hero->m_carriedAetheriteOre=amount;
}

HeroesContainer::HeroesContainer(Base *base) noexcept
    : m_preparedHero(nullptr), m_basePtr(base)
{

}

HeroesContainer::~HeroesContainer() noexcept
{

}

bool HeroesContainer::prepareHeroAt(unsigned index) noexcept
{
    if (index >= m_heroes.size())
        return 0;
    m_preparedHero=m_heroes[index];
    return 1;
}

void HeroesContainer::addHero(Hero *hero) noexcept
{
    m_heroes+=hero;
    connectHeroToBanSystem(hero->name());
}

void HeroesContainer::removeHero(unsigned index) noexcept
{
    if (index < m_heroes.size())
    {
        if (m_heroes[index]->currentActivity() == HeroEnums::CA_InHospital)
            m_basePtr->hospital()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_OnTrainingGround)
            m_basePtr->trainingGround()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InGym)
            m_basePtr->gym()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InLaboratory)
            m_basePtr->laboratory()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InPlayingField)
            m_basePtr->playingField()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InBar)
            m_basePtr->bar()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InShrine)
            m_basePtr->shrine()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_InSeclusion)
            m_basePtr->seclusion()->removeHero(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_Arriving)
            m_basePtr->dockingStation()->cancelHeroArrival(m_heroes[index]->name());
        else if (m_heroes[index]->currentActivity() == HeroEnums::CA_OnMission)
            ;//TODO missions
        Game::gameInstance()->assetsPool().unloadHero(m_heroes[index]->name());
        m_heroes.remove(index);
    }
}

int HeroesContainer::findHero(const QString &name) const noexcept
{
    for (int i=0;i<m_heroes.size();++i)
        if (m_heroes[i]->name() == name)
            return i;
    return -1;
}

void HeroesContainer::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    disconnectHeroFromBanSystem(name);
    Game::gameInstance()->addDoStBan(name,daysAmount);
    removeHero(findHero(name));
}

void HeroesContainer::addDoStBan(QString name, HeroEnums::DyingReason) noexcept
{
    addDoStBan(name,-1/*that's unsigned so yeah...*/);
}

void HeroesContainer::connectHeroToBanSystem(const QString &name) noexcept
{
    connect(m_heroes[findHero(name)],SIGNAL(died(QString,HeroEnums::DyingReason)),this,SLOT(addDoStBan(QString,HeroEnums::DyingReason)));
    connect(m_heroes[findHero(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}

void HeroesContainer::disconnectHeroFromBanSystem(const QString &name) noexcept
{
    disconnect(m_heroes[findHero(name)],SIGNAL(died(QString,HeroEnums::DyingReason)),this,SLOT(addDoStBan(QString,HeroEnums::DyingReason)));
    disconnect(m_heroes[findHero(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}
