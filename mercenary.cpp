#include "mercenary.h"

#include "game.h"

#include <QDebug>

MercenaryEnums::Nature MercenaryEnums::fromQStringToNatureEnum(const QString &nature) noexcept
{
    if (nature == "Active")
        return N_Active;
    if (nature == "Convivial")
        return N_Convivial;
    if (nature == "Religious")
        return N_Religious;
    if (nature == "Recluse")
        return N_Recluse;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Nature enum conversion failed for {}",nature.toStdString());
}

QString MercenaryEnums::fromNatureEnumToQString(MercenaryEnums::Nature nature) noexcept
{
    if (nature == N_Active)
        return "Active";
    if (nature == N_Convivial)
        return "Convivial";
    if (nature == N_Religious)
        return "Religious";
    if (nature == N_Recluse)
        return "Recluse";
    Game::gameInstance()->loggers()->mainLogger()->warn("Nature enum->QString conversion failed for {}",static_cast<unsigned>(nature));
}

MercenaryEnums::StressBorderEffect MercenaryEnums::fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept
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
    if (stressBorderEffect == "Stone Skin")
        return SBE_StoneSkin;
    if (stressBorderEffect == "Multitasking")
        return SBE_Multitasking;
    if (stressBorderEffect == "Equilibrium")
        return SBE_Equilibrium;
    if (stressBorderEffect == "Stress Resistant")
        return SBE_StressResistant;
    if (stressBorderEffect == "The Lucky One")
        return SBE_TheLuckyOne;
    if (stressBorderEffect == "Doombringer")
        return SBE_Doombringer;
    if (stressBorderEffect == "Excellence")
        return SBE_Excellence;
    if (stressBorderEffect == "Absolute")
        return SBE_Absolute;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->StressBorderEffect enum conversion failed for {}",stressBorderEffect.toStdString());
}

QString MercenaryEnums::fromStressBorderEffectEnumToQString(MercenaryEnums::StressBorderEffect stressBorderEffect) noexcept
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
        return "Stress Resistant";
    if (stressBorderEffect == SBE_TheLuckyOne)
        return "The Lucky One";
    if (stressBorderEffect == SBE_Doombringer)
        return "Doombringer";
    if (stressBorderEffect == SBE_Excellence)
        return "Excellence";
    if (stressBorderEffect == SBE_Absolute)
        return "Absolute";
    Game::gameInstance()->loggers()->mainLogger()->warn("StressBorderEffect enum->QString conversion failed for {}",static_cast<unsigned>(stressBorderEffect));
}

MercenaryEnums::Attribute MercenaryEnums::fromQStringToAttributeEnum(const QString &attribute) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Attribute enum conversion failed for {}",attribute.toStdString());
}

QString MercenaryEnums::fromAttributeEnumToQString(MercenaryEnums::Attribute attribute) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("Attribute enum->QString conversion failed for {}",static_cast<unsigned>(attribute));
}

MercenaryEnums::CurrentActivity MercenaryEnums::fromQStringToCurrentActivityEnum(const QString &currentActivity) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->CurrentActivity enum conversion failed for {}",currentActivity.toStdString());
}

QString MercenaryEnums::fromCurrentActivityEnumToQString(MercenaryEnums::CurrentActivity currentActivity) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("CurrentActivity enum->QString conversion failed for {}",static_cast<unsigned>(currentActivity));
}

MercenaryEnums::Profession MercenaryEnums::fromQStringToProfessionEnum(const QString &profession) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Profession enum conversion failed for {}",profession.toStdString());
}

QString MercenaryEnums::fromProfessionEnumToQString(MercenaryEnums::Profession profession) noexcept
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
    Game::gameInstance()->loggers()->mainLogger()->warn("Profession enum->QString conversion failed for {}",static_cast<unsigned>(profession));
}

QDataStream &MercenaryStressBorderEffect::read(QDataStream &stream) noexcept
{
    quint8 n;

    stream>>n;
    effectName = static_cast<MercenaryEnums::StressBorderEffect>(n);

    return stream;
}

QDataStream &MercenaryStressBorderEffect::write(QDataStream &stream) const noexcept
{
    stream<<static_cast<quint8>(effectName);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const MercenaryStressBorderEffect &effect) noexcept
{
    return effect.write(stream);
}

QDataStream &operator>>(QDataStream &stream, MercenaryStressBorderEffect &effect) noexcept
{
    return effect.read(stream);
}

QDataStream &operator<<(QDataStream &stream, const MercenaryAttributesSet &attrs) noexcept
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

QDataStream &operator>>(QDataStream &stream, MercenaryAttributesSet &attrs) noexcept
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

const MercenaryStressBorderEffect *Mercenary::currentSBE() const noexcept
{
    return m_indexOfCurrentSBE==-1 ? nullptr : &(m_stressBorderEffects[m_indexOfCurrentSBE]);
}

QString Mercenary::currentStressBorderEffectNameString() const noexcept
{
    if (m_indexOfCurrentSBE!=-1)
        return MercenaryEnums::fromStressBorderEffectEnumToQString(m_stressBorderEffects[m_indexOfCurrentSBE].effectName);
    return "";
}

QVector<QPair<MercenaryStressBorderEffect, unsigned> > Mercenary::diverseSBEs() const noexcept
{
    QVector<QPair<MercenaryStressBorderEffect, unsigned> > r;
    for (int i=0;i<m_stressBorderEffects.size();++i)
    {
        bool done=0;
        for (int j=0;j<r.size();++j)
            if (m_stressBorderEffects[i].effectName == r[j].first.effectName)
            {
                done=1;
                ++r[j].second;
                break;
            }
        if (!done)
            r+={m_stressBorderEffects[i],1};
    }
    return r;
}

int Mercenary::amountOfDiverseSBEs() const noexcept
{
    return diverseSBEs().size();
}

QString Mercenary::nameOfSBESummed(unsigned index) const noexcept
{
    auto sbes=diverseSBEs();
    if (index<sbes.size())
        return MercenaryEnums::fromStressBorderEffectEnumToQString(sbes[index].first.effectName);
    return "";
}

float Mercenary::chanceOfSBESummed(unsigned index) const noexcept
{
    auto sbes=diverseSBEs();
    if (index<sbes.size())
        return static_cast<float>(sbes[index].second)/static_cast<float>(m_stressBorderEffects.size());
    return 0;
}

QString Mercenary::natureString() const noexcept
{
    return MercenaryEnums::fromNatureEnumToQString(m_nature);
}

QString Mercenary::professionString() const noexcept
{
    return MercenaryEnums::fromProfessionEnumToQString(m_profession);
}

bool Mercenary::canTrainCombatEffectiveness() const noexcept
{
    return m_stockCE + 5 > m_baseAttributesValues.combatEffectiveness;
}

bool Mercenary::canTrainProficiency() const noexcept
{
    return m_stockPR + 5 > m_baseAttributesValues.proficiency;
}

bool Mercenary::canTrainCleverness() const noexcept
{
    return m_stockCL + 5 > m_baseAttributesValues.cleverness;
}

void Mercenary::trainCombatEffectiveness() noexcept
{
    if (m_baseAttributesValues.combatEffectiveness > 7)
    {
        changeProficiency(-1);
        changeCleverness(-1);
    }
    else if (m_baseAttributesValues.combatEffectiveness > 4)
        changeCleverness(-1);

    changeCombatEffectiveness(1);
}

void Mercenary::trainProficiency() noexcept
{
    if (m_baseAttributesValues.proficiency > 7)
    {
        changeCombatEffectiveness(-1);
        changeCleverness(-1);
    }
    else if (m_baseAttributesValues.proficiency > 4)
        changeCombatEffectiveness(-1);

    changeProficiency(1);
}

void Mercenary::trainCleverness() noexcept
{
    if (m_baseAttributesValues.cleverness > 7)
    {
        changeProficiency(-1);
        changeCombatEffectiveness(-1);
    }
    else if (m_baseAttributesValues.cleverness > 4)
        changeProficiency(-1);

    changeCleverness(1);
}

void Mercenary::changeCombatEffectiveness(int amount) noexcept
{
    if (m_baseAttributesValues.combatEffectiveness+amount >= 0)
        m_baseAttributesValues.combatEffectiveness+=amount;
    else
        m_baseAttributesValues.combatEffectiveness=0;

    calculateCurrentAttributeValues();
}

void Mercenary::changeProficiency(int amount) noexcept
{
    if (m_baseAttributesValues.proficiency+amount >= 0)
        m_baseAttributesValues.proficiency+=amount;
    else
        m_baseAttributesValues.proficiency=0;

    calculateCurrentAttributeValues();
}

void Mercenary::changeCleverness(int amount) noexcept
{
    if (m_baseAttributesValues.cleverness+amount >= 0)
        m_baseAttributesValues.cleverness+=amount;
    else
        m_baseAttributesValues.cleverness=0;

    calculateCurrentAttributeValues();
}

void Mercenary::changeLuck(float amount) noexcept
{
    if (m_baseAttributesValues.luck+amount < 0)
        m_baseAttributesValues.luck=0;
    else
        m_baseAttributesValues.luck+=amount;

    calculateCurrentAttributeValue(MercenaryEnums::A_Luck);
}

void Mercenary::changeHealth(int amount) noexcept
{
    if (m_currentAttributesValues.health + amount > 0)
    {
        if (m_currentAttributesValues.health+amount<m_currentAttributesValues.healthLimit)
            m_currentAttributesValues.health+=amount;
        else
            m_currentAttributesValues.health=m_currentAttributesValues.healthLimit;
    }
    else
    {
        if (isStressBorderEffectActive() && m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Bravery && 10 >= Randomizer::randomBetweenAAndB(1,100))
        {
            m_currentAttributesValues.health=1;
            m_carriedAetheriteOre=0;
            m_carriedBuildingMaterials=0;
            m_carriedEnergy=0;
            m_carriedFoodSupplies=0;
        }
        else
        {
            m_currentAttributesValues.health=0;
            die();
        }
    }
}

void Mercenary::changeHealthLimit(int amount) noexcept
{
    if (m_currentAttributesValues.healthLimit+amount > 0)
        m_currentAttributesValues.healthLimit+=amount;
    else
        m_currentAttributesValues.healthLimit=1;

    calculateCurrentAttributeValue(MercenaryEnums::A_HealthLimit);
}

void Mercenary::changeDailyHealthRecovery(int amount) noexcept
{
    m_baseAttributesValues.dailyHealthRecovery+=amount;

    calculateCurrentAttributeValue(MercenaryEnums::A_DailyHealthRecovery);
}

void Mercenary::increaseStress(unsigned amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stress+amount*m_currentAttributesValues.stressResistance>=m_currentAttributesValues.stressLimit)
        {
            m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
            die();
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

void Mercenary::decreaseStress(unsigned amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stress-amount<m_currentAttributesValues.stressBorder && isStressBorderEffectActive())
        {
            if (m_currentAttributesValues.stress-static_cast<int>(amount)>0)
                m_currentAttributesValues.stress-=amount;
            else
                m_currentAttributesValues.stress=0;
            deactivateStressBorderEffect();
        }
        else
        {
            if (m_currentAttributesValues.stress-static_cast<int>(amount)>0)
                m_currentAttributesValues.stress-=amount;
            else
                m_currentAttributesValues.stress=0;
        }
    }
}

void Mercenary::changeStressResistance(float amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_currentAttributesValues.stressResistance+amount>=0)
            m_currentAttributesValues.stressResistance+=amount;
    }
}

void Mercenary::changeStressLimit(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_baseAttributesValues.stressLimit+amount>1)
        {
            m_baseAttributesValues.stressLimit+=amount;

            calculateCurrentAttributeValue(MercenaryEnums::A_StressLimit);

            if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressLimit)
            {
                m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
                die();
            }
        }
        else
        {
            m_baseAttributesValues.stressLimit=1;

            calculateCurrentAttributeValue(MercenaryEnums::A_StressLimit);

            if (m_currentAttributesValues.stress>=1)
            {
                m_currentAttributesValues.stress=1;
                die();
            }
        }
    }
}

void Mercenary::changeStressBorder(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        if (m_baseAttributesValues.stressBorder+amount<1)
            m_baseAttributesValues.stressBorder=0;
        else
            m_baseAttributesValues.stressBorder+=amount;

        calculateCurrentAttributeValue(MercenaryEnums::A_StressBorder);

        if (m_currentAttributesValues.stress<m_currentAttributesValues.stressBorder && isStressBorderEffectActive())
            deactivateStressBorderEffect();
        else if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressBorder && !isStressBorderEffectActive())
            activateStressBorderEffect();
    }
}

void Mercenary::changeDailyStressRecovery(int amount) noexcept
{
    if (!isImmuneToStress())
    {
        m_baseAttributesValues.dailyStressRecovery+=amount;

        calculateCurrentAttributeValue(MercenaryEnums::A_DailyStressRecovery);
    }
}

void Mercenary::changeSalary(int amount) noexcept
{
    m_baseAttributesValues.salary+=amount;

    calculateCurrentAttributeValue(MercenaryEnums::A_Salary);
}

void Mercenary::changeDailyFoodConsumption(int amount) noexcept
{
    if (m_baseAttributesValues.dailyFoodConsumption+amount>=0)
        m_baseAttributesValues.dailyFoodConsumption+=amount;
    else
        m_baseAttributesValues.dailyFoodConsumption=0;

    calculateCurrentAttributeValue(MercenaryEnums::A_DailyFoodConsumption);
}

void Mercenary::setDailyHealthRecoveryBuildingBonus(int bonus) noexcept
{
    m_dhrBuildingBonus=bonus;
    calculateCurrentAttributeValue(MercenaryEnums::A_DailyHealthRecovery);
}

void Mercenary::setDailyStressRecoveryBuildingBonus(int bonus) noexcept
{
    m_dsrBuildingBonus=bonus;
    calculateCurrentAttributeValue(MercenaryEnums::A_DailyStressRecovery);
}

void Mercenary::addAttributeModification(AttributeModification *mod) noexcept
{
    m_attributeModifications+=mod;
    switch (mod->attribute)
    {
    case MercenaryEnums::A_CombatEffectiveness:
        [[fallthrough]];
    case MercenaryEnums::A_Proficiency:
        [[fallthrough]];
    case MercenaryEnums::A_Cleverness:
        calculateCurrentAttributeValues();
        break;
    default:
        calculateCurrentAttributeValue(mod->attribute);
        break;
    }
}

void Mercenary::decrementModificationsDuration() noexcept
{
    for (int i=0;i<m_attributeModifications.size();)
    {
        if (m_attributeModifications[i]->duration > 1)
        {
            --m_attributeModifications[i]->duration;
            ++i;
        }
        else if (m_attributeModifications[i]->duration == 1)
        {
            delete m_attributeModifications[i];
            m_attributeModifications.remove(i);
        }
        else
            ++i;
    }
}

const Equipment *Mercenary::weaponTool(unsigned slot) const noexcept
{
    return m_weaponsTools.value(slot,nullptr);
}

bool Mercenary::hasWeaponToolInSlot(unsigned slot) const noexcept
{
    if (slot>=m_amountOfWeaponToolSlots)
        return 0;
    return m_weaponsTools[slot]!=nullptr;
}

void Mercenary::prepareWeaponTool(unsigned slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots)
        m_preparedWeaponTool=m_weaponsTools[slot];
}

void Mercenary::equipArmor(Equipment *armor) noexcept
{
    if (armor!=nullptr)
    {
        if (m_armor!=nullptr)
            unequipArmor();

        setArmor(armor);
        applyEquipmentEffect();
    }
}

void Mercenary::unequipArmor() noexcept
{
    if (m_armor!=nullptr)
    {
        addCarriedEquipment(m_armor);
        setArmor(nullptr);
        applyEquipmentEffect();
    }
}

void Mercenary::equipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept
{
    if (weaponTool!=nullptr && slot<m_amountOfWeaponToolSlots)
    {
        if (m_weaponsTools[slot]!=nullptr)
            unequipWeaponTool(slot);

        setWeaponTool(weaponTool,slot);
        applyEquipmentEffect();
    }
}

void Mercenary::unequipWeaponTool(unsigned slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots && m_weaponsTools[slot]!=nullptr)
    {
        addCarriedEquipment(m_weaponsTools[slot]);
        setWeaponTool(nullptr,slot);
        applyEquipmentEffect();
    }
}

void Mercenary::removeArmor() noexcept
{
    if (m_armor!=nullptr)
    {
        setArmor(nullptr);
        applyEquipmentEffect();
    }
}

void Mercenary::removeWeaponTool(unsigned slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots && m_weaponsTools[slot]!=nullptr)
    {
        setWeaponTool(nullptr,slot);
        applyEquipmentEffect();
    }
}

QVector<EquipmentEnums::Category> Mercenary::currentEquipmentCategories() const noexcept
{
    return m_currentEquipmentCategories;
}

bool Mercenary::hasEquipmentFromCategory(EquipmentEnums::Category cat) const noexcept
{
    return m_currentEquipmentCategories.contains(cat);
}

void Mercenary::addCarriedEquipment(Equipment *eq) noexcept
{
    if (eq!=nullptr)
        m_carriedEquipment+=eq;
}

QVector<Equipment *> Mercenary::carriedEquipment() const noexcept
{
    return m_carriedEquipment;
}

void Mercenary::clearCarriedEquipment() noexcept
{
    m_carriedEquipment.clear();
}

void Mercenary::prepareCarriedEquipmentAt(unsigned index) noexcept
{
    if (index<m_carriedEquipment.size())
        m_preparedCarriedEquipment=m_carriedEquipment[index];
}

unsigned Mercenary::dailyEquipmentCostEnergy() noexcept
{
    unsigned r=0;
    if (m_armor != nullptr)
        r+=m_armor->maintenanceEnergyCost();
    for (int i=0;i<m_amountOfWeaponToolSlots;++i)
        if (m_weaponsTools[i] != nullptr)
            r+=m_weaponsTools[i]->maintenanceEnergyCost();
    return r;
}

unsigned Mercenary::dailyEquipmentCostBM() noexcept
{
    unsigned r=0;
    if (m_armor != nullptr)
        r+=m_armor->maintenanceBuildingMaterialsCost();
    for (int i=0;i<m_amountOfWeaponToolSlots;++i)
        if (m_weaponsTools[i] != nullptr)
            r+=m_weaponsTools[i]->maintenanceBuildingMaterialsCost();
    return r;
}

void Mercenary::setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept
{
    if (m_noSignalDaysRemaining == noSignalDaysRemaining)
        return;

    if (noSignalDaysRemaining == 0)
    {
        m_noSignalDaysRemaining = 0;
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}]{}: signal retrieved",m_base->gameClock()->currentTime().toQString().toStdString(),m_name.toStdString());
        if (m_assignedMission==nullptr || isDead())
            return;//safety measure
        addWaitingReport(new UnifiedReport(new SignalRetrievedReport(pathToArt(), m_assignedMission->land()->name(), m_base->gameClock()->currentTime())));
        sendWaitingReports();
        sendWaitingDBEntries();
    }
    else
    {
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}]{}: signal lost or still off",m_base->gameClock()->currentTime().toQString().toStdString(),m_name.toStdString());
        if (m_assignedMission!=nullptr && isCommunicationAvailable())
            m_base->addReport(new UnifiedReport(new SignalLostReport(pathToArt(), name(), m_assignedMission->land()->name(), m_base->gameClock()->currentTime())));
        m_noSignalDaysRemaining = noSignalDaysRemaining;
    }
}

Mercenary::Mercenary(Base *base) noexcept
    : m_base(base), m_stockCE(0), m_stockPR(0), m_stockCL(0), m_nature(MercenaryEnums::N_Active), m_armor(nullptr), m_preparedWeaponTool(nullptr), m_preparedCarriedEquipment(nullptr), m_isEquipmentActive(1), m_dhrBuildingBonus(0), m_dsrBuildingBonus(0), m_isDead(0), m_indexOfCurrentSBE(-1), m_noSignalDaysRemaining(0), m_carriedEnergy(0), m_carriedFoodSupplies(0), m_carriedBuildingMaterials(0), m_carriedAetheriteOre(0), m_noSalaryWeeks(0), m_assignedMission(nullptr), m_currentActivity(MercenaryEnums::CA_Idle)
{
    m_stressBorderEffects.reserve(1);
    m_stressBorderEffects.push_back({MercenaryEnums::SBE_None});
    
    m_weaponsTools.reserve(2);
    m_weaponsTools.push_back(nullptr);
    m_weaponsTools.push_back(nullptr);
}

void Mercenary::setCarriedEnergy(int carriedEnergy) noexcept
{
    if (carriedEnergy >= 0)
        m_carriedEnergy = carriedEnergy;
}

void Mercenary::setCarriedFoodSupplies(int carriedFoodSupplies) noexcept
{
    if (carriedFoodSupplies >= 0)
        m_carriedFoodSupplies = carriedFoodSupplies;
}

void Mercenary::setCarriedBuildingMaterials(int carriedBuildingMaterials) noexcept
{
    if (carriedBuildingMaterials >= 0)
        m_carriedBuildingMaterials = carriedBuildingMaterials;
}

void Mercenary::setCarriedAetheriteOre(int carriedAetheriteOre) noexcept
{
    if (carriedAetheriteOre >= 0)
        m_carriedAetheriteOre = carriedAetheriteOre;
}

void Mercenary::assignMission(Mission *mission) noexcept
{
    m_assignedMission=mission;
    m_currentActivity=MercenaryEnums::CA_OnMission;
    if (mission != nullptr)
        m_lastKnownLandName=mission->land()->name();
}

void Mercenary::trySendingReport(UnifiedReport *report, bool registerInMission) noexcept
{
    if (isCommunicationAvailable())
    {
        m_base->addReport(report);
        if (registerInMission)
            m_base->registerLatestReportInMission(m_assignedMission);
    }
    else
        addWaitingReport(report);
}

void Mercenary::addWaitingReport(UnifiedReport *report) noexcept
{
    m_waitingReports+=report;
}

void Mercenary::sendWaitingReports() noexcept
{
    for (auto &e : m_waitingReports)
    {
        m_base->addReport(e);
        m_base->registerLatestReportInMission(m_assignedMission);
    }
    m_waitingReports.clear();
}

void Mercenary::addWaitingDBEntry(const QString &entryName) noexcept
{
    m_waitingDBEntries+=entryName;
}

void Mercenary::sendWaitingDBEntries() noexcept
{
    for (const auto &e : m_waitingDBEntries)
        if (m_base->database()->isEntryUnlocked(e,m_lastKnownLandName))
            m_base->database()->unlockEntry(e,m_lastKnownLandName);
    m_waitingDBEntries.clear();
}

QString Mercenary::currentActivityString() const noexcept
{
    return MercenaryEnums::fromCurrentActivityEnumToQString(m_currentActivity);
}

void Mercenary::setCurrentActivity(MercenaryEnums::CurrentActivity activity) noexcept
{
    m_currentActivity=activity;
    if (activity==MercenaryEnums::CA_OnMission)
        m_assignedMission=nullptr;
}

QString Mercenary::pathToArt() const noexcept
{
    return "qrc:/graphics/Mercs/"+Global::alterNormalTextToInternal(professionString())+"/"+Global::alterNormalTextToInternal(name())+".png";
}

void Mercenary::dismiss(unsigned banDays) noexcept
{
    emit ranAway(name(),banDays);
}

void Mercenary::handleNewDay() noexcept
{
    if (!m_isDead)
    {
        handleSBEAtDayEnd();
        if (!m_isDead)
        {
            handleHunger();
            if (!m_isDead)
            {
                handleEquipmentCosts();
                handleRegeneration();
                decrementModificationsDuration();
            }
        }
    }
}

void Mercenary::handleNewWeek() noexcept
{
    if (!m_isDead)
        handleSalary();
}

void Mercenary::returnToBase() noexcept
{
    Game::gameInstance()->loggers()->mercenariesLogger()->trace("{} has returned to base",m_name.toStdString());
    m_base->increaseAetheriteAmount(m_carriedAetheriteOre);
    m_base->increaseBuildingMaterialsAmount(m_carriedBuildingMaterials);
    m_base->increaseEnergyAmount(m_carriedEnergy);
    m_base->increaseFoodSuppliesAmount(m_carriedFoodSupplies);

    m_carriedAetheriteOre=0;
    m_carriedBuildingMaterials=0;
    m_carriedEnergy=0;
    m_carriedFoodSupplies=0;

    for (auto &e : m_carriedEquipment)
        m_base->availableEquipment() += e;

    m_carriedEquipment.clear();

    if (m_armor!=nullptr)
        m_base->availableEquipment() += m_armor;
    for (auto &e : m_weaponsTools)
        if (e!=nullptr)
            m_base->availableEquipment() += e;

    m_armor = nullptr;
    m_weaponsTools.fill(nullptr);
    m_currentEquipmentCategories.clear();
    m_preparedWeaponTool=nullptr;
    m_isEquipmentActive = false;

    m_assignedMission = nullptr;
    m_currentActivity = MercenaryEnums::CA_Idle;
    m_noSignalDaysRemaining = 0;

    sendWaitingReports();
    sendWaitingDBEntries();

    calculateCurrentAttributeValues();
}

void Mercenary::die(bool playerKnowsIt, bool showNotification) noexcept
{
    Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}]{} died",m_base->gameClock()->currentTime().toQString().toStdString(),m_name.toStdString());
    m_isDead=1;
    m_currentAttributesValues.health=0;
    if (m_currentActivity != MercenaryEnums::CA_OnMission || playerKnowsIt)
    {
        if (showNotification)
            m_base->addReport(new UnifiedReport(new MercenaryDeathReport(pathToArt(),name(),m_base->gameClock()->currentTime())));
        m_noSignalDaysRemaining=-1;
        emit died(name());
    }
    else
        becomeMIA();
}

void Mercenary::becomeMIA() noexcept
{
    if (m_currentActivity==MercenaryEnums::CA_OnMission && m_assignedMission!=nullptr)
    {
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}]{} became MIA",m_base->gameClock()->currentTime().toQString().toStdString(),m_name.toStdString());
        if (isCommunicationAvailable())
            m_base->addReport(new UnifiedReport(new SignalLostReport(pathToArt(),name(),m_assignedMission->land()->name(),m_base->gameClock()->currentTime())));
        m_noSignalDaysRemaining=-1;
        m_assignedMission->forceEndSilently();
    }
}

void Mercenary::activateStressBorderEffect() noexcept
{
    if (!isImmuneToStress())
    {
        m_indexOfCurrentSBE = Randomizer::randomBetweenAAndB(0,m_stressBorderEffects.size()-1);
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("SBE activated for {}: {}",m_name.toStdString(),static_cast<unsigned>(m_stressBorderEffects[m_indexOfCurrentSBE].effectName));

        if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Consciousness)
        {
            m_carriedBuildingMaterials = 0;
        }

        calculateCurrentAttributeValues();
    }
}

void Mercenary::deactivateStressBorderEffect() noexcept
{
    if (!isImmuneToStress())
    {
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("SBE deactivated for {}",m_name.toStdString());
        m_indexOfCurrentSBE = -1;

        calculateCurrentAttributeValues();
    }
}

void Mercenary::setArmor(Equipment *armor) noexcept
{
    m_armor=armor;
}

void Mercenary::setWeaponTool(Equipment *weaponTool, int slot) noexcept
{
    if (slot<m_amountOfWeaponToolSlots)
        m_weaponsTools[slot]=weaponTool;
}

void Mercenary::applyEquipmentEffect() noexcept
{
    calculateCurrentAttributeValues();
}

void Mercenary::calculateCurrentAttributeValue(MercenaryEnums::Attribute attributeName) noexcept
{
    if (attributeName == MercenaryEnums::A_Cleverness)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Cleverness && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.cleverness = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.cleverness;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Cleverness)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Cleverness)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Faint)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_FanaticWrath)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Rage)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Consciousness)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Caution)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Awareness)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Bravery)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Doombringer)
                x+=4;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_CombatEffectiveness)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_CombatEffectiveness && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.combatEffectiveness = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.combatEffectiveness;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_CombatEffectiveness)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_CombatEffectiveness)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Faint)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Fear)
                x-=3;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_FanaticWrath)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Confusion)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Rage)
                x+=4;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Restive)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Consciousness)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Caution)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Awareness)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Bravery)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Doombringer)
                x+=6;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_DailyFoodConsumption)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyFoodConsumption && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.dailyFoodConsumption = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.dailyFoodConsumption;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyFoodConsumption)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyFoodConsumption)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Awareness)
                x+=1;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_DailyHealthRecovery)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyHealthRecovery && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.dailyHealthRecovery = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.dailyHealthRecovery;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyHealthRecovery)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyHealthRecovery)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        x+=m_dhrBuildingBonus;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_StoneSkin)
                x-=5;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_DailyStressRecovery)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyStressRecovery && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.dailyStressRecovery = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.dailyStressRecovery;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyStressRecovery)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_DailyStressRecovery)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        x+=m_dsrBuildingBonus;
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_FanaticWrath)
                x+=10;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Doombringer)
                x+=10;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_HealthLimit)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_HealthLimit && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.healthLimit = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.healthLimit;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_HealthLimit)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_HealthLimit)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_StoneSkin)
                x+=10;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_Luck)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Luck && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.luck = e->value.toFloat();
                return;
            }
        float x=m_baseAttributesValues.luck;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Luck)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toFloat();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toFloat();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Luck)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toFloat();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toFloat();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Hopeless)
                x-=0.35;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_TheLuckyOne)
                x+=1;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
        {
            if (m_armor!=nullptr)
                x+=m_armor->luckBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=nullptr)
                    x+=m_weaponsTools[i]->luckBonus();
        }

        if (x<0)
            m_currentAttributesValues.luck=0;
        else
            m_currentAttributesValues.luck=x;
    }
    else if (attributeName == MercenaryEnums::A_Proficiency)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Proficiency && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.proficiency = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.proficiency;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Proficiency)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Proficiency)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Faint)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_FanaticWrath)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Confusion)
                x-=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Abandonce)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Rage)
                x-=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Caution)
                x+=2;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Bravery)
                x+=1;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Doombringer)
                x+=4;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_Salary)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Salary && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.salary = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.salary;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Salary)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_Salary)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_StressBorder)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressBorder && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.stressBorder = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.stressBorder;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressBorder)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressBorder)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_StressResistant)
                x-=30;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
    else if (attributeName == MercenaryEnums::A_StressLimit)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressLimit && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.stressLimit = e->value.toInt();
                return;
            }
        int x=m_baseAttributesValues.stressLimit;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressLimit)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toInt();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toInt();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressLimit)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toInt();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toInt();
            }
        if (isStressBorderEffectActive())
        {
            if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Abandonce)
                x-=30;
            else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_StressResistant)
                x+=30;
        }
        if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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
            die();
        }
    }
    else if (attributeName == MercenaryEnums::A_StressResistance)
    {
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressResistance && e->type == AttributeModification::T_Set)
            {
                m_currentAttributesValues.stressResistance = e->value.toFloat();
                return;
            }
        float x=m_baseAttributesValues.stressResistance;
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressResistance)
            {
                if (e->type == AttributeModification::T_Multiply)
                    x *= e->value.toFloat();
                else if (e->type == AttributeModification::T_Divide)
                    x /= e->value.toFloat();
            }
        for (auto e : m_attributeModifications)
            if (e->attribute == MercenaryEnums::A_StressResistance)
            {
                if (e->type == AttributeModification::T_Add)
                    x += e->value.toFloat();
                else if (e->type == AttributeModification::T_Subtract)
                    x -= e->value.toFloat();
            }

        if (x==-1)//special value, N/A
            m_currentAttributesValues.stressResistance=-1;
        else
        {
            if (isStressBorderEffectActive())
            {
                if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Faint)
                    x+=0.2;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Paranoia)
                    x+=0.5;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Rage)
                    x-=0.3;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Restive)
                    x+=0.1;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Consciousness)
                    x-=0.2;
                else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Absolute)
                    x+=0.2;
            }
            if ((!isStressBorderEffectActive() || m_stressBorderEffects[m_indexOfCurrentSBE].effectName != MercenaryEnums::SBE_Madness) && isEquipmentActive())
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

void Mercenary::calculateCurrentAttributeValues() noexcept
{
    calculateCurrentAttributeValue(MercenaryEnums::A_Cleverness);
    calculateCurrentAttributeValue(MercenaryEnums::A_CombatEffectiveness);
    calculateCurrentAttributeValue(MercenaryEnums::A_DailyFoodConsumption);
    calculateCurrentAttributeValue(MercenaryEnums::A_DailyHealthRecovery);
    if (!isImmuneToStress())
    {
        calculateCurrentAttributeValue(MercenaryEnums::A_DailyStressRecovery);
        calculateCurrentAttributeValue(MercenaryEnums::A_StressBorder);
        calculateCurrentAttributeValue(MercenaryEnums::A_StressLimit);
        calculateCurrentAttributeValue(MercenaryEnums::A_StressResistance);
    }
    calculateCurrentAttributeValue(MercenaryEnums::A_HealthLimit);
    calculateCurrentAttributeValue(MercenaryEnums::A_Luck);
    calculateCurrentAttributeValue(MercenaryEnums::A_Proficiency);
    calculateCurrentAttributeValue(MercenaryEnums::A_Salary);

    if (isStressBorderEffectActive())//calculate those effect results which are more "meta"-like
    {
        if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Stupor)
        {
            int minVal = qMin(m_currentAttributesValues.combatEffectiveness, qMin(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness));

            m_currentAttributesValues.combatEffectiveness = minVal;
            m_currentAttributesValues.proficiency = minVal;
            m_currentAttributesValues.cleverness = minVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Equilibrium)
        {
            int minVal = qMin(m_currentAttributesValues.combatEffectiveness, qMin(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness)) + 1;

            m_currentAttributesValues.combatEffectiveness = minVal;
            m_currentAttributesValues.proficiency = minVal;
            m_currentAttributesValues.cleverness = minVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Excellence)
        {
            int maxVal = qMax(m_currentAttributesValues.combatEffectiveness, qMax(m_currentAttributesValues.proficiency, m_currentAttributesValues.cleverness));

            m_currentAttributesValues.combatEffectiveness = maxVal;
            m_currentAttributesValues.proficiency = maxVal;
            m_currentAttributesValues.cleverness = maxVal;
        }
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Absolute)
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
        else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Multitasking)
        {
            int val = (m_currentAttributesValues.combatEffectiveness+m_currentAttributesValues.proficiency+m_currentAttributesValues.cleverness)/3;

            m_currentAttributesValues.combatEffectiveness=val;
            m_currentAttributesValues.proficiency=val;
            m_currentAttributesValues.cleverness=val;
        }
    }
}

void Mercenary::sumEquipmentCategories() noexcept
{
    m_currentEquipmentCategories.clear();
    if (m_armor!=nullptr)
        m_currentEquipmentCategories=m_armor->categories();
    for (int i=0;i<m_weaponsTools.size();++i)
        if (m_weaponsTools[i]!=nullptr)
            for (int j=0;j<m_weaponsTools[j]->categories().size();++j)
                if (!m_currentEquipmentCategories.contains(m_weaponsTools[i]->categories()[j]))
                    m_currentEquipmentCategories+=m_weaponsTools[i]->categories()[j];
}

void Mercenary::setAttributeValue(MercenaryEnums::Attribute attrName, QVariant val) noexcept
{
    switch (attrName) {
    case MercenaryEnums::A_Cleverness:
        m_currentAttributesValues.cleverness=val.toInt();
        break;
    case MercenaryEnums::A_CombatEffectiveness:
        m_currentAttributesValues.combatEffectiveness=val.toInt();
        break;
    case MercenaryEnums::A_DailyFoodConsumption:
        m_currentAttributesValues.dailyFoodConsumption=val.toInt();
        break;
    case MercenaryEnums::A_DailyHealthRecovery:
        m_currentAttributesValues.dailyHealthRecovery=val.toInt();
        break;
    case MercenaryEnums::A_DailyStressRecovery:
        m_currentAttributesValues.dailyStressRecovery=val.toInt();
        break;
    case MercenaryEnums::A_Health:
        m_currentAttributesValues.health=val.toInt();
        break;
    case MercenaryEnums::A_HealthLimit:
        m_currentAttributesValues.healthLimit=val.toInt();
        break;
    case MercenaryEnums::A_Luck:
        m_currentAttributesValues.luck=val.toFloat();
        break;
    case MercenaryEnums::A_Proficiency:
        m_currentAttributesValues.proficiency=val.toInt();
        break;
    case MercenaryEnums::A_Salary:
        m_currentAttributesValues.salary=val.toInt();
        break;
    case MercenaryEnums::A_Stress:
        m_currentAttributesValues.stress=val.toInt();
        break;
    case MercenaryEnums::A_StressBorder:
        m_currentAttributesValues.stressBorder=val.toInt();
        break;
    case MercenaryEnums::A_StressLimit:
        m_currentAttributesValues.stressLimit=val.toInt();
        break;
    case MercenaryEnums::A_StressResistance:
        m_currentAttributesValues.stressResistance=val.toFloat();
        break;
    default:
        break;
    }
}

void Mercenary::activateEquipment() noexcept
{
    m_isEquipmentActive=1;
    calculateCurrentAttributeValues();
}

void Mercenary::deactivateEquipment() noexcept
{
    m_isEquipmentActive=0;
    calculateCurrentAttributeValues();
}

void Mercenary::handleSBEAtDayEnd()  noexcept
{
    if (!isStressBorderEffectActive())
        return;

    if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Desertion)
    {
        int chance = 100*m_currentAttributesValues.stress/m_currentAttributesValues.stressLimit;

        if (chance >= Randomizer::randomBetweenAAndB(1,100))
        {
            trySendingReport(new UnifiedReport(new DesertionReport(pathToArt(), name(), m_base->gameClock()->currentTime())), m_assignedMission!=nullptr);
            ranAway(m_name,21);
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Confusion)
    {
        if (m_currentActivity == MercenaryEnums::CA_OnMission)
        {
            if (10 >= Randomizer::randomBetweenAAndB(1,100))
            {
                if (isCommunicationAvailable())
                    m_base->addReport(new UnifiedReport(new SignalLostReport(pathToArt(), name(), m_assignedMission->land()->name(), m_base->gameClock()->currentTime())));
                m_noSignalDaysRemaining=-1;
            }
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Masochism)
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
                die();
            }
        }
    }
    else if (m_stressBorderEffects[m_indexOfCurrentSBE].effectName == MercenaryEnums::SBE_Restlessness)
    {
        increaseStress(m_currentAttributesValues.stressLimit/20);
    }
}

void Mercenary::handleEquipmentCosts() noexcept
{
    if (m_currentActivity!=MercenaryEnums::CA_OnMission)
        return;

    int energyNeeded=0, bmNeeded=0;

    if (m_armor!=nullptr)
    {
        energyNeeded+=m_armor->maintenanceEnergyCost();
        bmNeeded+=m_armor->maintenanceBuildingMaterialsCost();
    }
    for (int i=0;i<m_weaponsTools.size();++i)
        if (m_weaponsTools[i]!=nullptr)
        {
            energyNeeded+=m_weaponsTools[i]->maintenanceEnergyCost();
            bmNeeded+=m_weaponsTools[i]->maintenanceBuildingMaterialsCost();
        }

    if (energyNeeded<=m_carriedEnergy && bmNeeded<=m_carriedBuildingMaterials)
    {
        m_carriedEnergy-=energyNeeded;
        m_carriedBuildingMaterials-=bmNeeded;

        if (!isEquipmentActive())
            activateEquipment();
    }
    else if (isEquipmentActive())
        deactivateEquipment();
}

void Mercenary::handleHunger() noexcept
{
    if (m_currentActivity == MercenaryEnums::CA_OnMission)
    {
        int missingFood = dailyFoodConsumption()-carriedFoodSupplies();
        if (missingFood<=0)
            setCarriedFoodSupplies(carriedFoodSupplies()-dailyFoodConsumption());
        else
        {
            trySendingReport(new UnifiedReport(new HungerReport(pathToArt(), name(), m_base->gameClock()->currentTime())), 1);
            setCarriedFoodSupplies(0);
            changeHealth(-missingFood);
            if (!isDead())
                increaseStress(missingFood*10);
        }
    }
    else if (m_currentActivity != MercenaryEnums::CA_Arriving)
    {
        int missingFood = dailyFoodConsumption()-m_base->currentFoodSuppliesAmount();
        if (missingFood<=0)
            m_base->decreaseFoodSuppliesAmount(dailyFoodConsumption());
        else
        {
            m_base->addReport(new UnifiedReport(new HungerReport(pathToArt(), name(), m_base->gameClock()->currentTime())));
            m_base->setCurrentFoodSuppliesAmount(0);
            changeHealth(-missingFood);
            if (!isDead())
                increaseStress(missingFood*10);
        }
    }
}

void Mercenary::handleRegeneration() noexcept
{
    changeHealth(dailyHealthRecovery());
    decreaseStress(dailyStressRecovery());
}

void Mercenary::handleSalary() noexcept
{
    if (m_currentActivity != MercenaryEnums::CA_Arriving)
    {
        int missingAetherite = salary()-m_base->currentAetheriteAmount();
        if (missingAetherite<=0)
        {
            m_base->decreaseAetheriteAmount(salary());
            if (m_noSalaryWeeks>0)
                --m_noSalaryWeeks;
        }
        else
        {
            trySendingReport(new UnifiedReport(new NoSalaryReport(pathToArt(), name(), m_base->gameClock()->currentTime())), m_assignedMission!=nullptr);
            m_base->setCurrentAetheriteAmount(0);
            increaseStress(missingAetherite*3);
            if (m_noSalaryWeeks+1 == 4)
            {
                trySendingReport(new UnifiedReport(new DesertionReport(pathToArt(), name(), m_base->gameClock()->currentTime())), m_assignedMission!=nullptr);
                ranAway(m_name,21);
            }
            else
            {
                ++m_noSalaryWeeks;
                if (stress()/stressLimit()*100 >= Randomizer::randomBetweenAAndB(1,100))
                {
                    trySendingReport(new UnifiedReport(new DesertionReport(pathToArt(), name(), m_base->gameClock()->currentTime())), m_assignedMission!=nullptr);
                    ranAway(m_name,21);
                }
            }
        }
    }
}

Base *MercenaryBuilder::m_base;

MercenaryBuilder::MercenaryBuilder() noexcept
{
    m_mercenary=new Mercenary(m_base);
}

MercenaryBuilder::~MercenaryBuilder() noexcept
{
    delete m_mercenary;
}

void MercenaryBuilder::init(Base *base) noexcept
{
    m_base=base;
}

Mercenary *MercenaryBuilder::getMercenary() noexcept
{
    m_mercenary->calculateCurrentAttributeValues();
    Mercenary *r=m_mercenary;
    m_mercenary=new Mercenary(m_base);
    return r;
}

Mercenary *MercenaryBuilder::qobjectifyMercenaryData(const MercenaryDataHelper &mercenary) noexcept
{
    Mercenary *r=new Mercenary(m_base);
    r->m_name = mercenary.name;
    r->m_baseAttributesValues = mercenary.baseAttributesValues;
    r->m_currentAttributesValues = mercenary.currentAttributesValues;
    r->m_stockCE = mercenary.stockCE;
    r->m_stockPR = mercenary.stockPR;
    r->m_stockCL = mercenary.stockCL;
    r->m_stressBorderEffects = mercenary.stressBorderEffects;
    r->m_nature = mercenary.nature;
    r->m_profession = mercenary.profession;

    r->m_dhrBuildingBonus = mercenary.dhrBuildingBonus;
    r->m_dsrBuildingBonus = mercenary.dsrBuildingBonus;
    r->m_isDead = mercenary.isDead;
    r->m_indexOfCurrentSBE = mercenary.indexOfCurrentSBE;
    r->m_noSignalDaysRemaining = mercenary.noSignalDaysRemaining;
    r->m_carriedEnergy = mercenary.carriedEnergy;
    r->m_carriedFoodSupplies = mercenary.carriedFoodSupplies;
    r->m_carriedBuildingMaterials = mercenary.carriedBuildingMaterials;
    r->m_carriedAetheriteOre = mercenary.carriedAetheriteOre;
    r->m_noSalaryWeeks = mercenary.noSalaryWeeks;
    r->m_lastKnownLandName = mercenary.lastKnownLandName;
    r->m_waitingReports = mercenary.waitingReports;
    r->m_waitingDBEntries = mercenary.waitingDBEntries;
    r->m_currentActivity = mercenary.currentActivity;
    if (mercenary.currentActivity == MercenaryEnums::CA_OnMission)
    {
        if (!mercenary.armor.isEmpty())
            r->m_armor = Game::gameInstance()->assetsPool().makeEquipmentNamed(mercenary.armor);
        else
            r->m_armor = nullptr;
        for (int i=0;i<mercenary.weaponsTools.size();++i)
        {
            if (!mercenary.weaponsTools[i].isEmpty())
                r->m_weaponsTools[i]=Game::gameInstance()->assetsPool().makeEquipmentNamed(mercenary.weaponsTools[i]);
            else
                r->m_weaponsTools[i]=nullptr;
        }
        r->m_currentEquipmentCategories = mercenary.equipmentCategories;
        for (int i=0;i<mercenary.carriedEquipment.size();++i)
            r->m_carriedEquipment+=Game::gameInstance()->assetsPool().makeEquipmentNamed(mercenary.carriedEquipment[i]);
        r->m_isEquipmentActive = mercenary.isEquipmentActive;
    }
    else
        r->calculateCurrentAttributeValues();
    return r;
}

MercenaryDataHelper MercenaryBuilder::deqobjectifyMercenary(Mercenary *mercenary) noexcept
{
    MercenaryDataHelper r;

    r.name = mercenary->m_name;
    r.baseAttributesValues = mercenary->m_baseAttributesValues;
    r.currentAttributesValues = mercenary->m_currentAttributesValues;
    r.stockCE = mercenary->m_stockCE;
    r.stockPR = mercenary->m_stockPR;
    r.stockCL = mercenary->m_stockCL;
    r.stressBorderEffects = mercenary->m_stressBorderEffects;
    r.nature = mercenary->m_nature;
    r.profession = mercenary->m_profession;
    if (mercenary->m_armor != nullptr)
        r.armor = mercenary->m_armor->name();
    else
        r.armor = "";
    for (int i=0;i<mercenary->amountOfWeaponToolSlots();++i)
    {
        if (mercenary->m_weaponsTools[i] != nullptr)
            r.weaponsTools.push_back(mercenary->m_weaponsTools[i]->name());
        else
            r.weaponsTools.push_back("");
    }
    r.equipmentCategories = mercenary->m_currentEquipmentCategories;
    for (int i=0;i<mercenary->m_carriedEquipment.size();++i)
        r.carriedEquipment+=mercenary->m_carriedEquipment[i]->name();
    r.isEquipmentActive = mercenary->m_isEquipmentActive;
    r.dhrBuildingBonus = mercenary->m_dhrBuildingBonus;
    r.dsrBuildingBonus = mercenary->m_dsrBuildingBonus;
    r.isDead = mercenary->m_isDead;
    r.indexOfCurrentSBE = mercenary->m_indexOfCurrentSBE;
    r.noSignalDaysRemaining = mercenary->m_noSignalDaysRemaining;
    r.carriedEnergy = mercenary->m_carriedEnergy;
    r.carriedFoodSupplies = mercenary->m_carriedFoodSupplies;
    r.carriedBuildingMaterials = mercenary->m_carriedBuildingMaterials;
    r.carriedAetheriteOre = mercenary->m_carriedAetheriteOre;
    r.noSalaryWeeks = mercenary->m_noSalaryWeeks;
    r.lastKnownLandName = mercenary->m_lastKnownLandName;
    r.waitingReports = mercenary->m_waitingReports;
    r.waitingDBEntries = mercenary->m_waitingDBEntries;
    r.currentActivity = mercenary->m_currentActivity;

    return r;
}

QDataStream &operator<<(QDataStream &stream, const MercenaryDataHelper &mercenary) noexcept
{
    stream<<mercenary.name;

    stream<<mercenary.baseAttributesValues;

    stream<<mercenary.currentAttributesValues;

    stream<<static_cast<qint16>(mercenary.stockCE);
    stream<<static_cast<qint16>(mercenary.stockPR);
    stream<<static_cast<qint16>(mercenary.stockCL);

    stream<<mercenary.stressBorderEffects;

    stream<<static_cast<quint8>(mercenary.nature);

    stream<<static_cast<quint8>(mercenary.profession);

    stream<<mercenary.armor;

    stream<<mercenary.weaponsTools;

    QVector <quint8> cats;
    for (int i=0;i<mercenary.equipmentCategories.size();++i)
        cats+=static_cast<quint8>(mercenary.equipmentCategories[i]);
    stream<<cats;

    stream<<mercenary.carriedEquipment;

    stream<<mercenary.isEquipmentActive;

    stream<<static_cast<qint16>(mercenary.dhrBuildingBonus);
    stream<<static_cast<qint16>(mercenary.dsrBuildingBonus);

    stream<<mercenary.isDead;

    stream<<static_cast<qint16>(mercenary.indexOfCurrentSBE);

    stream<<static_cast<qint16>(mercenary.noSignalDaysRemaining);

    stream<<static_cast<qint16>(mercenary.carriedEnergy);

    stream<<static_cast<qint16>(mercenary.carriedFoodSupplies);

    stream<<static_cast<qint16>(mercenary.carriedBuildingMaterials);

    stream<<static_cast<qint16>(mercenary.carriedAetheriteOre);

    stream<<static_cast<qint16>(mercenary.noSalaryWeeks);

    stream<<mercenary.lastKnownLandName;

    QVector<QPair<Time,QString>> wrs;
    for (const auto e : mercenary.waitingReports)
        wrs+={e->time(),e->msg()};
    stream<<wrs;

    stream<<mercenary.waitingDBEntries;

    stream<<static_cast<quint8>(mercenary.currentActivity);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, MercenaryDataHelper &mercenary) noexcept
{
    qint16 ii;
    quint8 n;

    stream>>mercenary.name;

    stream>>mercenary.baseAttributesValues;

    stream>>mercenary.currentAttributesValues;

    stream>>ii;
    mercenary.stockCE=ii;

    stream>>ii;
    mercenary.stockPR=ii;

    stream>>ii;
    mercenary.stockCL=ii;

    stream>>mercenary.stressBorderEffects;

    stream>>n;
    mercenary.nature=static_cast<MercenaryEnums::Nature>(n);

    stream>>n;
    mercenary.profession=static_cast<MercenaryEnums::Profession>(n);

    stream>>mercenary.armor;

    stream>>mercenary.weaponsTools;

    QVector <quint8> cats;
    stream>>cats;
    for (int _i=0;_i<cats.size();++_i)
        mercenary.equipmentCategories+=static_cast<EquipmentEnums::Category>(cats[_i]);

    stream>>mercenary.carriedEquipment;

    stream>>mercenary.isEquipmentActive;

    stream>>ii;
    mercenary.dhrBuildingBonus=ii;

    stream>>ii;
    mercenary.dsrBuildingBonus=ii;

    stream>>mercenary.isDead;

    stream>>ii;
    mercenary.indexOfCurrentSBE=ii;

    stream>>ii;
    mercenary.noSignalDaysRemaining=ii;

    stream>>ii;
    mercenary.carriedEnergy=ii;

    stream>>ii;
    mercenary.carriedFoodSupplies=ii;

    stream>>ii;
    mercenary.carriedBuildingMaterials=ii;

    stream>>ii;
    mercenary.carriedAetheriteOre=ii;

    stream>>ii;
    mercenary.noSalaryWeeks=ii;

    stream>>mercenary.lastKnownLandName;

    QVector<QPair<Time,QString>> wrs;
    stream>>wrs;
    for (const auto e : wrs)
        mercenary.waitingReports+=new UnifiedReport{e.first,e.second};

    stream>>mercenary.waitingDBEntries;

    stream>>n;
    mercenary.currentActivity=static_cast<MercenaryEnums::CurrentActivity>(n);

    return stream;
}

void MercenaryBuilder::resetMercenary() noexcept
{
    delete m_mercenary;
    m_mercenary=new Mercenary(m_base);
}

void MercenaryBuilder::setCombatEffectiveness(int combatEffectiveness) noexcept
{
    if (combatEffectiveness>=0)
    {
        m_mercenary->m_stockCE=combatEffectiveness;
        m_mercenary->m_baseAttributesValues.combatEffectiveness=combatEffectiveness;
    }
}

void MercenaryBuilder::setProficiency(int proficiency) noexcept
{
    if (proficiency>=0)
    {
        m_mercenary->m_stockPR=proficiency;
        m_mercenary->m_baseAttributesValues.proficiency=proficiency;
    }
}

void MercenaryBuilder::setCleverness(int cleverness) noexcept
{
    if (cleverness>=0)
    {
        m_mercenary->m_stockCL=cleverness;
        m_mercenary->m_baseAttributesValues.cleverness=cleverness;
    }
}

void MercenaryBuilder::setLuck(float luck) noexcept
{
    if (luck>=0)
        m_mercenary->m_baseAttributesValues.luck=luck;
}

void MercenaryBuilder::setHealth(int health) noexcept
{
    if (health>=0)
        m_mercenary->m_currentAttributesValues.health=health;
}

void MercenaryBuilder::setHealthLimit(int healthLimit) noexcept
{
    if (healthLimit>0)
        m_mercenary->m_baseAttributesValues.healthLimit=healthLimit;
}

void MercenaryBuilder::setDailyHealthRecovery(int dailyHealthRecovery) noexcept
{
    m_mercenary->m_baseAttributesValues.dailyHealthRecovery=dailyHealthRecovery;
}

void MercenaryBuilder::setStress(int stress) noexcept
{
    if (stress>=0)
        m_mercenary->m_currentAttributesValues.stress=stress;
}

void MercenaryBuilder::setStressResistance(float stressResistance) noexcept
{
    if (stressResistance>=0)
        m_mercenary->m_baseAttributesValues.stressResistance=stressResistance;
}

void MercenaryBuilder::setStressLimit(int stressLimit) noexcept
{
    if (stressLimit!=0)
        m_mercenary->m_baseAttributesValues.stressLimit=stressLimit;
}

void MercenaryBuilder::setStressBorder(int stressBorder) noexcept
{
    if (stressBorder>=0)
        m_mercenary->m_baseAttributesValues.stressBorder=stressBorder;
}

void MercenaryBuilder::setDailyStressRecovery(int dailyStressRecovery) noexcept
{
    m_mercenary->m_baseAttributesValues.dailyStressRecovery=dailyStressRecovery;
}

void MercenaryBuilder::setSalary(int salary) noexcept
{
    m_mercenary->m_baseAttributesValues.salary=salary;
}

void MercenaryBuilder::setDailyFoodConsumption(int dailyFoodConsumption) noexcept
{
    if (dailyFoodConsumption>=0)
        m_mercenary->m_baseAttributesValues.dailyFoodConsumption=dailyFoodConsumption;
}

void MercenaryBuilder::setAndEquipWeaponTool(Equipment *weaponTool, unsigned slot) noexcept
{
    if (slot<m_mercenary->amountOfWeaponToolSlots())
        m_mercenary->equipWeaponTool(weaponTool,slot);
}

void MercenaryBuilder::setCarriedEnergy(int amount) noexcept
{
    if (amount >= 0)
        m_mercenary->m_carriedEnergy=amount;
}

void MercenaryBuilder::setCarriedFoodSupplies(int amount) noexcept
{
    if (amount >= 0)
        m_mercenary->m_carriedFoodSupplies=amount;
}

void MercenaryBuilder::setCarriedBuildingMaterials(int amount) noexcept
{
    if (amount >= 0)
        m_mercenary->m_carriedBuildingMaterials=amount;
}

void MercenaryBuilder::setCarriedAetheriteOre(int amount) noexcept
{
    if (amount >= 0)
        m_mercenary->m_carriedAetheriteOre=amount;
}

void MercenaryBuilder::setNoSalaryWeeks(unsigned amount) noexcept
{
    m_mercenary->m_noSalaryWeeks=amount;
}

MercenariesContainer::MercenariesContainer(Base *base) noexcept
    : m_preparedMercenary(nullptr), m_basePtr(base) {}

bool MercenariesContainer::prepareMercenaryAt(unsigned index) noexcept
{
    if (index >= m_mercenaries.size())
        return 0;
    m_preparedMercenary=m_mercenaries[index];
    return 1;
}

void MercenariesContainer::addMercenary(Mercenary *mercenary) noexcept
{
    m_mercenaries+=mercenary;
    connectMercenaryToBanSystem(mercenary->name());

    Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}] Mercenary added: {}",mercenary->base()->gameClock()->currentTime().toQString().toStdString(), mercenary->name().toStdString());
}

void MercenariesContainer::removeMercenary(unsigned index) noexcept
{
    if (index < m_mercenaries.size())
    {
        Game::gameInstance()->loggers()->mercenariesLogger()->trace("[{}] Removing mercenary: {}",m_mercenaries[index]->base()->gameClock()->currentTime().toQString().toStdString(), m_mercenaries[index]->name().toStdString());

        if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InHospital)
            m_basePtr->hospital()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_OnTrainingGround)
            m_basePtr->trainingGround()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InGym)
            m_basePtr->gym()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InLaboratory)
            m_basePtr->laboratory()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InPlayingField)
            m_basePtr->playingField()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InBar)
            m_basePtr->bar()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InShrine)
            m_basePtr->shrine()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InSeclusion)
            m_basePtr->seclusion()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_Arriving)
            m_basePtr->dockingStation()->cancelMercenaryArrival(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_OnMission)
        {
            auto m=m_mercenaries[index]->assignedMission();
            if (m!=nullptr)
                m->forceEndBecauseOfDeath();
        }
        Game::gameInstance()->assetsPool().unloadMercenary(m_mercenaries[index]->name());
        m_mercenaries.remove(index);
    }
}

int MercenariesContainer::findMercenary(const QString &name) const noexcept
{
    for (int i=0;i<m_mercenaries.size();++i)
        if (m_mercenaries[i]->name() == name)
            return i;
    return -1;
}

void MercenariesContainer::handleNewDay() noexcept
{
    for (auto e : m_mercenaries)
        e->handleNewDay();

    for (auto e : m_mercenaries)
        if (!e->isCommunicationAvailable())
        {
            if (!e->isDead())
                e->increaseStress(20);
            for (auto f : m_mercenaries)
                if (!f->isDead() && (f->currentActivity() != MercenaryEnums::CA_Arriving && f->currentActivity() != MercenaryEnums::CA_OnMission))
                {
                    if (e->nature() == f->nature())
                        f->increaseStress(20);
                    else
                        f->increaseStress(10);
                }
        }
}

void MercenariesContainer::handleNewWeek() noexcept
{
    for (auto e : m_mercenaries)
        e->handleNewWeek();
}

void MercenariesContainer::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    disconnectMercenaryFromBanSystem(name);
    Game::gameInstance()->addDoStBan(name,daysAmount);
    removeMercenary(findMercenary(name));
}

void MercenariesContainer::addDoStBan(QString name) noexcept
{
    auto natureOfKilledMerc = m_mercenaries[findMercenary(name)]->nature();

    addDoStBan(name,-1/*that's unsigned so yeah...*/);

    for (auto e : m_mercenaries)
        if (!e->isDead() && (e->currentActivity() != MercenaryEnums::CA_Arriving && e->currentActivity() != MercenaryEnums::CA_OnMission))
        {
            if (e->nature() == natureOfKilledMerc)
                e->increaseStress(40);
            else
                e->increaseStress(20);
        }
}

void MercenariesContainer::connectMercenaryToBanSystem(const QString &name) noexcept
{
    connect(m_mercenaries[findMercenary(name)],SIGNAL(died(QString)),this,SLOT(addDoStBan(QString)));
    connect(m_mercenaries[findMercenary(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}

void MercenariesContainer::disconnectMercenaryFromBanSystem(const QString &name) noexcept
{
    disconnect(m_mercenaries[findMercenary(name)],SIGNAL(died(QString)),this,SLOT(addDoStBan(QString)));
    disconnect(m_mercenaries[findMercenary(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}
