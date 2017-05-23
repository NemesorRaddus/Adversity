#include "hero.h"

#include "game.h"

#include <QDebug>

HeroEnums::Nature HeroEnums::fromQStringToNatureEnum(const QString &nature) noexcept
{
    if (nature == "Active")
        return HeroEnums::N_Active;
    if (nature == "Convivial")
        return HeroEnums::N_Convivial;
    if (nature == "Religious")
        return HeroEnums::N_Religious;
    if (nature == "Recluse")
        return HeroEnums::N_Recluse;
}

QString HeroEnums::fromNatureEnumToQString(HeroEnums::Nature nature) noexcept
{
    if (nature == HeroEnums::N_Active)
        return "Active";
    if (nature == HeroEnums::N_Convivial)
        return "Convivial";
    if (nature == HeroEnums::N_Religious)
        return "Religious";
    if (nature == HeroEnums::N_Recluse)
        return "Recluse";
}

HeroEnums::StressBorderEffect HeroEnums::fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept
{
    if (stressBorderEffect == "None")
        return HeroEnums::SBE_None;
    if (stressBorderEffect == "Faint")
        return HeroEnums::SBE_Faint;
    if (stressBorderEffect == "Desertion")
        return HeroEnums::SBE_Desertion;
    if (stressBorderEffect == "Fear")
        return HeroEnums::SBE_Fear;
    if (stressBorderEffect == "Rage")
        return HeroEnums::SBE_Rage;
    if (stressBorderEffect == "Fanatic Wrath")
        return HeroEnums::SBE_FanaticWrath;
    if (stressBorderEffect == "Paranoia")
        return HeroEnums::SBE_Paranoia;
    if (stressBorderEffect == "Bravery")
        return HeroEnums::SBE_Bravery;
    if (stressBorderEffect == "Hopeless")
        return HeroEnums::SBE_Hopeless;
    if (stressBorderEffect == "Confusion")
        return HeroEnums::SBE_Confusion;
}

QString HeroEnums::fromStressBorderEffectEnumToQString(HeroEnums::StressBorderEffect stressBorderEffect) noexcept
{
    if (stressBorderEffect == HeroEnums::SBE_None)
        return "None";
    if (stressBorderEffect == HeroEnums::SBE_Faint)
        return "Faint";
    if (stressBorderEffect == HeroEnums::SBE_Desertion)
        return "Desertion";
    if (stressBorderEffect == HeroEnums::SBE_Fear)
        return "Fear";
    if (stressBorderEffect == HeroEnums::SBE_Rage)
        return "Rage";
    if (stressBorderEffect == HeroEnums::SBE_FanaticWrath)
        return "Fanatic Wrath";
    if (stressBorderEffect == HeroEnums::SBE_Paranoia)
        return "Paranoia";
    if (stressBorderEffect == HeroEnums::SBE_Bravery)
        return "Bravery";
    if (stressBorderEffect == HeroEnums::SBE_Hopeless)
        return "Hopeless";
    if (stressBorderEffect == HeroEnums::SBE_Confusion)
        return "Confusion";
}

HeroEnums::Attribute HeroEnums::fromQStringToAttributeEnum(const QString &attribute) noexcept
{
    if (attribute == "Combat Effectiveness")
        return HeroEnums::A_CombatEffectiveness;
    if (attribute == "Proficiency")
        return HeroEnums::A_Proficiency;
    if (attribute == "Cleverness")
        return HeroEnums::A_Cleverness;
    if (attribute == "Luck")
        return HeroEnums::A_Luck;
    if (attribute == "Health")
        return HeroEnums::A_Health;
    if (attribute == "Health Limit")
        return HeroEnums::A_HealthLimit;
    if (attribute == "Daily Health Recovery")
        return HeroEnums::A_DailyHealthRecovery;
    if (attribute == "Stress")
        return HeroEnums::A_Stress;
    if (attribute == "Stress Resistance")
        return HeroEnums::A_StressResistance;
    if (attribute == "Stress Limit")
        return HeroEnums::A_StressLimit;
    if (attribute == "Stress Border")
        return HeroEnums::A_StressBorder;
    if (attribute == "Daily Stress Recovery")
        return HeroEnums::A_DailyStressRecovery;
    if (attribute == "Salary")
        return HeroEnums::A_Salary;
    if (attribute == "Daily Food Consumption")
        return HeroEnums::A_DailyFoodConsumption;
}

QString HeroEnums::fromAttributeEnumToQString(HeroEnums::Attribute attribute) noexcept
{
    if (attribute == HeroEnums::A_CombatEffectiveness)
        return "Combat Effectiveness";
    if (attribute == HeroEnums::A_Proficiency)
        return "Proficiency";
    if (attribute == HeroEnums::A_Cleverness)
        return "Cleverness";
    if (attribute == HeroEnums::A_Luck)
        return "Luck";
    if (attribute == HeroEnums::A_Health)
        return "Health";
    if (attribute == HeroEnums::A_HealthLimit)
        return "Health Limit";
    if (attribute == HeroEnums::A_DailyHealthRecovery)
        return "Daily Health Recovery";
    if (attribute == HeroEnums::A_Stress)
        return "Stress";
    if (attribute == HeroEnums::A_StressResistance)
        return "Stress Resistance";
    if (attribute == HeroEnums::A_StressLimit)
        return "Stress Limit";
    if (attribute == HeroEnums::A_StressBorder)
        return "Stress Border";
    if (attribute == HeroEnums::A_DailyStressRecovery)
        return "Daily Stress Recovery";
    if (attribute == HeroEnums::A_Salary)
        return "Salary";
    if (attribute == HeroEnums::A_DailyFoodConsumption)
        return "Daily Food Consumption";
}

QDataStream &HeroStressBorderEffect::read(QDataStream &stream) noexcept
{
    quint8 n;
    QVector <QVariant> vd;

    stream>>n;
    effectName = static_cast<HeroEnums::StressBorderEffect>(n);

    stream>>vd;
    effectParams.resize(vd.size());
    for (int i=0;i<vd.size();++i)
        effectParams[i]=vd[i];

    return stream;
}

QDataStream &HeroStressBorderEffect::write(QDataStream &stream) const noexcept
{
    QVector <QVariant> vd;

    stream<<static_cast<quint8>(effectName);

    vd.resize(effectParams.size());
    for (int i=0;i<effectParams.size();++i)
        vd[i]=effectParams[i];
    stream<<vd;

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

void Hero::changeCombatEffectiveness(int amount) noexcept
{
    if (m_baseAttributesValues.combatEffectiveness+amount >= 0)
        m_baseAttributesValues.combatEffectiveness+=amount;
    else
        m_baseAttributesValues.combatEffectiveness=0;

    calculateCurrentAttributeValue(HeroEnums::A_CombatEffectiveness);
}

void Hero::changeProficiency(int amount) noexcept
{
    if (m_baseAttributesValues.proficiency+amount >= 0)
        m_baseAttributesValues.proficiency+=amount;
    else
        m_baseAttributesValues.proficiency=0;

    calculateCurrentAttributeValue(HeroEnums::A_Proficiency);
}

void Hero::changeCleverness(int amount) noexcept
{
    if (m_baseAttributesValues.cleverness+amount >= 0)
        m_baseAttributesValues.cleverness+=amount;
    else
        m_baseAttributesValues.cleverness=0;

    calculateCurrentAttributeValue(HeroEnums::A_Cleverness);
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
    if (m_currentAttributesValues.stress+amount*m_currentAttributesValues.stressResistance>=m_currentAttributesValues.stressLimit)
    {
        m_currentAttributesValues.stress=m_currentAttributesValues.stressLimit;
        die(HeroEnums::DR_StressLimitAchieved);
    }
    else if (m_currentAttributesValues.stress + amount * m_currentAttributesValues.stressResistance >= m_currentAttributesValues.stressBorder && !m_isStressBorderEffectActive)
    {
        m_currentAttributesValues.stress+=amount*m_currentAttributesValues.stressResistance;
        activateStressBorderEffect();
    }
    else
        m_currentAttributesValues.stress+=amount*m_currentAttributesValues.stressResistance;
}

void Hero::decreaseStress(unsigned amount) noexcept
{
    if (m_currentAttributesValues.stress-amount<m_currentAttributesValues.stressBorder && m_isStressBorderEffectActive)
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

void Hero::changeStressResistance(float amount) noexcept
{
    if (m_currentAttributesValues.stressResistance+amount>=0)
        m_currentAttributesValues.stressResistance+=amount;
}

void Hero::changeStressLimit(int amount) noexcept
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

void Hero::changeStressBorder(int amount) noexcept
{
    if (m_baseAttributesValues.stressBorder+amount<1)
        m_baseAttributesValues.stressBorder=0;
    else
        m_baseAttributesValues.stressBorder+=amount;

    calculateCurrentAttributeValue(HeroEnums::A_StressBorder);

    if (m_currentAttributesValues.stress<m_currentAttributesValues.stressBorder && m_isStressBorderEffectActive)
        deactivateStressBorderEffect();
    else if (m_currentAttributesValues.stress>=m_currentAttributesValues.stressBorder && !m_isStressBorderEffectActive)
        activateStressBorderEffect();
}

void Hero::changeDailyStressRecovery(int amount) noexcept
{
    m_baseAttributesValues.dailyStressRecovery+=amount;

    calculateCurrentAttributeValue(HeroEnums::A_DailyStressRecovery);
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

void Hero::equipArmor(Equipment *armor) noexcept
{
    if (armor!=NULL)
    {
        if (m_armor!=NULL)
            unequipArmor();

        applyEquipmentEffect();
        setArmor(armor);
    }
}

void Hero::unequipArmor() noexcept
{
    if (m_armor!=NULL)
    {
        unapplyEquipmentEffect();
        setArmor(NULL);
    }
}

void Hero::equipWeaponTool(Equipment *weaponTool, int slot) noexcept
{
    if (weaponTool!=NULL && slot>=0 && slot<m_amountOfWeaponToolSlots)
    {
        if (m_weaponsTools[slot]!=NULL)
            unequipWeaponTool(slot);

        applyEquipmentEffect();
        setWeaponTool(weaponTool,slot);
    }
}

void Hero::unequipWeaponTool(int slot) noexcept
{
    if (slot>=0 && slot<m_amountOfWeaponToolSlots && m_weaponsTools[slot]!=NULL)
    {
        unapplyEquipmentEffect();
        setWeaponTool(NULL,slot);
    }
}

Hero::Hero() noexcept
    : m_stressBorderEffect({HeroEnums::SBE_None,{}}), m_nature(HeroEnums::N_Active), m_armor(NULL), m_isDead(0), m_isStressBorderEffectActive(0), m_noSignalDaysRemaining(0), m_carriedEnergy(0), m_carriedFoodSupplies(0), m_carriedBuildingMaterials(0), m_carriedAetheriteOre(0), m_assignedMission(NULL), m_currentActivity(HeroEnums::CA_Idle)
{
    m_weaponsTools.reserve(2);
    m_weaponsTools.push_back(NULL);
    m_weaponsTools.push_back(NULL);
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

void Hero::setCurrentActivity(HeroEnums::CurrentActivity activity) noexcept
{
    m_currentActivity=activity;
    if (activity==HeroEnums::CA_OnMission)
        m_assignedMission=NULL;
}

QDataStream &Hero::read(QDataStream &stream) noexcept
{
    qint16 ii;
    quint8 n;
    QString s;
    QVector <QString> vs;

    stream>>m_name;

    stream>>m_baseAttributesValues;

    stream>>m_currentAttributesValues;

    stream>>m_stressBorderEffect;

    stream>>n;
    m_nature=static_cast<HeroEnums::Nature>(n);

    stream>>s;
    if (!s.isEmpty())
    {
        for (int i=0;i<Game::gameInstance()->assetsPool().equipment().size();++i)
            if (Game::gameInstance()->assetsPool().equipment()[i]->name() == s)
            {
                equipArmor(EquipmentBuilder::copyEquipment(Game::gameInstance()->assetsPool().equipment()[i]));
                break;
            }
    }

    stream>>vs;
    for (int i=0;i<vs.size() && i<m_amountOfWeaponToolSlots;++i)
    {
        if (!vs[i].isEmpty())
        {
            for (int j=0;j<Game::gameInstance()->assetsPool().equipment().size();++j)
                if (Game::gameInstance()->assetsPool().equipment()[j]->name() == s)
                {
                    equipWeaponTool(EquipmentBuilder::copyEquipment(Game::gameInstance()->assetsPool().equipment()[j]),i);
                    break;
                }
        }
    }

    stream>>m_isDead;

    stream>>m_isStressBorderEffectActive;

    stream>>ii;
    m_noSignalDaysRemaining=ii;

    stream>>ii;
    m_carriedEnergy=ii;

    stream>>ii;
    m_carriedFoodSupplies=ii;

    stream>>ii;
    m_carriedBuildingMaterials=ii;

    stream>>ii;
    m_carriedAetheriteOre=ii;

    //TODO Mission loading

    stream>>n;
    m_currentActivity=static_cast<HeroEnums::CurrentActivity>(n);

    return stream;
}

QDataStream &Hero::write(QDataStream &stream) const noexcept
{
    stream<<m_name;

    stream<<m_baseAttributesValues;

    stream<<m_currentAttributesValues;

    stream<<m_stressBorderEffect;

    stream<<static_cast<quint8>(m_nature);

    if (m_armor!=NULL)
        stream<<m_armor->name();
    else
        stream<<QString("");

    QVector <QString> vs;
    for (int i=0;i<m_weaponsTools.size();++i)
    {
        if (m_weaponsTools[i]!=NULL)
            vs.push_back(m_weaponsTools[i]->name());
        else
            vs.push_back("");
    }
    stream<<vs;

    stream<<m_isDead;

    stream<<m_isStressBorderEffectActive;

    stream<<static_cast<qint16>(m_noSignalDaysRemaining);

    stream<<static_cast<qint16>(m_carriedEnergy);

    stream<<static_cast<qint16>(m_carriedFoodSupplies);

    stream<<static_cast<qint16>(m_carriedBuildingMaterials);

    stream<<static_cast<qint16>(m_carriedAetheriteOre);

    //TODO Mission saving

    stream<<static_cast<quint8>(m_currentActivity);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const Hero &hero) noexcept
{
    return hero.write(stream);
}

QDataStream &operator>>(QDataStream &stream, Hero &hero) noexcept
{
    return hero.read(stream);
}

void Hero::setNoSignalDaysRemaining(int noSignalDaysRemaining) noexcept
{
    m_noSignalDaysRemaining = noSignalDaysRemaining;
}

void Hero::setIsDead(bool isDead) noexcept
{
    m_isDead = isDead;
}

void Hero::setName(const QString &name) noexcept
{
    m_name=name;
}

void Hero::setStressBorderEffect(const HeroStressBorderEffect &stressBorderEffect) noexcept
{
    m_stressBorderEffect=stressBorderEffect;
}

void Hero::setNature(HeroEnums::Nature nature) noexcept
{
    m_nature=nature;
}

void Hero::activateStressBorderEffect() noexcept
{
    m_isStressBorderEffectActive=1;
    calculateCurrentAttributeValues();
}

void Hero::deactivateStressBorderEffect() noexcept
{
    m_isStressBorderEffectActive=0;
    calculateCurrentAttributeValues();
}

void Hero::die(HeroEnums::DyingReason reason) noexcept
{
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
        if (m_isStressBorderEffectActive && m_stressBorderEffect.effectName!=HeroEnums::SBE_None)
            x+=m_stressBorderEffect.effectParams[2].toInt();
        if (m_armor!=NULL)
            x+=m_armor->clevernessBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->clevernessBonus();

        if (x>0)
            m_currentAttributesValues.cleverness=x;
        else
            m_currentAttributesValues.cleverness=0;
    }
    else if (attributeName == HeroEnums::A_CombatEffectiveness)
    {
        int x=m_baseAttributesValues.combatEffectiveness;
        if (m_isStressBorderEffectActive && m_stressBorderEffect.effectName!=HeroEnums::SBE_None)
            x+=m_stressBorderEffect.effectParams[0].toInt();
        if (m_armor!=NULL)
            x+=m_armor->combatEffectivenessBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->combatEffectivenessBonus();

        if (x>0)
            m_currentAttributesValues.combatEffectiveness=x;
        else
            m_currentAttributesValues.combatEffectiveness=0;
    }
    else if (attributeName == HeroEnums::A_DailyFoodConsumption)
    {
        int x=m_baseAttributesValues.dailyFoodConsumption;
        if (m_armor!=NULL)
            x+=m_armor->dailyFoodConsumptionBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->dailyFoodConsumptionBonus();

        if (x>0)
            m_currentAttributesValues.dailyFoodConsumption=x;
        else
            m_currentAttributesValues.dailyFoodConsumption=0;
    }
    else if (attributeName == HeroEnums::A_DailyHealthRecovery)
    {
        int x=m_baseAttributesValues.dailyHealthRecovery;
        if (m_armor!=NULL)
            x+=m_armor->dailyHealthRecoveryBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->dailyHealthRecoveryBonus();

        if (x>0)
            m_currentAttributesValues.dailyHealthRecovery=x;
        else
            m_currentAttributesValues.dailyHealthRecovery=0;
    }
    else if (attributeName == HeroEnums::A_DailyStressRecovery)
    {
        int x=m_baseAttributesValues.dailyStressRecovery;
        if (m_armor!=NULL)
            x+=m_armor->dailyStressRecoveryBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->dailyStressRecoveryBonus();

        if (x>0)
            m_currentAttributesValues.dailyStressRecovery=x;
        else
            m_currentAttributesValues.dailyStressRecovery=0;
    }
    else if (attributeName == HeroEnums::A_HealthLimit)
    {
        int x=m_baseAttributesValues.healthLimit;
        if (m_armor!=NULL)
            x+=m_armor->healthLimitBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->healthLimitBonus();

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
        if (m_isStressBorderEffectActive && m_stressBorderEffect.effectName==HeroEnums::SBE_Hopeless)
            x+=m_stressBorderEffect.effectParams[4].toFloat();
        if (m_armor!=NULL)
            x+=m_armor->luckBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->luckBonus();

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
        if (m_isStressBorderEffectActive && m_stressBorderEffect.effectName!=HeroEnums::SBE_None)
            x+=m_stressBorderEffect.effectParams[1].toInt();
        if (m_armor!=NULL)
            x+=m_armor->proficiencyBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->proficiencyBonus();

        if (x>0)
            m_currentAttributesValues.proficiency=x;
        else
            m_currentAttributesValues.proficiency=0;
    }
    else if (attributeName == HeroEnums::A_Salary)
    {
        int x=m_baseAttributesValues.salary;
        if (m_armor!=NULL)
            x+=m_armor->salaryBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->salaryBonus();

        if (x>0)
            m_currentAttributesValues.salary=x;
        else
            m_currentAttributesValues.salary=0;
    }
    else if (attributeName == HeroEnums::A_StressBorder)
    {
        int x=m_baseAttributesValues.stressBorder;
        if (m_armor!=NULL)
            x+=m_armor->stressBorderBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->stressBorderBonus();

        if (x>0)
            m_currentAttributesValues.stressBorder=x;
        else
            m_currentAttributesValues.stressBorder=0;

        if (!m_isStressBorderEffectActive && m_currentAttributesValues.stress>=m_currentAttributesValues.stressBorder)
            activateStressBorderEffect();
        if (m_isStressBorderEffectActive && m_currentAttributesValues.stress<m_currentAttributesValues.stressBorder)
            deactivateStressBorderEffect();
    }
    else if (attributeName == HeroEnums::A_StressLimit)
    {
        int x=m_baseAttributesValues.stressLimit;
        if (m_armor!=NULL)
            x+=m_armor->stressLimitBonus();
        for (int i=0;i<m_amountOfWeaponToolSlots;++i)
            if (m_weaponsTools[i]!=NULL)
                x+=m_weaponsTools[i]->stressLimitBonus();

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
            if (m_isStressBorderEffectActive && m_stressBorderEffect.effectName!=HeroEnums::SBE_None)
                x+=m_stressBorderEffect.effectParams[3].toFloat();
            if (m_armor!=NULL)
                x+=m_armor->stressResistanceBonus();
            for (int i=0;i<m_amountOfWeaponToolSlots;++i)
                if (m_weaponsTools[i]!=NULL)
                    x+=m_weaponsTools[i]->stressResistanceBonus();

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
    calculateCurrentAttributeValue(HeroEnums::A_DailyStressRecovery);
    calculateCurrentAttributeValue(HeroEnums::A_HealthLimit);
    calculateCurrentAttributeValue(HeroEnums::A_Luck);
    calculateCurrentAttributeValue(HeroEnums::A_Proficiency);
    calculateCurrentAttributeValue(HeroEnums::A_Salary);
    calculateCurrentAttributeValue(HeroEnums::A_StressBorder);
    calculateCurrentAttributeValue(HeroEnums::A_StressLimit);
    calculateCurrentAttributeValue(HeroEnums::A_StressResistance);
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
    Hero *r=m_hero;
    m_hero=new Hero;
    return r;
}

void HeroBuilder::resetHero() noexcept
{
    delete m_hero;
    m_hero=new Hero;
}

HeroesContainer::HeroesContainer() noexcept
    : m_preparedHero(NULL)
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
}

void HeroesContainer::removeHero(unsigned index) noexcept
{
    if (index < m_heroes.size())
    {
        m_heroes.remove(index);
    }
}
