#include "base.h"

#include "timer.h"
#include "game.h"

#include <QDebug>

BaseEnums::Resource BaseEnums::fromQStringToResourceEnum(const QString &resource) noexcept
{
    if (resource=="Energy")
        return R_Energy;
    if (resource=="Food Supplies")
        return R_FoodSupplies;
    if (resource=="Building Materials")
        return R_BuildingMaterials;
    if (resource=="Aetherite")
        return R_AetheriteOre;
    qWarning()<<"QString->enum conversion failed for "<<resource;
}

QString BaseEnums::fromResourceEnumToQString(BaseEnums::Resource resource) noexcept
{
    if (resource==R_Energy)
        return "Energy";
    if (resource==R_FoodSupplies)
        return "Food Supplies";
    if (resource==R_BuildingMaterials)
        return "Building Materials";
    if (resource==R_AetheriteOre)
        return "Aetherite";
    qWarning()<<"enum->QString conversion failed for "<<resource;
}

BaseEnums::Building BaseEnums::fromQStringToBuildingEnum(const QString &building) noexcept
{
    if (building=="Central Unit")
        return B_CentralUnit;
    if (building=="Powerplant")
        return B_Powerplant;
    if (building=="Factory")
        return B_Factory;
    if (building=="Cool Room")
        return B_CoolRoom;
    if (building=="Storage Room")
        return B_StorageRoom;
    if (building=="Aetherite Silo")
        return B_AetheriteSilo;
    if (building=="Hospital")
        return B_Hospital;
    if (building=="Barracks")
        return B_Barracks;
    if (building=="Docking Station")
        return B_DockingStation;
    if (building=="Training Ground")
        return B_TrainingGround;
    if (building=="Gym")
        return B_Gym;
    if (building=="Laboratory")
        return B_Laboratory;
    if (building=="Playing Field")
        return B_PlayingField;
    if (building=="Bar")
        return B_Bar;
    if (building=="Shrine")
        return B_Shrine;
    if (building=="Seclusion")
        return B_Seclusion;
    qWarning()<<"QString->enum conversion failed for "<<building;
}

QString BaseEnums::fromBuildingEnumToQString(BaseEnums::Building building) noexcept
{
    if (building==B_CentralUnit)
        return "Central Unit";
    if (building==B_Powerplant)
        return "Powerplant";
    if (building==B_Factory)
        return "Factory";
    if (building==B_CoolRoom)
        return "Cool Room";
    if (building==B_StorageRoom)
        return "Storage Room";
    if (building==B_AetheriteSilo)
        return "Aetherite Silo";
    if (building==B_Hospital)
        return "Hospital";
    if (building==B_Barracks)
        return "Barracks";
    if (building==B_DockingStation)
        return "Docking Station";
    if (building==B_TrainingGround)
        return "Training Ground";
    if (building==B_Gym)
        return "Gym";
    if (building==B_Laboratory)
        return "Laboratory";
    if (building==B_PlayingField)
        return "Playing Field";
    if (building==B_Bar)
        return "Bar";
    if (building==B_Shrine)
        return "Shrine";
    if (building==B_Seclusion)
        return "Seclusion";
    qWarning()<<"enum->QString conversion failed for "<<building;
}

unsigned Building::currentLevel() const noexcept
{
    return m_base->buildingLevel(m_buildingName);
}

BuildingUpgradeRequirements Building::requirementsForNextLevel() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1);
}

unsigned Building::requirementsForNextLevelEnergy() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredEnergy;
}

unsigned Building::requirementsForNextLevelBM() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredBuildingMaterials;
}

unsigned Building::requirementsForNextLevelTime() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredTime;
}

bool Building::tryUpgrading() noexcept
{
    BuildingUpgradeRequirements reqs = requirementsForNextLevel();
    if (reqs.requiredBuildingMaterials > m_base->currentBuildingMaterialsAmount())
        return 0;
    if (reqs.requiredEnergy > m_base->currentEnergyAmount())
        return 0;

    TimerAlarm *alrm=new BuildingUpgradeTimerAlarm(m_buildingName,currentLevel()+1);
    if (m_base->gameClock()->checkIfAlarmIsSet(alrm))
    {
        delete alrm;
        return 0;
    }

    m_base->setCurrentBuildingMaterialsAmount(m_base->currentBuildingMaterialsAmount() - reqs.requiredBuildingMaterials);
    m_base->setCurrentEnergyAmount(m_base->currentEnergyAmount() - reqs.requiredEnergy);
    m_base->gameClock()->addAlarm(reqs.requiredTime,alrm);

    registerUpgradeStart();
    return 1;
}

QString Building::description() const noexcept
{
    return m_base->buildingDescription(m_buildingName);
}

Building::Building(BaseEnums::Building buildingName, Base *base, unsigned level) noexcept
    : m_buildingName(buildingName), m_base(base), m_isBeingUpgraded(0)
{
    m_base->setBuildingLevel(m_buildingName,level);
}

CentralUnit::CentralUnit(Base *base, unsigned level, const QVector<CentralUnitLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_CentralUnit, base, level), m_levelsInfo(levelsInfo){}

void CentralUnit::setLevelsInfo(const QVector<CentralUnitLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned CentralUnit::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_CentralUnit,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

Hospital::Hospital(Base *base, unsigned level, const QVector<HospitalLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Hospital, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingHealed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString Hospital::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingHealed.size() && m_heroesBeingHealed[index]!=nullptr)
        return m_heroesBeingHealed[index]->name();
    return "";
}

QString Hospital::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingHealed.size() && m_heroesBeingHealed[index]!=nullptr)
        return m_heroesBeingHealed[index]->professionString();
    return "";
}

void Hospital::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingHealed.size())
        return;

    if (m_heroesBeingHealed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingHealed[slotIndex]=base()->heroes()->getHero(pos);
    m_heroesBeingHealed[slotIndex]->setCurrentActivity(HeroEnums::CA_InHospital);
    setRecoveryValuesForHero(slotIndex);
}

void Hospital::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingHealed.size())
        return;

    if (m_heroesBeingHealed[slotIndex]==nullptr)
        return;

    m_heroesBeingHealed[slotIndex]->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingHealed[slotIndex]->setDailyHealthRecoveryBuildingBonus(0);
    m_heroesBeingHealed[slotIndex]=nullptr;
}

void Hospital::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=nullptr && m_heroesBeingHealed[i]->name() == name)
        {
            m_heroesBeingHealed[i]->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingHealed[i]=nullptr;
            break;
        }
}

int Hospital::daysToFullRecovery(const QString &name) const noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=nullptr && m_heroesBeingHealed[i]->name()==name)
            return daysToFullRecovery(i);
}

int Hospital::daysToFullRecovery(unsigned slotIndex) const noexcept
{
    if (slotIndex<m_heroesBeingHealed.size())
    {
        if (m_heroesBeingHealed[slotIndex]==nullptr)
            return -1;

        return ceil(static_cast<float>(m_heroesBeingHealed[slotIndex]->healthLimit()-m_heroesBeingHealed[slotIndex]->health())/static_cast<float>(hpRestoredPerDay()));
    }
}

void Hospital::healHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy) && base()->canDecreaseFoodSuppliesAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);
            base()->decreaseFoodSuppliesAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies);

            m_heroesBeingHealed[i]->changeHealth(m_levelsInfo.value(currentLevel()).hpRestored);
        }
}

void Hospital::setRecoveryValuesForHero(unsigned index) noexcept
{
    m_heroesBeingHealed[index]->setDailyHealthRecoveryBuildingBonus(hpRestoredPerDay());
}

void Hospital::setRecoveryValuesForHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=nullptr)
            setRecoveryValuesForHero(i);
}

void Hospital::setLevelsInfo(const QVector<HospitalLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Hospital::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Hospital,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Hospital::resizeSlotsAfterUpgrade() noexcept
{
    while (m_heroesBeingHealed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_heroesBeingHealed.push_back(nullptr);
    m_heroesBeingHealed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForHeroes();
}

TrainingGround::TrainingGround(Base *base, unsigned level, const QVector<TrainingGroundLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_TrainingGround, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill({nullptr,0},levelsInfo.value(level).amountOfSlots);
}

QString TrainingGround::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->name();
    return "";
}

QString TrainingGround::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->professionString();
    return "";
}

void TrainingGround::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingTrained[slotIndex].first=base()->heroes()->getHero(pos);
    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_OnTrainingGround);
    m_heroesBeingTrained[slotIndex].second=duration();
}

void TrainingGround::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first==nullptr)
        return;

    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingTrained[slotIndex].first=nullptr;
    m_heroesBeingTrained[slotIndex].second=0;
}

void TrainingGround::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name() == name)
        {
            m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingTrained[i].first=nullptr;
            m_heroesBeingTrained[i].second=0;
            break;
        }
}

void TrainingGround::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr)
        {
            if (m_heroesBeingTrained[i].second>0 && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
            {
                base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

                --m_heroesBeingTrained[i].second;
            }
            else if (m_heroesBeingTrained[i].second==0)
            {
                m_heroesBeingTrained[i].first->trainCombatEffectiveness();
                m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
                m_heroesBeingTrained[i].first=nullptr;
                m_heroesBeingTrained[i].second=0;
            }
        }
}

void TrainingGround::setLevelsInfo(const QVector<TrainingGroundLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned TrainingGround::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_TrainingGround,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

int TrainingGround::remainingDaysOfTraining(const QString &heroName) const noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name()==heroName)
            return m_heroesBeingTrained[i].second;
    return -1;
}

Gym::Gym(Base *base, unsigned level, const QVector<GymLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Gym, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill({nullptr,0},levelsInfo.value(level).amountOfSlots);
}

int Gym::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

QString Gym::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->name();
    return "";
}

QString Gym::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->professionString();
    return "";
}

void Gym::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingTrained[slotIndex].first=base()->heroes()->getHero(pos);
    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_InGym);
    m_heroesBeingTrained[slotIndex].second=duration();
}

void Gym::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first==nullptr)
        return;

    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingTrained[slotIndex].first=nullptr;
    m_heroesBeingTrained[slotIndex].second=0;
}

void Gym::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name() == name)
        {
            m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingTrained[i].first=nullptr;
            m_heroesBeingTrained[i].second=0;
            break;
        }
}

void Gym::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr)
        {
            if (m_heroesBeingTrained[i].second>0 && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
            {
                base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

                --m_heroesBeingTrained[i].second;
            }
            else if (m_heroesBeingTrained[i].second==0)
            {
                m_heroesBeingTrained[i].first->trainProficiency();
                m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
                m_heroesBeingTrained[i].first=nullptr;
                m_heroesBeingTrained[i].second=0;
            }
        }
}

void Gym::setLevelsInfo(const QVector<GymLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Gym::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Gym,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

int Gym::remainingDaysOfTraining(const QString &heroName) const noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name()==heroName)
            return m_heroesBeingTrained[i].second;
    return -1;
}

Laboratory::Laboratory(Base *base, unsigned level, const QVector<LaboratoryLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Laboratory, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill({nullptr,0},levelsInfo.value(level).amountOfSlots);
}

int Laboratory::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

QString Laboratory::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->name();
    return "";
}

QString Laboratory::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingTrained.size() && m_heroesBeingTrained[index].first!=nullptr)
        return m_heroesBeingTrained[index].first->professionString();
    return "";
}

void Laboratory::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingTrained[slotIndex].first=base()->heroes()->getHero(pos);
    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_InLaboratory);
    m_heroesBeingTrained[slotIndex].second=duration();
}

void Laboratory::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingTrained.size())
        return;

    if (m_heroesBeingTrained[slotIndex].first==nullptr)
        return;

    m_heroesBeingTrained[slotIndex].first->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingTrained[slotIndex].first=nullptr;
    m_heroesBeingTrained[slotIndex].second=0;
}

void Laboratory::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name() == name)
        {
            m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingTrained[i].first=nullptr;
            m_heroesBeingTrained[i].second=0;
            break;
        }
}

void Laboratory::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr)
        {
            if (m_heroesBeingTrained[i].second>0 && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
            {
                base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

                --m_heroesBeingTrained[i].second;
            }
            else if (m_heroesBeingTrained[i].second==0)
            {
                m_heroesBeingTrained[i].first->trainCleverness();
                m_heroesBeingTrained[i].first->setCurrentActivity(HeroEnums::CA_Idle);
                m_heroesBeingTrained[i].first=nullptr;
                m_heroesBeingTrained[i].second=0;
            }
        }
}

void Laboratory::setLevelsInfo(const QVector<LaboratoryLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Laboratory::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Laboratory,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

int Laboratory::remainingDaysOfTraining(const QString &heroName) const noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i].first!=nullptr && m_heroesBeingTrained[i].first->name()==heroName)
            return m_heroesBeingTrained[i].second;
    return -1;
}

PlayingField::PlayingField(Base *base, unsigned level, const QVector<PlayingFieldLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_PlayingField, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString PlayingField::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->name();
    return "";
}

QString PlayingField::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->professionString();
    return "";
}

void PlayingField::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingDestressed[slotIndex]=base()->heroes()->getHero(pos);
    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_InPlayingField);
    setRecoveryValuesForHero(slotIndex);
}

void PlayingField::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]==nullptr)
        return;

    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_heroesBeingDestressed[slotIndex]=nullptr;
}

void PlayingField::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && m_heroesBeingDestressed[i]->name() == name)
        {
            m_heroesBeingDestressed[i]->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingDestressed[i]=nullptr;
            break;
        }
}

void PlayingField::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForReligious);
        }
}

void PlayingField::setRecoveryValuesForHero(unsigned index) noexcept
{
    switch (m_heroesBeingDestressed[index]->nature())
    {
    case HeroEnums::N_Active:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case HeroEnums::N_Convivial:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case HeroEnums::N_Recluse:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case HeroEnums::N_Religious:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void PlayingField::setRecoveryValuesForHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForHero(i);
}

void PlayingField::setLevelsInfo(const QVector<PlayingFieldLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned PlayingField::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_PlayingField,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void PlayingField::resizeSlotsAfterUpgrade() noexcept
{
    while (m_heroesBeingDestressed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_heroesBeingDestressed.push_back(nullptr);
    m_heroesBeingDestressed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForHeroes();
}

Bar::Bar(Base *base, unsigned level, const QVector<BarLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Bar, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString Bar::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->name();
    return "";
}

QString Bar::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->professionString();
    return "";
}

void Bar::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingDestressed[slotIndex]=base()->heroes()->getHero(pos);
    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_InBar);
    setRecoveryValuesForHero(slotIndex);
}

void Bar::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]==nullptr)
        return;

    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_heroesBeingDestressed[slotIndex]=nullptr;
}

void Bar::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && m_heroesBeingDestressed[i]->name() == name)
        {
            m_heroesBeingDestressed[i]->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingDestressed[i]=nullptr;
            break;
        }
}

void Bar::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForReligious);
        }
}

void Bar::setRecoveryValuesForHero(unsigned index) noexcept
{
    switch (m_heroesBeingDestressed[index]->nature())
    {
    case HeroEnums::N_Active:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case HeroEnums::N_Convivial:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case HeroEnums::N_Recluse:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case HeroEnums::N_Religious:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void Bar::setRecoveryValuesForHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForHero(i);
}

void Bar::setLevelsInfo(const QVector<BarLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Bar::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Bar,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Bar::resizeSlotsAfterUpgrade() noexcept
{
    while (m_heroesBeingDestressed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_heroesBeingDestressed.push_back(nullptr);
    m_heroesBeingDestressed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForHeroes();
}

Shrine::Shrine(Base *base, unsigned level, const QVector<ShrineLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Shrine, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString Shrine::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->name();
    return "";
}

QString Shrine::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->professionString();
    return "";
}

void Shrine::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingDestressed[slotIndex]=base()->heroes()->getHero(pos);
    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_InShrine);
    setRecoveryValuesForHero(slotIndex);
}

void Shrine::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]==nullptr)
        return;

    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_heroesBeingDestressed[slotIndex]=nullptr;
}

void Shrine::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && m_heroesBeingDestressed[i]->name() == name)
        {
            m_heroesBeingDestressed[i]->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingDestressed[i]=nullptr;
            break;
        }
}

void Shrine::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForReligious);
        }
}

void Shrine::setRecoveryValuesForHero(unsigned index) noexcept
{
    switch (m_heroesBeingDestressed[index]->nature())
    {
    case HeroEnums::N_Active:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case HeroEnums::N_Convivial:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case HeroEnums::N_Recluse:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case HeroEnums::N_Religious:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void Shrine::setRecoveryValuesForHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForHero(i);
}

void Shrine::setLevelsInfo(const QVector<ShrineLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Shrine::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Shrine,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Shrine::resizeSlotsAfterUpgrade() noexcept
{
    while (m_heroesBeingDestressed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_heroesBeingDestressed.push_back(nullptr);
    m_heroesBeingDestressed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForHeroes();
}

Seclusion::Seclusion(Base *base, unsigned level, const QVector<SeclusionLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Seclusion, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString Seclusion::heroNameInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->name();
    return "";
}

QString Seclusion::heroProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_heroesBeingDestressed.size() && m_heroesBeingDestressed[index]!=nullptr)
        return m_heroesBeingDestressed[index]->professionString();
    return "";
}

void Seclusion::placeHeroInSlot(unsigned slotIndex, const QString &heroName) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->heroes()->findHero(heroName);
    if (pos==-1)
        return;

    if (base()->heroes()->getHero(pos)->currentActivity() != HeroEnums::CA_Idle)
        return;

    m_heroesBeingDestressed[slotIndex]=base()->heroes()->getHero(pos);
    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_InSeclusion);
    setRecoveryValuesForHero(slotIndex);
}

void Seclusion::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_heroesBeingDestressed.size())
        return;

    if (m_heroesBeingDestressed[slotIndex]==nullptr)
        return;

    m_heroesBeingDestressed[slotIndex]->setCurrentActivity(HeroEnums::CA_Idle);
    m_heroesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_heroesBeingDestressed[slotIndex]=nullptr;
}

void Seclusion::removeHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && m_heroesBeingDestressed[i]->name() == name)
        {
            m_heroesBeingDestressed[i]->setCurrentActivity(HeroEnums::CA_Idle);
            m_heroesBeingDestressed[i]=nullptr;
            break;
        }
}

void Seclusion::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForReligious);
        }
}

void Seclusion::setRecoveryValuesForHero(unsigned index) noexcept
{
    switch (m_heroesBeingDestressed[index]->nature())
    {
    case HeroEnums::N_Active:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case HeroEnums::N_Convivial:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case HeroEnums::N_Recluse:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case HeroEnums::N_Religious:
        m_heroesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void Seclusion::setRecoveryValuesForHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForHero(i);
}

void Seclusion::setLevelsInfo(const QVector<SeclusionLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Seclusion::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Seclusion,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Seclusion::resizeSlotsAfterUpgrade() noexcept
{
    while (m_heroesBeingDestressed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_heroesBeingDestressed.push_back(nullptr);
    m_heroesBeingDestressed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForHeroes();
}

Powerplant::Powerplant(Base *base, unsigned level, const QVector<PowerplantLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Powerplant, base, level), m_levelsInfo(levelsInfo), m_currentCycles(0)
{

}

void Powerplant::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->currentAetheriteAmount() / m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    unsigned uselessnessLimit = m_levelsInfo.value(currentLevel()).energyGiven != 0 ? (((m_levelsInfo.value(currentLevel()).energyLimit - base()->currentEnergyAmount()) / m_levelsInfo.value(currentLevel()).energyGiven) + ((m_levelsInfo.value(currentLevel()).energyLimit - base()->currentEnergyAmount()) % m_levelsInfo.value(currentLevel()).energyGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - (cyclesToDo * m_levelsInfo.value(currentLevel()).aetheriteOreTaken));
    base()->setCurrentEnergyAmount(base()->currentEnergyAmount() + (cyclesToDo * m_levelsInfo.value(currentLevel()).energyGiven));
}

void Powerplant::setCurrentCycles(unsigned amount) noexcept
{
    if (amount<=maxCycles())
        m_currentCycles=amount;
}

void Powerplant::setLevelsInfo(const QVector<PowerplantLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Powerplant::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Powerplant,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

Factory::Factory(Base *base, unsigned level, const QVector<FactoryLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Factory, base, level), m_levelsInfo(levelsInfo), m_currentCycles(0)
{

}

void Factory::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->currentAetheriteAmount() / m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    unsigned uselessnessLimit = m_levelsInfo.value(currentLevel()).buildingMaterialsGiven != 0 ? (((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) / m_levelsInfo.value(currentLevel()).buildingMaterialsGiven) + ((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) % m_levelsInfo.value(currentLevel()).buildingMaterialsGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - (cyclesToDo * m_levelsInfo.value(currentLevel()).aetheriteOreTaken));
    base()->setCurrentBuildingMaterialsAmount(base()->currentBuildingMaterialsAmount() + (cyclesToDo * m_levelsInfo.value(currentLevel()).buildingMaterialsGiven));
}

void Factory::setCurrentCycles(unsigned amount) noexcept
{
    if (amount<=maxCycles())
        m_currentCycles=amount;
}

void Factory::setLevelsInfo(const QVector<FactoryLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Factory::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Factory,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

CoolRoom::CoolRoom(Base *base, unsigned level, const QVector<CoolRoomLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_CoolRoom, base, level), m_levelsInfo(levelsInfo){}

void CoolRoom::setLevelsInfo(const QVector<CoolRoomLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned CoolRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_CoolRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

StorageRoom::StorageRoom(Base *base, unsigned level, const QVector<StorageRoomLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_StorageRoom, base, level), m_levelsInfo(levelsInfo){}

void StorageRoom::setLevelsInfo(const QVector<StorageRoomLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned StorageRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_StorageRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

AetheriteSilo::AetheriteSilo(Base *base, unsigned level, const QVector<AetheriteSiloLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_AetheriteSilo, base, level), m_levelsInfo(levelsInfo){}

void AetheriteSilo::setLevelsInfo(const QVector<AetheriteSiloLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned AetheriteSilo::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_AetheriteSilo,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

Barracks::Barracks(Base *base, unsigned level, const QVector<BarracksLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Barracks, base, level), m_levelsInfo(levelsInfo)
{

}

void Barracks::setLevelsInfo(const QVector<BarracksLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Barracks::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_Barracks,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

QDataStream &operator<<(QDataStream &stream, const ActiveTransaction &transaction) noexcept
{
    stream<<static_cast<quint8>(transaction.sourceRes);

    stream<<static_cast<quint8>(transaction.targetRes);

    stream<<static_cast<quint16>(transaction.sourceAmount);

    stream<<static_cast<quint16>(transaction.targetAmount);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, ActiveTransaction &transaction) noexcept
{
    quint8 n;
    quint16 ii;

    stream>>n;
    transaction.sourceRes=static_cast<BaseEnums::Resource>(n);

    stream>>n;
    transaction.targetRes=static_cast<BaseEnums::Resource>(n);

    stream>>ii;
    transaction.sourceAmount=ii;

    stream>>ii;
    transaction.targetAmount=ii;

    return stream;
}

DockingStation::DockingStation(Base *base, unsigned level, const QVector<DockingStationLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_DockingStation, base, level), m_levelsInfo(levelsInfo)
{

}

void DockingStation::prepareRecruits() noexcept
{
    clearRecruits();
    loadRecruits();
    prepareRecruitForQML(0);
}

void DockingStation::prepareRecruitForQML(unsigned slot) noexcept
{
    if (slot<m_recruits.size())
        m_recruitPreparedForQML=m_recruits[slot];
    else
        m_recruitPreparedForQML=nullptr;
}

void DockingStation::hireMercenary(const QString &name, unsigned eta) noexcept
{
    if (base()->heroes()->canAddHero())
    {
        for (int i=0;i<m_recruits.size();++i)
            if (m_recruits[i]->name() == name)
            {
                if (eta>0)
                {
                    m_recruits[i]->setCurrentActivity(HeroEnums::CA_Arriving);
                    base()->heroes()->addHero(m_recruits[i]);
                    m_arrivingHeroes.push_back({m_recruits[i],eta});
                    if (m_recruitPreparedForQML==m_recruits[i])
                    {
                        if (m_recruits.size()>i+1)
                            m_recruitPreparedForQML=m_recruits[i+1];
                        else if (i>0)
                            m_recruitPreparedForQML=m_recruits[i-1];
                        else
                            m_recruitPreparedForQML=nullptr;
                    }
                    m_recruits.remove(i);
                    break;
                }
                else//instant
                {
                    base()->heroes()->addHero(m_recruits[i]);
                    if (m_recruitPreparedForQML==m_recruits[i])
                    {
                        if (m_recruits.size()>i+1)
                            m_recruitPreparedForQML=m_recruits[i+1];
                        else if (i>0)
                            m_recruitPreparedForQML=m_recruits[i-1];
                        else
                            m_recruitPreparedForQML=nullptr;
                    }
                    m_recruits.remove(i);
                    break;
                }
            }
    }
}

void DockingStation::doRecrutationStuff() noexcept
{
    for (int i=0;i<m_arrivingHeroes.size();++i)
    {
        if (m_arrivingHeroes[i].second == 0)
        {
            Hero *h=m_arrivingHeroes[i].first;//antibug thing, leave it as it is
            h->setCurrentActivity(HeroEnums::CA_Idle);
            m_arrivingHeroes.remove(i);
        }
        else
            --m_arrivingHeroes[i].second;
    }
}

QStringList DockingStation::getRecruitsNames() const noexcept
{
    QStringList r;
    for (int i=0;i<m_recruits.size();++i)
        r+=m_recruits[i]->name();
    return r;
}

void DockingStation::cancelHeroArrival(const QString &name) noexcept
{
    for (int i=0;i<m_arrivingHeroes.size();++i)
        if (m_arrivingHeroes[i].first->name() == name)
        {
            m_arrivingHeroes.remove(i);
            break;
        }
}

unsigned DockingStation::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_DockingStation,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

unsigned DockingStation::calculateTransaction(BaseEnums::Resource sourceRes, BaseEnums::Resource targetRes, unsigned sourceAmount) const noexcept
{
    return m_tradingTables.value(m_levelsInfo.value(currentLevel()).profitability).value({sourceRes,targetRes}) * sourceAmount;
}

unsigned DockingStation::calculateTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) const noexcept
{
    return ceilf(static_cast<float>(targetAmount) / m_tradingTables.value(m_levelsInfo.value(currentLevel()).profitability).value({static_cast<BaseEnums::Resource>(sourceRes), static_cast<BaseEnums::Resource>(targetRes)}));
}

void DockingStation::startTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) noexcept
{
    unsigned sA = calculateTransaction(sourceRes, targetRes, targetAmount);
    BaseEnums::Resource sR = static_cast<BaseEnums::Resource>(sourceRes);
    BaseEnums::Resource tR = static_cast<BaseEnums::Resource>(targetRes);

    if (sR == BaseEnums::R_Energy)
        base()->setCurrentEnergyAmount(base()->currentEnergyAmount() - sA);
    else if (sR == BaseEnums::R_FoodSupplies)
        base()->setCurrentFoodSuppliesAmount(base()->currentFoodSuppliesAmount() - sA);
    else if (sR == BaseEnums::R_BuildingMaterials)
        base()->setCurrentBuildingMaterialsAmount(base()->currentBuildingMaterialsAmount() - sA);
    else
        base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - sA);

    m_activeTransactions.push_back({{sR,tR,sA,targetAmount},m_levelsInfo.value(currentLevel()).waitingTime});
}

void DockingStation::handleActiveTransactions() noexcept
{
    for (int i=0;i<m_activeTransactions.size();++i)
    {
        if (m_activeTransactions[i].second == 0)
        {
            if (m_activeTransactions[i].first.targetRes == BaseEnums::R_Energy)
                base()->setCurrentEnergyAmount(base()->currentEnergyAmount() + m_activeTransactions[i].first.targetAmount);
            else if (m_activeTransactions[i].first.targetRes == BaseEnums::R_FoodSupplies)
                base()->setCurrentFoodSuppliesAmount(base()->currentFoodSuppliesAmount() + m_activeTransactions[i].first.targetAmount);
            else if (m_activeTransactions[i].first.targetRes == BaseEnums::R_BuildingMaterials)
                base()->setCurrentBuildingMaterialsAmount(base()->currentBuildingMaterialsAmount() + m_activeTransactions[i].first.targetAmount);
            else
                base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() + m_activeTransactions[i].first.targetAmount);

            m_activeTransactions.remove(i);
            --i;
        }
        else
            --m_activeTransactions[i].second;
    }
}

void DockingStation::prepareEquipments() noexcept
{
    clearEquipments();
    loadEquipments();
    m_equipmentPreparedForQML=m_equipments.value(0,nullptr);
}

void DockingStation::prepareEquipmentForQML(unsigned pos) noexcept
{
    if (pos<m_equipments.size())
        m_equipmentPreparedForQML=m_equipments[pos];
}

void DockingStation::buyEquipment(unsigned pos, unsigned eta) noexcept
{
    if (pos<m_equipments.size())
    {
        if (eta>0)
        {
            m_arrivingEquipments.push_back({m_equipments[pos],eta});
            if (m_equipmentPreparedForQML==m_equipments[pos])
            {
                if (m_equipments.size()>pos+1)
                    m_equipmentPreparedForQML=m_equipments[pos+1];
                else if (pos>0)
                    m_equipmentPreparedForQML=m_equipments[pos-1];
                else
                    m_equipmentPreparedForQML=nullptr;
            }
            m_equipments.remove(pos);
        }
        else//instant
        {
            base()->freeEquipment().push_back(m_equipments[pos]);
            if (m_equipmentPreparedForQML==m_equipments[pos])
            {
                if (m_equipments.size()>pos+1)
                    m_equipmentPreparedForQML=m_equipments[pos+1];
                else if (pos>0)
                    m_equipmentPreparedForQML=m_equipments[pos-1];
                else
                    m_equipmentPreparedForQML=nullptr;
            }
            m_equipments.remove(pos);
        }
    }
}

void DockingStation::doBuyingEquipmentStuff() noexcept
{
    for (int i=0;i<m_arrivingEquipments.size();++i)
    {
        if (m_arrivingEquipments[i].second == 0)
        {
            Equipment *eq=m_arrivingEquipments[i].first;
            base()->freeEquipment().push_back(eq);
            m_arrivingEquipments.remove(i);
        }
        else
            --m_arrivingEquipments[i].second;
    }
}

int DockingStation::remainingDaysUntilHeroArrival(const QString &heroName) const noexcept
{
    for (int i=0;i<m_arrivingHeroes.size();++i)
        if (m_arrivingHeroes[i].first->name() == heroName)
            return m_arrivingHeroes[i].second;

    return -1;
}

void DockingStation::loadRecruits() noexcept
{
    QStringList names{base()->gameObject()->assetsPool().allHeroes()};//load all mercs names
    for (int i=0;i<base()->heroes()->heroes().size();++i)//remove mercs that are already hired
        names.removeAt(names.indexOf(base()->heroes()->heroes()[i]->name()));
    for (int i=0;i<names.size();)//remove mercs banned in DoSt
    {
        if (base()->heroDockingStationBans().contains(names[i]))
            names.removeAt(i);
        else
            ++i;
    }
    for (int i=0;i<recruitsAmount() && !names.isEmpty();++i)//add random recruits
    {
        unsigned indexOfRecruit = Randomizer::randomBetweenAAndB(0,names.size()-1);
        base()->gameObject()->assetsPool().loadHeroNamedFromList(names[indexOfRecruit]);
        for (int j=0;j<base()->gameObject()->assetsPool().loadedHeroes().size();++j)
            if (base()->gameObject()->assetsPool().loadedHeroes()[j]->name()==names[indexOfRecruit])
            {
                m_recruits.push_back(base()->gameObject()->assetsPool().loadedHeroes()[j]);
                break;
            }
        names.removeAt(indexOfRecruit);
    }
}

void DockingStation::clearRecruits() noexcept
{
    for (int i=0;i<m_recruits.size();++i)
        if (m_recruits[i] != nullptr)//TODO possibly remove that if
            for (int j=0;j<base()->gameObject()->assetsPool().loadedHeroes().size();++j)
                if (base()->gameObject()->assetsPool().loadedHeroes()[j]->name() == m_recruits[i]->name())
                {
                    base()->gameObject()->assetsPool().unloadHero(j);
                    break;
                }
    m_recruits.clear();

    m_recruitPreparedForQML=nullptr;
}

void DockingStation::loadEquipments() noexcept
{
    auto allEq=base()->gameObject()->assetsPool().equipment();
    for (int i=0;i<allEq.size();)
    {
        if (allEq[i]->tier()<=maxTier())
            ++i;
        else
            allEq.remove(i);
    }
    for (int i=0;i<equipmentsAmount();++i)
    {
        unsigned indexOfEquipment = Randomizer::randomBetweenAAndB(0,allEq.size()-1);
        m_equipments.push_back(base()->gameObject()->assetsPool().makeEquipmentNamed(allEq[indexOfEquipment]->name()));
    }
}

void DockingStation::clearEquipments() noexcept
{
    for (int i=0;i<m_equipments.size();++i)
        delete m_equipments[i];

    m_equipments.clear();

    m_equipmentPreparedForQML=nullptr;
}

void DockingStation::addEquipmentFromSave(Equipment *eq) noexcept
{
    m_equipments.push_back(eq);
}

Base::Base(Game *gameObject) noexcept
    : QObject(nullptr), m_gameObject(gameObject), m_freezeGameProgress(false)
{
    m_gameClock=new GameClock;
    m_gameClock->setBasePtr(this);

    m_centralUnit=new CentralUnit(this,1,{});
    m_hospital=new Hospital(this,0,{});
    m_trainingGround=new TrainingGround(this,0,{});
    m_gym=new Gym(this,0,{});
    m_laboratory=new Laboratory(this,0,{});
    m_playingField=new PlayingField(this,0,{});
    m_bar=new Bar(this,0,{});
    m_shrine=new Shrine(this,0,{});
    m_seclusion=new Seclusion(this,0,{});
    m_powerplant=new Powerplant(this,1,{});
    m_factory=new Factory(this,1,{});
    m_coolRoom=new CoolRoom(this,1,{});
    m_storageRoom=new StorageRoom(this,1,{});
    m_aetheriteSilo=new AetheriteSilo(this,1,{});
    m_barracks=new Barracks(this,1,{});
    m_dockingStation=new DockingStation(this,1,{});

    m_buildings.insert(BaseEnums::B_CentralUnit,m_centralUnit);
    m_buildings.insert(BaseEnums::B_Hospital,m_hospital);
    m_buildings.insert(BaseEnums::B_TrainingGround,m_trainingGround);
    m_buildings.insert(BaseEnums::B_Gym,m_gym);
    m_buildings.insert(BaseEnums::B_Laboratory,m_laboratory);
    m_buildings.insert(BaseEnums::B_PlayingField,m_playingField);
    m_buildings.insert(BaseEnums::B_Bar,m_bar);
    m_buildings.insert(BaseEnums::B_Shrine,m_shrine);
    m_buildings.insert(BaseEnums::B_Seclusion,m_seclusion);
    m_buildings.insert(BaseEnums::B_Powerplant,m_powerplant);
    m_buildings.insert(BaseEnums::B_Factory,m_factory);
    m_buildings.insert(BaseEnums::B_CoolRoom,m_coolRoom);
    m_buildings.insert(BaseEnums::B_StorageRoom,m_storageRoom);
    m_buildings.insert(BaseEnums::B_AetheriteSilo,m_aetheriteSilo);
    m_buildings.insert(BaseEnums::B_Barracks,m_barracks);
    m_buildings.insert(BaseEnums::B_DockingStation,m_dockingStation);

    m_heroes=new HeroesContainer(this);
}

void Base::setupNewBase() noexcept
{
    m_energy=100;
    m_foodSupplies=5;
    m_buildingMaterials=5;
    m_aetherite=50;

    m_dockingStation->prepareRecruits();
    m_dockingStation->prepareEquipments();

    m_heroes->setAmountOfSlots(m_barracks->heroesLimit());//setting heroes limit
}

Base::~Base() noexcept
{
    delete m_centralUnit;
    delete m_hospital;
    delete m_trainingGround;
    delete m_gym;
    delete m_laboratory;
    delete m_playingField;
    delete m_bar;
    delete m_shrine;
    delete m_seclusion;
    delete m_powerplant;
    delete m_factory;
    delete m_coolRoom;
    delete m_storageRoom;
    delete m_aetheriteSilo;
    delete m_barracks;
    delete m_dockingStation;

    delete m_gameClock;

    delete m_heroes;
}

void Base::loadSaveData(const SaveData &data) noexcept
{
    m_buildingLevels.insert(BaseEnums::B_CentralUnit,data.buildings.levels.centralUnit);//buildings levels loading
    m_buildingLevels.insert(BaseEnums::B_Hospital,data.buildings.levels.hospital);
    m_buildingLevels.insert(BaseEnums::B_TrainingGround,data.buildings.levels.trainingGround);
    m_buildingLevels.insert(BaseEnums::B_Gym,data.buildings.levels.gym);
    m_buildingLevels.insert(BaseEnums::B_Laboratory,data.buildings.levels.laboratory);
    m_buildingLevels.insert(BaseEnums::B_PlayingField,data.buildings.levels.playingField);
    m_buildingLevels.insert(BaseEnums::B_Bar,data.buildings.levels.bar);
    m_buildingLevels.insert(BaseEnums::B_Shrine,data.buildings.levels.shrine);
    m_buildingLevels.insert(BaseEnums::B_Seclusion,data.buildings.levels.seclusion);
    m_buildingLevels.insert(BaseEnums::B_Powerplant,data.buildings.levels.powerplant);
    m_buildingLevels.insert(BaseEnums::B_Factory,data.buildings.levels.factory);
    m_buildingLevels.insert(BaseEnums::B_CoolRoom,data.buildings.levels.coolRoom);
    m_buildingLevels.insert(BaseEnums::B_StorageRoom,data.buildings.levels.storageRoom);
    m_buildingLevels.insert(BaseEnums::B_AetheriteSilo,data.buildings.levels.aetheriteSilo);
    m_buildingLevels.insert(BaseEnums::B_Barracks,data.buildings.levels.barracks);
    m_buildingLevels.insert(BaseEnums::B_DockingStation,data.buildings.levels.dockingStation);

    m_hospital->resizeSlotsAfterUpgrade();//resizing slots in buildings
    m_trainingGround->resizeSlotsAfterUpgrade();
    m_gym->resizeSlotsAfterUpgrade();
    m_laboratory->resizeSlotsAfterUpgrade();
    m_playingField->resizeSlotsAfterUpgrade();
    m_bar->resizeSlotsAfterUpgrade();
    m_shrine->resizeSlotsAfterUpgrade();
    m_seclusion->resizeSlotsAfterUpgrade();

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//loading needed mercenaries in AssetsPool
        m_gameObject->assetsPool().loadHeroNamedFromList(data.buildings.dockingStationThings.recruits[i]);
    for (int i=0;i<data.heroes.hiredHeroes.size();++i)
        m_gameObject->assetsPool().loadHeroNamedFromList(data.heroes.hiredHeroes[i].name);

    m_heroes->setAmountOfSlots(m_barracks->heroesLimit());//setting heroes limit

    m_powerplant->setCurrentCycles(data.buildings.cyclesSet.powerplant);//setting cycles
    m_factory->setCurrentCycles(data.buildings.cyclesSet.factory);

    m_centralUnit->setIsBeingUpgraded(data.buildings.upgrading.centralUnit);//setting upgrades
    m_powerplant->setIsBeingUpgraded(data.buildings.upgrading.powerplant);
    m_factory->setIsBeingUpgraded(data.buildings.upgrading.factory);
    m_coolRoom->setIsBeingUpgraded(data.buildings.upgrading.coolRoom);
    m_storageRoom->setIsBeingUpgraded(data.buildings.upgrading.storageRoom);
    m_aetheriteSilo->setIsBeingUpgraded(data.buildings.upgrading.aetheriteSilo);
    m_hospital->setIsBeingUpgraded(data.buildings.upgrading.hospital);
    m_barracks->setIsBeingUpgraded(data.buildings.upgrading.barracks);
    m_dockingStation->setIsBeingUpgraded(data.buildings.upgrading.dockingStation);
    m_trainingGround->setIsBeingUpgraded(data.buildings.upgrading.trainingGround);
    m_gym->setIsBeingUpgraded(data.buildings.upgrading.gym);
    m_laboratory->setIsBeingUpgraded(data.buildings.upgrading.laboratory);
    m_playingField->setIsBeingUpgraded(data.buildings.upgrading.playingField);
    m_bar->setIsBeingUpgraded(data.buildings.upgrading.bar);
    m_shrine->setIsBeingUpgraded(data.buildings.upgrading.shrine);
    m_seclusion->setIsBeingUpgraded(data.buildings.upgrading.seclusion);

    for (int i=0;i<data.equipments.freeArmor.size();++i)//creating owned equipment
        m_freeEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeArmor[i]));
    for (int i=0;i<data.equipments.freeWeaponsTools.size();++i)
        m_freeEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeWeaponsTools[i]));

    for (int i=0;i<data.heroes.hiredHeroes.size();++i)//adding mercenaries
        m_heroes->addHero(HeroBuilder::qobjectifyHeroData(data.heroes.hiredHeroes[i]));

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//adding possible recruits
        for (int j=0;j<m_gameObject->assetsPool().loadedHeroes().size();++j)
            if (m_gameObject->assetsPool().loadedHeroes()[j]->name() == data.buildings.dockingStationThings.recruits[i])
            {
                m_dockingStation->addRecruitFromSave(m_gameObject->assetsPool().loadedHeroes()[j]);
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.equipments.size();++i)//adding buyable equipments
        m_dockingStation->addEquipmentFromSave(m_gameObject->assetsPool().makeEquipmentNamed(data.buildings.dockingStationThings.equipments[i]));

    for (int i=0;i<data.buildings.dockingStationThings.arrivingHeroes.size();++i)//adding arriving mercenaries
        for (int j=0;j<m_heroes->amountOfHeroes();++j)
            if (m_heroes->getHero(j)->name() == data.buildings.dockingStationThings.arrivingHeroes[i].first)
            {
                m_dockingStation->addArrivingHeroFromSave({m_heroes->getHero(j),static_cast<unsigned>(data.buildings.dockingStationThings.arrivingHeroes[i].second)});
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.arrivingEquipments.size();++i)//adding arriving equipments
        for (int j=0;j<m_gameObject->assetsPool().equipment().size();++j)
            if (m_gameObject->assetsPool().equipment()[j]->name() == data.buildings.dockingStationThings.arrivingEquipments[i].first)
            {
                m_dockingStation->addArrivingEquipmentFromSave({m_gameObject->assetsPool().equipment()[j],static_cast<unsigned>(data.buildings.dockingStationThings.arrivingEquipments[i].second)});
                break;
            }

    QVector <QPair <ActiveTransaction, unsigned> > actTr;
    for (int i=0;i<data.buildings.dockingStationThings.activeResourceTransactions.size();++i)//set active resource transactions
        actTr+={data.buildings.dockingStationThings.activeResourceTransactions[i].first, static_cast<unsigned>(data.buildings.dockingStationThings.activeResourceTransactions[i].second)};
    m_dockingStation->setActiveTransactionsFromSave(actTr);

    for (int i=0;i<data.buildings.heroSlots.hospital.size();++i)//setting slots in buildings
        m_hospital->setSlot(i,!data.buildings.heroSlots.hospital[i].isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.hospital[i])) : nullptr);
    for (int i=0;i<data.buildings.heroSlots.trainingGround.size();++i)
        m_trainingGround->setSlot(i,!data.buildings.heroSlots.trainingGround[i].first.isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.trainingGround[i].first)) : nullptr, static_cast<unsigned>(data.buildings.heroSlots.trainingGround[i].second));
    for (int i=0;i<data.buildings.heroSlots.gym.size();++i)
        m_gym->setSlot(i,!data.buildings.heroSlots.gym[i].first.isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.gym[i].first)) : nullptr, static_cast<unsigned>(data.buildings.heroSlots.gym[i].second));
    for (int i=0;i<data.buildings.heroSlots.laboratory.size();++i)
        m_laboratory->setSlot(i,!data.buildings.heroSlots.laboratory[i].first.isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.laboratory[i].first)) : nullptr, static_cast<unsigned>(data.buildings.heroSlots.laboratory[i].second));
    for (int i=0;i<data.buildings.heroSlots.playingField.size();++i)
        m_playingField->setSlot(i,!data.buildings.heroSlots.playingField[i].isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.playingField[i])) : nullptr);
    for (int i=0;i<data.buildings.heroSlots.bar.size();++i)
        m_bar->setSlot(i,!data.buildings.heroSlots.bar[i].isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.bar[i])) : nullptr);
    for (int i=0;i<data.buildings.heroSlots.shrine.size();++i)
        m_shrine->setSlot(i,!data.buildings.heroSlots.shrine[i].isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.shrine[i])) : nullptr);
    for (int i=0;i<data.buildings.heroSlots.seclusion.size();++i)
        m_seclusion->setSlot(i,!data.buildings.heroSlots.seclusion[i].isEmpty() ? m_heroes->getHero(m_heroes->findHero(data.buildings.heroSlots.seclusion[i])) : nullptr);

    m_energy=data.resources.energy;//setting resources
    m_foodSupplies=data.resources.foodSupplies;
    m_buildingMaterials=data.resources.buildingMaterials;
    m_aetherite=data.resources.aetheriteOre;

    m_gameClock->clearAlarms();//setting alarms in GameClock
    for (int i=0;i<data.alarms.buildingUpgrades.size();++i)
    {
        m_gameClock->addAlarm(data.alarms.buildingUpgrades[i].first, static_cast<TimerAlarm*>(new BuildingUpgradeTimerAlarm (data.alarms.buildingUpgrades[i].second.buildingName(), data.alarms.buildingUpgrades[i].second.buildingLevel())));
    }

    m_gameClock->updateClock(data.overall.freezeGameProgress ? QDateTime::currentDateTime() : data.overall.lastKnownDate, data.overall.lastKnownDay, data.overall.lastKnownHour, data.overall.lastKnownMinute);//setting date and time in GameClock
}

SaveData Base::getSaveData() noexcept
{
    SaveData data;

    data.buildings.levels.centralUnit=m_buildingLevels.value(BaseEnums::B_CentralUnit,0);
    data.buildings.levels.hospital=m_buildingLevels.value(BaseEnums::B_Hospital,0);
    data.buildings.levels.trainingGround=m_buildingLevels.value(BaseEnums::B_TrainingGround,0);
    data.buildings.levels.gym=m_buildingLevels.value(BaseEnums::B_Gym,0);
    data.buildings.levels.laboratory=m_buildingLevels.value(BaseEnums::B_Laboratory,0);
    data.buildings.levels.playingField=m_buildingLevels.value(BaseEnums::B_PlayingField,0);
    data.buildings.levels.bar=m_buildingLevels.value(BaseEnums::B_Bar,0);
    data.buildings.levels.shrine=m_buildingLevels.value(BaseEnums::B_Shrine,0);
    data.buildings.levels.seclusion=m_buildingLevels.value(BaseEnums::B_Seclusion,0);
    data.buildings.levels.powerplant=m_buildingLevels.value(BaseEnums::B_Powerplant,0);
    data.buildings.levels.factory=m_buildingLevels.value(BaseEnums::B_Factory,0);
    data.buildings.levels.coolRoom=m_buildingLevels.value(BaseEnums::B_CoolRoom,0);
    data.buildings.levels.storageRoom=m_buildingLevels.value(BaseEnums::B_StorageRoom,0);
    data.buildings.levels.aetheriteSilo=m_buildingLevels.value(BaseEnums::B_AetheriteSilo,0);
    data.buildings.levels.barracks=m_buildingLevels.value(BaseEnums::B_Barracks,0);
    data.buildings.levels.dockingStation=m_buildingLevels.value(BaseEnums::B_DockingStation,0);

    data.buildings.cyclesSet.powerplant=m_powerplant->currentCycles();
    data.buildings.cyclesSet.factory=m_factory->currentCycles();

    data.buildings.upgrading.centralUnit=m_centralUnit->isBeingUpgraded();
    data.buildings.upgrading.powerplant=m_powerplant->isBeingUpgraded();
    data.buildings.upgrading.factory=m_factory->isBeingUpgraded();
    data.buildings.upgrading.coolRoom=m_coolRoom->isBeingUpgraded();
    data.buildings.upgrading.storageRoom=m_storageRoom->isBeingUpgraded();
    data.buildings.upgrading.aetheriteSilo=m_aetheriteSilo->isBeingUpgraded();
    data.buildings.upgrading.hospital=m_hospital->isBeingUpgraded();
    data.buildings.upgrading.barracks=m_barracks->isBeingUpgraded();
    data.buildings.upgrading.dockingStation=m_dockingStation->isBeingUpgraded();
    data.buildings.upgrading.trainingGround=m_trainingGround->isBeingUpgraded();
    data.buildings.upgrading.gym=m_gym->isBeingUpgraded();
    data.buildings.upgrading.laboratory=m_laboratory->isBeingUpgraded();
    data.buildings.upgrading.playingField=m_playingField->isBeingUpgraded();
    data.buildings.upgrading.bar=m_bar->isBeingUpgraded();
    data.buildings.upgrading.shrine=m_shrine->isBeingUpgraded();
    data.buildings.upgrading.seclusion=m_seclusion->isBeingUpgraded();

    for (int i=0;i<m_freeEquipment.size();++i)
    {
        if (m_freeEquipment[i]->type()==EquipmentEnums::T_Armor)
            data.equipments.freeArmor.push_back(m_freeEquipment[i]->name());
        else if (m_freeEquipment[i]->type()==EquipmentEnums::T_WeaponTool)
            data.equipments.freeWeaponsTools.push_back(m_freeEquipment[i]->name());
    }

    for (int i=0;i<m_heroes->amountOfHeroes();++i)
        data.heroes.hiredHeroes.push_back(HeroBuilder::deqobjectifyHero(m_heroes->heroes()[i]));

    data.buildings.dockingStationThings.recruits=m_dockingStation->getRecruitsNames().toVector();

    data.buildings.dockingStationThings.equipments=m_dockingStation->availableEquipmentsNames();

    for (int i=0;i<m_dockingStation->arrivingHeroes().size();++i)
        data.buildings.dockingStationThings.arrivingHeroes.push_back({m_dockingStation->arrivingHeroes()[i].first->name(), static_cast<quint8>(m_dockingStation->arrivingHeroes()[i].second)});

    for (int i=0;i<m_dockingStation->arrivingEquipments().size();++i)
        data.buildings.dockingStationThings.arrivingEquipments.push_back({m_dockingStation->arrivingEquipments()[i].first->name(), static_cast<quint8>(m_dockingStation->arrivingEquipments()[i].second)});

    auto actTr=m_dockingStation->activeTransactions();
    for (int i=0;i<actTr.size();++i)
        data.buildings.dockingStationThings.activeResourceTransactions+={actTr[i].first,static_cast<quint8>(actTr[i].second)};

    for (int i=0;i<m_hospital->amountOfSlots();++i)
        data.buildings.heroSlots.hospital.push_back(m_hospital->slot(i)!=nullptr ? m_hospital->slot(i)->name() : "");
    for (int i=0;i<m_trainingGround->amountOfSlots();++i)
    {
        auto p=m_trainingGround->slot(i);
        if (p.first!=nullptr)
            data.buildings.heroSlots.trainingGround.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.heroSlots.trainingGround.push_back({"",0});
    }
    for (int i=0;i<m_gym->amountOfSlots();++i)
    {
        auto p=m_gym->slot(i);
        if (p.first!=nullptr)
            data.buildings.heroSlots.gym.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.heroSlots.gym.push_back({"",0});
    }
    for (int i=0;i<m_laboratory->amountOfSlots();++i)
    {
        auto p=m_laboratory->slot(i);
        if (p.first!=nullptr)
            data.buildings.heroSlots.laboratory.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.heroSlots.laboratory.push_back({"",0});
    }
    for (int i=0;i<m_playingField->amountOfSlots();++i)
        data.buildings.heroSlots.playingField.push_back(m_playingField->slot(i)!=nullptr ? m_playingField->slot(i)->name() : "");
    for (int i=0;i<m_bar->amountOfSlots();++i)
        data.buildings.heroSlots.bar.push_back(m_bar->slot(i)!=nullptr ? m_bar->slot(i)->name() : "");
    for (int i=0;i<m_shrine->amountOfSlots();++i)
        data.buildings.heroSlots.shrine.push_back(m_shrine->slot(i)!=nullptr ? m_shrine->slot(i)->name() : "");
    for (int i=0;i<m_seclusion->amountOfSlots();++i)
        data.buildings.heroSlots.seclusion.push_back(m_seclusion->slot(i)!=nullptr ? m_seclusion->slot(i)->name() : "");

    data.resources.energy=m_energy;
    data.resources.foodSupplies=m_foodSupplies;
    data.resources.buildingMaterials=m_buildingMaterials;
    data.resources.aetheriteOre=m_aetherite;

    m_gameClock->saveCurrentDate();
    data.overall.lastKnownDate=QDateTime::currentDateTime();
    data.overall.lastKnownDay=m_gameClock->currentDay();
    data.overall.lastKnownHour=m_gameClock->currentHour();
    data.overall.lastKnownMinute=m_gameClock->currentMin();
    data.overall.freezeGameProgress=m_freezeGameProgress;

    QVector <QPair<unsigned,BuildingUpgradeTimerAlarm>> buTimerAlarms;
    QVector <QPair<unsigned,TimerAlarm*>> timerAlarms = m_gameClock->getAllAlarms();
    for (int i=0;i<timerAlarms.size();++i)
    {
        if (timerAlarms[i].second->type()==TimerAlarmEnums::AT_BuildingUpgrade)
            buTimerAlarms.push_back({timerAlarms[i].first,*static_cast<BuildingUpgradeTimerAlarm*>(timerAlarms[i].second)});
    }
    data.alarms.buildingUpgrades=buTimerAlarms;
    buTimerAlarms.clear();

    return data;
}

void Base::startNewDay() noexcept
{
    if (m_gameClock->currentDay() % 7 == 1)
        startNewWeek();

    int dailyFoodConsumptionCost=0;
    for (int i=0;i<m_heroes->amountOfHeroes();++i)
        dailyFoodConsumptionCost+=m_heroes->getHero(i)->dailyFoodConsumption();
    if (dailyFoodConsumptionCost < m_foodSupplies)
        m_foodSupplies-=dailyFoodConsumptionCost;
    else
        m_foodSupplies=0;

    activateBuildingsAtDayEnd();

    QVector<TimerAlarm *> timeoutedAlarms = m_gameClock->moveToNextDayAndGetTimeoutedResults();

    for (int i=0;i<timeoutedAlarms.size();++i)
    {
        if (timeoutedAlarms[i]->type() == TimerAlarmEnums::AT_BuildingUpgrade)
        {
            m_buildingLevels.insert(static_cast<BuildingUpgradeTimerAlarm*>(timeoutedAlarms[i])->buildingName(), static_cast<BuildingUpgradeTimerAlarm*>(timeoutedAlarms[i])->buildingLevel());
            m_buildings[static_cast<BuildingUpgradeTimerAlarm*>(timeoutedAlarms[i])->buildingName()]->registerUpgradeCompletion();
        }
    }

    for (int i=0;i<timeoutedAlarms.size();++i)
        delete timeoutedAlarms[i];

    m_heroes->setAmountOfSlots(m_barracks->heroesLimit());

    for (auto heroName : m_heroDockingStationBans.keys())
    {
        if (m_heroDockingStationBans.value(heroName)==1)
        {
            m_heroDockingStationBans.erase(m_heroDockingStationBans.find(heroName));
            continue;
        }
        m_heroDockingStationBans.insert(heroName,m_heroDockingStationBans.value(heroName)-1);
    }
    m_dockingStation->doRecrutationStuff();
    m_dockingStation->doBuyingEquipmentStuff();

    m_dockingStation->handleActiveTransactions();
}

void Base::activateBuildingsAtDayEnd() noexcept
{
    int basicEnergyCost=0;
    for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
        basicEnergyCost+=m_buildings.value(static_cast<BaseEnums::Building>(i))->basicCostInEnergy();
    if (basicEnergyCost < m_energy)
        m_energy-=basicEnergyCost;
    else
        m_energy=0;

    bar()->destressHeroes();
    factory()->exchangeResources();
    gym()->trainHeroes();
    hospital()->healHeroes();
    laboratory()->trainHeroes();
    playingField()->destressHeroes();
    powerplant()->exchangeResources();
    seclusion()->destressHeroes();
    shrine()->destressHeroes();
    trainingGround()->trainHeroes();
}

void Base::startNewWeek() noexcept
{
    m_dockingStation->prepareRecruits();
    m_dockingStation->prepareEquipments();

    int salaryAetheriteCost=0;
    for (int i=0;i<m_heroes->amountOfHeroes();++i)
        salaryAetheriteCost+=m_heroes->getHero(i)->salary();
    if (salaryAetheriteCost < m_aetherite)
        m_aetherite-=salaryAetheriteCost;
    else
        m_aetherite=0;
}

BuildingUpgradeRequirements Base::buildingRequirements(BaseEnums::Building buildingName, unsigned level) const noexcept
{
    return m_buildingRequirements.value({buildingName,level});
}

void Base::setCurrentEnergyAmount(unsigned amount) noexcept
{
    if (amount <= currentEnergyLimit())
        m_energy = amount;
}

void Base::setCurrentFoodSuppliesAmount(unsigned amount) noexcept
{
    if (amount <= currentFoodSuppliesLimit())
        m_foodSupplies = amount;
}

void Base::setCurrentBuildingMaterialsAmount(unsigned amount) noexcept
{
    if (amount <= currentBuildingMaterialsLimit())
        m_buildingMaterials = amount;
}

void Base::setCurrentAetheriteAmount(unsigned amount) noexcept
{
    if (amount <= currentAetheriteLimit())
        m_aetherite = amount;
}

void Base::decreaseEnergyAmount(unsigned amount) noexcept
{
    m_energy = m_energy>amount ? m_energy-amount : 0;
}

void Base::decreaseFoodSuppliesAmount(unsigned amount) noexcept
{
    m_foodSupplies = m_foodSupplies>amount ? m_foodSupplies-amount : 0;
}

void Base::setBuildingLevel(BaseEnums::Building buildingName, unsigned level) noexcept
{
    m_buildingLevels.insert(buildingName,level);
}

void Base::setBuildingDescription(BaseEnums::Building buildingName, const QString &desc) noexcept
{
    m_buildingDescriptions.insert(buildingName,desc);
}

void Base::setBuildingDescriptions(const QVector<QPair<BaseEnums::Building, QString> > &descs) noexcept
{
    for (int i=0;i<descs.size();++i)
        m_buildingDescriptions.insert(descs[i].first,descs[i].second);
}

void Base::setBuildingRequirements(const QMap<QPair<BaseEnums::Building, unsigned>, BuildingUpgradeRequirements> &reqs) noexcept
{
    m_buildingRequirements=reqs;
}

Building *Base::getBuilding(BaseEnums::Building buildingName) noexcept
{
    switch (buildingName) {
    case BaseEnums::B_AetheriteSilo:
        return m_aetheriteSilo;
    case BaseEnums::B_Bar:
        return m_bar;
    case BaseEnums::B_Barracks:
        return m_barracks;
    case BaseEnums::B_CentralUnit:
        return m_centralUnit;
    case BaseEnums::B_CoolRoom:
        return m_coolRoom;
    case BaseEnums::B_DockingStation:
        return m_dockingStation;
    case BaseEnums::B_Factory:
        return m_factory;
    case BaseEnums::B_Gym:
        return m_gym;
    case BaseEnums::B_Hospital:
        return m_hospital;
    case BaseEnums::B_Laboratory:
        return m_laboratory;
    case BaseEnums::B_PlayingField:
        return m_playingField;
    case BaseEnums::B_Powerplant:
        return m_powerplant;
    case BaseEnums::B_Seclusion:
        return m_seclusion;
    case BaseEnums::B_Shrine:
        return m_shrine;
    case BaseEnums::B_StorageRoom:
        return m_storageRoom;
    case BaseEnums::B_TrainingGround:
        return m_trainingGround;
    default:
        qWarning()<<"BaseEnums::Building enum->Building * conversion failed for "<<buildingName;
        return nullptr;
    }
}
