#include "dockingstation.h"

#include <QDataStream>

#include "base/base.h"
#include "base/managers/equipmentmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "general/game.h"
#include "general/randomizer.h"
#include "logging/loggersprovider.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/events/event.h"
#include "reports/basereports.h"
#include "reports/unifiedreport.h"

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
    transaction.sourceRes = static_cast<BaseEnums::Resource>(n);

    stream>>n;
    transaction.targetRes = static_cast<BaseEnums::Resource>(n);

    stream>>ii;
    transaction.sourceAmount = ii;

    stream>>ii;
    transaction.targetAmount = ii;

    return stream;
}

DockingStation::DockingStation(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_DockingStation, base, level, levelsInfo) {}

int DockingStation::recruitsAmount() const noexcept
{
    return currentLevelInfo()->recruitsAmount;
}

int DockingStation::recruitsAmountAfterUpgrade() const noexcept
{
    return nextLevelInfo()->recruitsAmount;
}

int DockingStation::readyRecruitsAmount() const noexcept
{
    return m_recruits.size();
}

void DockingStation::prepareRecruits() noexcept
{
    clearRecruits();
    loadRecruits();
    prepareRecruitForQML(0);
}

void DockingStation::prepareRecruitForQML(unsigned slot) noexcept
{
    if (slot < m_recruits.size())
        m_recruitPreparedForQML = m_recruits[slot];
    else
        m_recruitPreparedForQML = nullptr;
}

void DockingStation::hireMercenary(const QString &name, unsigned eta) noexcept
{
    if (base()->mercenaries()->mercenaries()->canAddMercenary())
    {
        for (int i=0;i < m_recruits.size();++i)
            if (m_recruits[i]->name() == name)
            {
                if (eta > 0)
                {
                    m_recruits[i]->setCurrentActivity(MercenaryEnums::CA_Arriving);
                    base()->mercenaries()->mercenaries()->addMercenary(m_recruits[i]);
                    m_arrivingMercenaries.push_back({m_recruits[i],eta});
                    if (m_recruitPreparedForQML == m_recruits[i])
                    {
                        if (m_recruits.size() > i+1)
                            m_recruitPreparedForQML = m_recruits[i+1];
                        else if (i > 0)
                            m_recruitPreparedForQML = m_recruits[i-1];
                        else
                            m_recruitPreparedForQML = nullptr;
                    }
                    m_recruits.remove(i);
                    break;
                }
                else//instant
                {
                    base()->mercenaries()->mercenaries()->addMercenary(m_recruits[i]);
                    if (m_recruitPreparedForQML == m_recruits[i])
                    {
                        if (m_recruits.size() > i+1)
                            m_recruitPreparedForQML = m_recruits[i+1];
                        else if (i > 0)
                            m_recruitPreparedForQML = m_recruits[i-1];
                        else
                            m_recruitPreparedForQML = nullptr;
                    }
                    m_recruits.remove(i);
                    break;
                }
            }
    }
}

void DockingStation::doRecrutationStuff() noexcept
{
    for (int i=0;i < m_arrivingMercenaries.size();++i)
    {
        if (m_arrivingMercenaries[i].second == 0)
        {
            Mercenary *h = m_arrivingMercenaries[i].first;//antibug thing, leave it as it is
            base()->reports()->addReport(new UnifiedReport(new MercenaryArrivalReport(h->pathToArt(), h->name(), base()->gameClock()->currentTime())));
            h->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_arrivingMercenaries.remove(i);
        }
        else
            --m_arrivingMercenaries[i].second;
    }
}

QStringList DockingStation::getRecruitsNames() const noexcept
{
    QStringList r;
    for (int i=0;i < m_recruits.size();++i)
        r+=m_recruits[i]->name();
    return r;
}

void DockingStation::cancelMercenaryArrival(const QString &name) noexcept
{
    for (int i=0;i < m_arrivingMercenaries.size();++i)
        if (m_arrivingMercenaries[i].first->name() == name)
        {
            m_arrivingMercenaries.remove(i);
            break;
        }
}

int DockingStation::waitingTime() const noexcept
{
    return currentLevelInfo()->waitingTime;
}

int DockingStation::waitingTimeAfterUpgrade() const noexcept
{
    return nextLevelInfo()->waitingTime;
}

int DockingStation::profitability() const noexcept
{
    return currentLevelInfo()->profitability;
}

int DockingStation::profitabilityAfterUpgrade() const noexcept
{
    return nextLevelInfo()->profitability;
}

int DockingStation::equipmentsAmount() const noexcept
{
    return currentLevelInfo()->equipmentsAmount;
}

int DockingStation::equipmentsAmountAfterUpgrade() const noexcept
{
    return nextLevelInfo()->equipmentsAmount;
}

int DockingStation::maxTier() const noexcept
{
    return currentLevelInfo()->maxTier;
}

int DockingStation::maxTierAfterUpgrade() const noexcept
{
    return nextLevelInfo()->maxTier;
}

void DockingStation::setLevelsInfo(const QVector < DockingStationLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

void DockingStation::setTradingTables(const QVector<QMap<QPair < BaseEnums::Resource, BaseEnums::Resource>, float> > &tradingTables) noexcept
{
    m_tradingTables = tradingTables;
}

unsigned DockingStation::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_DockingStation,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

unsigned DockingStation::calculateTransaction(BaseEnums::Resource sourceRes, BaseEnums::Resource targetRes, unsigned sourceAmount) const noexcept
{
    return m_tradingTables.value(currentLevelInfo()->profitability).value({sourceRes,targetRes}) * sourceAmount;
}

unsigned DockingStation::calculateTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) const noexcept
{
    return ceilf(static_cast<float>(targetAmount) / m_tradingTables.value(currentLevelInfo()->profitability).value({static_cast<BaseEnums::Resource>(sourceRes), static_cast<BaseEnums::Resource>(targetRes)}));
}

void DockingStation::startTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) noexcept
{
    unsigned sA = calculateTransaction(sourceRes, targetRes, targetAmount);
    BaseEnums::Resource sR = static_cast<BaseEnums::Resource>(sourceRes);
    BaseEnums::Resource tR = static_cast<BaseEnums::Resource>(targetRes);

    if (sR == BaseEnums::R_Energy)
        base()->resources()->setCurrentEnergyAmount(base()->resources()->currentEnergyAmount() - sA);
    else if (sR == BaseEnums::R_FoodSupplies)
        base()->resources()->setCurrentFoodSuppliesAmount(base()->resources()->currentFoodSuppliesAmount() - sA);
    else if (sR == BaseEnums::R_BuildingMaterials)
        base()->resources()->setCurrentBuildingMaterialsAmount(base()->resources()->currentBuildingMaterialsAmount() - sA);
    else
        base()->resources()->setCurrentAetheriteAmount(base()->resources()->currentAetheriteAmount() - sA);

    m_activeTransactions.push_back({{sR,tR,sA,targetAmount},currentLevelInfo()->waitingTime});
    LoggersProvider::buildingsLogger()->trace("[{}] Docking Station: started a transaction:",base()->gameClock()->currentTime().toQString().toStdString());
    LoggersProvider::buildingsLogger()->trace("    Source: {} {}",sA,BaseEnums::fromResourceEnumToQString(sR).toStdString());
    LoggersProvider::buildingsLogger()->trace("    Target: {} {}",targetAmount,BaseEnums::fromResourceEnumToQString(tR).toStdString());
}

void DockingStation::handleActiveTransactions() noexcept
{
    for (int i=0;i < m_activeTransactions.size();++i)
    {
        if (m_activeTransactions[i].second == 0)
        {
            base()->reports()->addReport(new UnifiedReport(new TradeCompletionReport(m_activeTransactions[i].first.targetRes, m_activeTransactions[i].first.targetAmount, base()->gameClock()->currentTime())));

            if (m_activeTransactions[i].first.targetRes == BaseEnums::R_Energy)
                base()->resources()->setCurrentEnergyAmount(base()->resources()->currentEnergyAmount() + m_activeTransactions[i].first.targetAmount);
            else if (m_activeTransactions[i].first.targetRes == BaseEnums::R_FoodSupplies)
                base()->resources()->setCurrentFoodSuppliesAmount(base()->resources()->currentFoodSuppliesAmount() + m_activeTransactions[i].first.targetAmount);
            else if (m_activeTransactions[i].first.targetRes == BaseEnums::R_BuildingMaterials)
                base()->resources()->setCurrentBuildingMaterialsAmount(base()->resources()->currentBuildingMaterialsAmount() + m_activeTransactions[i].first.targetAmount);
            else
                base()->resources()->setCurrentAetheriteAmount(base()->resources()->currentAetheriteAmount() + m_activeTransactions[i].first.targetAmount);

            m_activeTransactions.remove(i);
            --i;
        }
        else
            --m_activeTransactions[i].second;
    }
}

QVector <QString> DockingStation::availableEquipmentsNames() const noexcept
{
    QVector <QString> r;
    for (int i=0;i < m_equipments.size();++i)
        r+=m_equipments[i]->name();
    return r;
}

unsigned DockingStation::readyEquipmentsAmount() const noexcept
{
    return m_equipments.size();
}

void DockingStation::prepareEquipments() noexcept
{
    clearEquipments();
    loadEquipments();
    m_equipmentPreparedForQML = m_equipments.value(0,nullptr);
}

void DockingStation::prepareEquipmentForQML(unsigned pos) noexcept
{
    if (pos < m_equipments.size())
        m_equipmentPreparedForQML = m_equipments[pos];
}

void DockingStation::buyEquipment(unsigned pos, unsigned eta) noexcept
{
    if (pos < m_equipments.size())
    {
        base()->resources()->decreaseAetheriteAmount(m_equipments[pos]->buyingAetheriteCost());
        if (eta > 0)
        {
            m_arrivingEquipments.push_back({m_equipments[pos],eta});
            if (m_equipmentPreparedForQML == m_equipments[pos])
            {
                if (m_equipments.size() > pos+1)
                    m_equipmentPreparedForQML = m_equipments[pos+1];
                else if (pos > 0)
                    m_equipmentPreparedForQML = m_equipments[pos-1];
                else
                    m_equipmentPreparedForQML = nullptr;
            }
            m_equipments.remove(pos);
        }
        else//instant
        {
            base()->equipment()->availableEquipment().push_back(m_equipments[pos]);
            if (m_equipmentPreparedForQML == m_equipments[pos])
            {
                if (m_equipments.size() > pos+1)
                    m_equipmentPreparedForQML = m_equipments[pos+1];
                else if (pos > 0)
                    m_equipmentPreparedForQML = m_equipments[pos-1];
                else
                    m_equipmentPreparedForQML = nullptr;
            }
            m_equipments.remove(pos);
        }
    }
}

void DockingStation::doBuyingEquipmentStuff() noexcept
{
    for (int i=0;i < m_arrivingEquipments.size();++i)
    {
        if (m_arrivingEquipments[i].second == 0)
        {
            Equipment *eq = m_arrivingEquipments[i].first;
            base()->reports()->addReport(new UnifiedReport(new EquipmentArrivalReport(eq->name(), base()->gameClock()->currentTime())));
            base()->equipment()->availableEquipment().push_back(eq);
            m_arrivingEquipments.remove(i);
        }
        else
            --m_arrivingEquipments[i].second;
    }
}

int DockingStation::remainingDaysUntilMercenaryArrival(const QString &mercenaryName) const noexcept
{
    for (int i=0;i < m_arrivingMercenaries.size();++i)
        if (m_arrivingMercenaries[i].first->name() == mercenaryName)
            return m_arrivingMercenaries[i].second;

    return -1;
}

DockingStationLevelInfo *DockingStation::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<DockingStationLevelInfo > ();
}

DockingStationLevelInfo *DockingStation::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<DockingStationLevelInfo > ();
}

void DockingStation::loadRecruits() noexcept
{
    QStringList names{base()->gameObject()->assetsPool().allMercenaries()};//load all mercs names
    for (int i=0;i < base()->mercenaries()->mercenaries()->mercenaries().size();++i)//remove mercs that are already hired
        names.removeAt(names.indexOf(base()->mercenaries()->mercenaries()->mercenaries()[i]->name()));
    for (int i=0;i < names.size();)//remove mercs banned in DoSt
    {
        if (base()->mercenaries()->mercenaryDockingStationBans().contains(names[i]))
            names.removeAt(i);
        else
            ++i;
    }
    for (int i=0;i < recruitsAmount() && !names.isEmpty();++i)//add random recruits
    {
        unsigned indexOfRecruit = Randomizer::randomBetweenAAndB(0,names.size()-1);
        base()->gameObject()->assetsPool().loadMercenaryNamedFromList(names[indexOfRecruit]);
        for (int j=0;j < base()->gameObject()->assetsPool().loadedMercenaries().size();++j)
            if (base()->gameObject()->assetsPool().loadedMercenaries()[j]->name() == names[indexOfRecruit])
            {
                m_recruits.push_back(base()->gameObject()->assetsPool().loadedMercenaries()[j]);
                break;
            }
        names.removeAt(indexOfRecruit);
    }
}

void DockingStation::clearRecruits() noexcept
{
    for (int i=0;i < m_recruits.size();++i)
        if (m_recruits[i] != nullptr)//TODO possibly remove that if
            for (int j=0;j < base()->gameObject()->assetsPool().loadedMercenaries().size();++j)
                if (base()->gameObject()->assetsPool().loadedMercenaries()[j]->name() == m_recruits[i]->name())
                {
                    base()->gameObject()->assetsPool().unloadMercenary(j);
                    break;
                }
    m_recruits.clear();

    m_recruitPreparedForQML = nullptr;
}

void DockingStation::addRecruitFromSave(Mercenary *mercenary) noexcept
{
    m_recruits.push_back(mercenary);
}

void DockingStation::setActiveTransactionsFromSave(const QVector<QPair < ActiveTransaction, unsigned> > &transactions) noexcept
{
    m_activeTransactions = transactions;
}

void DockingStation::addArrivingMercenaryFromSave(const QPair < Mercenary *, unsigned> &arrMercenary) noexcept
{
    m_arrivingMercenaries+=arrMercenary;
}

void DockingStation::loadEquipments() noexcept
{
    auto allEq = base()->gameObject()->assetsPool().equipment();
    for (int i=0;i < allEq.size();)
    {
        if (allEq[i]->tier() <= maxTier())
            ++i;
        else
            allEq.remove(i);
    }
    for (int i=0;i < equipmentsAmount();++i)
    {
        unsigned indexOfEquipment = Randomizer::randomBetweenAAndB(0,allEq.size()-1);
        m_equipments.push_back(base()->gameObject()->assetsPool().makeEquipmentNamed(allEq[indexOfEquipment]->name()));
    }
}

void DockingStation::clearEquipments() noexcept
{
    for (int i=0;i < m_equipments.size();++i)
        delete m_equipments[i];

    m_equipments.clear();

    m_equipmentPreparedForQML = nullptr;
}

void DockingStation::addEquipmentFromSave(Equipment *eq) noexcept
{
    m_equipments.push_back(eq);
}

void DockingStation::addArrivingEquipmentFromSave(const QPair < Equipment *, unsigned> &arrEq) noexcept
{
    m_arrivingEquipments+=arrEq;
}
