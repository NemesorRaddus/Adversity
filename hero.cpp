#include "hero.h"

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

}

QString HeroEnums::fromAttributeEnumToQString(HeroEnums::Attribute attribute) noexcept
{

}

const QString &Hero::stressBorderEffectString() const noexcept
{

}

const QString &Hero::natureString() const noexcept
{

}

void Hero::setCombatEffectiveness(int combatEffectiveness) noexcept
{
    if (combatEffectiveness>=0)
        m_combatEffectiveness=combatEffectiveness;
    else
        m_combatEffectiveness=0;
}

void Hero::setProficiency(int proficiency) noexcept
{
    if (proficiency>=0)
        m_proficiency=proficiency;
    else
        m_proficiency=0;
}

void Hero::setCleverness(int cleverness) noexcept
{
    if (cleverness>=0)
        m_cleverness=cleverness;
    else
        m_cleverness=0;
}

void Hero::setLuck(float luck) noexcept
{
    m_luck=luck;
}

void Hero::setHealth(int health) noexcept
{
    if (health>=0)
    {
        if (health<=m_healthLimit)
            m_health=health;
        else
            m_health=m_healthLimit;
    }
    else
        m_health=0;
}

void Hero::setHealthLimit(int healthLimit) noexcept
{
    if (healthLimit>0)
    {
        m_healthLimit=healthLimit;
        if (m_health>m_healthLimit)
            m_health=m_healthLimit;
    }
    else
    {
        m_healthLimit=1;
        if (m_health>1)
            m_health=1;
    }
}

void Hero::setDailyHealthRecovery(int dailyHealthRecovery) noexcept
{
    m_dailyHealthRecovery=dailyHealthRecovery;
}

void Hero::setStress(int stress) noexcept
{
    if (stress>=0)
    {
        m_stress=stress;
        //if (stress>=)
    }
    else
        m_stress=0;
}

void Hero::setStressResistance(float stressResistance) noexcept
{
    m_stressResistance=stressResistance;
}

void Hero::setStressLimit(int stressLimit) noexcept
{
    if (stressLimit>0)
    {
        m_stressLimit=stressLimit;
        if (m_stress>m_stressLimit)
            m_stress=m_stressLimit;
    }
    else
    {
        m_stressLimit=1;
        if (m_stress>1)
            m_stress=1;
    }
}

void Hero::setStressBorder(int stressBorder) noexcept
{
    if (stressBorder<0)//TODO activate effect
        stressBorder=0;
    else
    {
        if (stressBorder<m_stressLimit)
            m_stressBorder=stressBorder;
        else
            m_stressBorder=m_stressLimit;
    }
}

void Hero::setDailyStressRecovery(int dailyStressRecovery) noexcept
{
    m_dailyStressRecovery=dailyStressRecovery;
}

void Hero::setSalary(int salary) noexcept
{
    m_salary=salary;
}

void Hero::setDailyFoodConsumption(int dailyFoodConsumption) noexcept
{
    m_dailyFoodConsumption=dailyFoodConsumption;
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

Hero::Hero() noexcept
{

}

void Hero::setID(unsigned id) noexcept
{
    if (id!=0)
        m_id=id;
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
    qreal d;
    quint8 n;

    stream>>m_name;

    stream>>ii;
    m_combatEffectiveness=ii;

    stream>>ii;
    m_proficiency=ii;

    stream>>ii;
    m_cleverness=ii;

    stream>>d;
    m_luck=d;

    stream>>ii;
    m_health=ii;

    stream>>ii;
    m_healthLimit=ii;

    stream>>ii;
    m_dailyHealthRecovery=ii;

    stream>>ii;
    m_stress=ii;

    stream>>d;
    m_stressResistance=d;

    stream>>ii;
    m_stressLimit=ii;

    stream>>ii;
    m_stressBorder=ii;

    //stream>>m_stressBorderEffect;//TODO make overload

    stream>>ii;
    m_dailyStressRecovery=ii;

    stream>>ii;
    m_salary=ii;

    stream>>ii;
    m_dailyFoodConsumption=ii;

    stream>>n;
    m_nature=static_cast<HeroEnums::Nature>(n);

//do eq load and finish this f

    return stream;
}

QDataStream &Hero::write(QDataStream &stream) const noexcept
{


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
    //TODO
}

void Hero::deactivateStressBorderEffect() noexcept
{
    //TODO
}

void Hero::die(HeroEnums::DyingReason reason) noexcept
{

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
    for (int i=0;i<m_heroes.size();++i)
        delete m_heroes[i];
}

bool HeroesContainer::prepareHeroAt(unsigned id) noexcept
{
    int index=findHero(id);
    if (index == -1)
        return 0;
    m_preparedHero=m_heroes[index];
    return 1;
}

unsigned HeroesContainer::availableID() const noexcept
{
    if (m_heroes.isEmpty())
        return 1;
    else
        return m_heroes.last()->id() + 1;
}

void HeroesContainer::addHero(Hero *hero) noexcept
{
    m_heroes+=hero;
}

void HeroesContainer::removeHero(unsigned id) noexcept
{
    int index=findHero(id);
    if (index != -1)
    {
        delete m_heroes[index];
        m_heroes.remove(index);
    }
}

int HeroesContainer::findHero(unsigned id) const noexcept
{
    for (int i=0;i<m_heroes.size();++i)
        if (m_heroes[i]->id() == id)
            return i;
    return -1;
}
