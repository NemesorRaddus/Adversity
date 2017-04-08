#include "base.h"

#include "timer.h"

#include <QDebug>

BaseEnums::Resource BaseEnums::fromQStringToResourceEnum(const QString &resource) noexcept
{
    if (resource=="R_Energy")
        return R_Energy;
    if (resource=="R_FoodSupplies")
        return R_FoodSupplies;
    if (resource=="R_BuildingMaterials")
        return R_BuildingMaterials;
    if (resource=="R_AetheriteOre")
        return R_AetheriteOre;
}

QString BaseEnums::fromResourceEnumToQString(BaseEnums::Resource resource) noexcept
{
    if (resource==R_Energy)
        return "R_Energy";
    if (resource==R_FoodSupplies)
        return "R_FoodSupplies";
    if (resource==R_BuildingMaterials)
        return "R_BuildingMaterials";
    if (resource==R_AetheriteOre)
        return "R_AetheriteOre";
}

BaseEnums::Building BaseEnums::fromQStringToBuildingEnum(const QString &building) noexcept
{
    if (building=="B_CentralUnit")
        return B_CentralUnit;
    if (building=="B_Powerplant")
        return B_Powerplant;
    if (building=="B_Factory")
        return B_Factory;
    if (building=="B_CoolRoom")
        return B_CoolRoom;
    if (building=="B_StorageRoom")
        return B_StorageRoom;
    if (building=="B_AetheriteSilo")
        return B_AetheriteSilo;
    if (building=="B_Hospital")
        return B_Hospital;
    if (building=="B_Barracks")
        return B_Barracks;
    if (building=="B_DockingStation")
        return B_DockingStation;
    if (building=="B_TrainingGround")
        return B_TrainingGround;
    if (building=="B_Gym")
        return B_Gym;
    if (building=="B_Laboratory")
        return B_Laboratory;
    if (building=="B_PlayingField")
        return B_PlayingField;
    if (building=="B_Bar")
        return B_Bar;
    if (building=="B_Shrine")
        return B_Shrine;
    if (building=="B_Seclusion")
        return B_Seclusion;
}

QString BaseEnums::fromBuildingEnumToQString(BaseEnums::Building building) noexcept
{
    if (building==B_CentralUnit)
        return "B_CentralUnit";
    if (building==B_Powerplant)
        return "B_Powerplant";
    if (building==B_Factory)
        return "B_Factory";
    if (building==B_CoolRoom)
        return "B_CoolRoom";
    if (building==B_StorageRoom)
        return "B_StorageRoom";
    if (building==B_AetheriteSilo)
        return "B_AetheriteSilo";
    if (building==B_Hospital)
        return "B_Hospital";
    if (building==B_Barracks)
        return "B_Barracks";
    if (building==B_DockingStation)
        return "B_DockingStation";
    if (building==B_TrainingGround)
        return "B_TrainingGround";
    if (building==B_Gym)
        return "B_Gym";
    if (building==B_Laboratory)
        return "B_Laboratory";
    if (building==B_PlayingField)
        return "B_PlayingField";
    if (building==B_Bar)
        return "B_Bar";
    if (building==B_Shrine)
        return "B_Shrine";
    if (building==B_Seclusion)
        return "B_Seclusion";
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
    m_heroesBeingHealed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void Hospital::healHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=NULL)
            m_heroesBeingHealed[i]->setHealth(m_heroesBeingHealed[i]->health() + m_levelsInfo.value(currentLevel()).hpRestored);
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

TrainingGround::TrainingGround(Base *base, unsigned level, const QVector<TrainingGroundLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_TrainingGround, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void TrainingGround::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i]!=NULL)
        {
            m_heroesBeingTrained[i]->setCombatEffectiveness(m_heroesBeingTrained[i]->combatEffectiveness() + m_levelsInfo.value(currentLevel()).combatEffectivenessBonus);
            m_heroesBeingTrained[i]->setProficiency(m_heroesBeingTrained[i]->proficiency() + m_levelsInfo.value(currentLevel()).proficiencyBonus);
            m_heroesBeingTrained[i]->setCleverness(m_heroesBeingTrained[i]->cleverness() + m_levelsInfo.value(currentLevel()).clevernessBonus);
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

Gym::Gym(Base *base, unsigned level, const QVector<GymLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Gym, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Gym::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

void Gym::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i]!=NULL)
        {
            m_heroesBeingTrained[i]->setCombatEffectiveness(m_heroesBeingTrained[i]->combatEffectiveness() + m_levelsInfo.value(currentLevel()).combatEffectivenessBonus);
            m_heroesBeingTrained[i]->setProficiency(m_heroesBeingTrained[i]->proficiency() + m_levelsInfo.value(currentLevel()).proficiencyBonus);
            m_heroesBeingTrained[i]->setCleverness(m_heroesBeingTrained[i]->cleverness() + m_levelsInfo.value(currentLevel()).clevernessBonus);
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

Laboratory::Laboratory(Base *base, unsigned level, const QVector<LaboratoryLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Laboratory, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Laboratory::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

void Laboratory::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i]!=NULL)
        {
            m_heroesBeingTrained[i]->setCombatEffectiveness(m_heroesBeingTrained[i]->combatEffectiveness() + m_levelsInfo.value(currentLevel()).combatEffectivenessBonus);
            m_heroesBeingTrained[i]->setProficiency(m_heroesBeingTrained[i]->proficiency() + m_levelsInfo.value(currentLevel()).proficiencyBonus);
            m_heroesBeingTrained[i]->setCleverness(m_heroesBeingTrained[i]->cleverness() + m_levelsInfo.value(currentLevel()).clevernessBonus);
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

PlayingField::PlayingField(Base *base, unsigned level, const QVector<PlayingFieldLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_PlayingField, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void PlayingField::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=NULL)
        {
            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForReligious);

        }
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

Bar::Bar(Base *base, unsigned level, const QVector<BarLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Bar, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void Bar::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=NULL)
        {
            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForReligious);

        }
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

Shrine::Shrine(Base *base, unsigned level, const QVector<ShrineLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Shrine, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void Shrine::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=NULL)
        {
            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForReligious);

        }
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

Seclusion::Seclusion(Base *base, unsigned level, const QVector<SeclusionLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Seclusion, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

void Seclusion::destressHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingDestressed.size();++i)
        if (m_heroesBeingDestressed[i]!=NULL)
        {
            if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Active)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Convivial)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Recluse)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_heroesBeingDestressed[i]->nature() == HeroEnums::N_Religious)
                m_heroesBeingDestressed[i]->setStress(m_heroesBeingDestressed[i]->stress() - m_levelsInfo.value(currentLevel()).stressReductionForReligious);

        }
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

DockingStation::DockingStation(Base *base, unsigned level, const QVector<DockingStationLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_DockingStation, base, level), m_levelsInfo(levelsInfo)
{

}

void DockingStation::setLevelsInfo(const QVector<DockingStationLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned DockingStation::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(BaseEnums::B_DockingStation,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

Base::Base(QObject *parent) noexcept
    : QObject(parent)
{
    m_energy=100;
    m_foodSupplies=5;
    m_buildingMaterials=5;
    m_aetherite=5;

    m_gameClock=new GameClock;
    m_gameClock->setBasePtr(this);

    m_centralUnit=new CentralUnit(this,1,QVector<CentralUnitLevelInfo>());//TESTINGONLY
    m_hospital=new Hospital(this,0,QVector <HospitalLevelInfo>());
    m_trainingGround=new TrainingGround(this,0,QVector<TrainingGroundLevelInfo>());
    m_gym=new Gym(this,0,QVector<GymLevelInfo>());
    m_laboratory=new Laboratory(this,0,QVector<LaboratoryLevelInfo>());
    m_playingField=new PlayingField(this,0,QVector<PlayingFieldLevelInfo>());
    m_bar=new Bar(this,0,QVector<BarLevelInfo>());
    m_shrine=new Shrine(this,0,QVector<ShrineLevelInfo>());
    m_seclusion=new Seclusion(this,0,QVector<SeclusionLevelInfo>());
    m_powerplant=new Powerplant(this,1,QVector<PowerplantLevelInfo>());
    m_factory=new Factory(this,1,QVector<FactoryLevelInfo>());
    m_coolRoom=new CoolRoom(this,1,QVector<CoolRoomLevelInfo>());
    m_storageRoom=new StorageRoom(this,1,QVector<StorageRoomLevelInfo>());
    m_aetheriteSilo=new AetheriteSilo(this,1,QVector<AetheriteSiloLevelInfo>());
    m_barracks=new Barracks(this,1,QVector<BarracksLevelInfo>());
    m_dockingStation=new DockingStation(this,0,QVector<DockingStationLevelInfo>());

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
}

void Base::loadSaveData(const SaveData &data) noexcept
{
    m_buildingLevels.insert(BaseEnums::B_CentralUnit,data.buildings.levels.centralUnit);
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

    m_powerplant->setCurrentCycles(data.buildings.cyclesSet.powerplant);
    m_factory->setCurrentCycles(data.buildings.cyclesSet.factory);

    m_centralUnit->setIsBeingUpgraded(data.buildings.upgrading.centralUnit);
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

    //TODO slots

    m_energy=data.resources.energy;
    m_foodSupplies=data.resources.foodSupplies;
    m_buildingMaterials=data.resources.buildingMaterials;
    m_aetherite=data.resources.aetheriteOre;

    m_gameClock->clearAlarms();
    for (int i=0;i<data.alarms.buildingUpgrades.size();++i)
    {
        m_gameClock->addAlarm(data.alarms.buildingUpgrades[i].first, static_cast<TimerAlarm*>(new BuildingUpgradeTimerAlarm (data.alarms.buildingUpgrades[i].second.buildingName(), data.alarms.buildingUpgrades[i].second.buildingLevel())));
    }

    m_gameClock->updateClock(data.overall.lastKnownDate, data.overall.lastKnownDay, data.overall.lastKnownHour, data.overall.lastKnownMinute);
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

    //TODO slots

    data.resources.energy=m_energy;
    data.resources.foodSupplies=m_foodSupplies;
    data.resources.buildingMaterials=m_buildingMaterials;
    data.resources.aetheriteOre=m_aetherite;

    m_gameClock->saveCurrentDate();
    data.overall.lastKnownDate=QDateTime::currentDateTime();
    data.overall.lastKnownDay=m_gameClock->currentDay();
    data.overall.lastKnownHour=m_gameClock->currentHour();
    data.overall.lastKnownMinute=m_gameClock->currentMin();

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
