#pragma once

#include <QVector>

#include "building.h"
#include "mercenaries/mercenary.h"
#include "equipment/equipment.h"
#include "base/enums.h"

struct DockingStationLevelInfo : public BuildingLevelInfo
{
    DockingStationLevelInfo()
        : recruitsAmount(0), waitingTime(0), profitability(0), equipmentsAmount(0), maxTier(0) {}

    unsigned recruitsAmount;
    unsigned waitingTime;
    unsigned profitability;
    unsigned equipmentsAmount;
    unsigned maxTier;
};

struct ActiveTransaction
{
    ActiveTransaction()
        : sourceRes(BaseEnums::R_Energy), targetRes(BaseEnums::R_Energy), sourceAmount(0), targetAmount(0){}
    ActiveTransaction(BaseEnums::Resource _sourceRes, BaseEnums::Resource _targetRes, unsigned _sourceAmount, unsigned _targetAmount)
        : sourceRes(_sourceRes), targetRes(_targetRes), sourceAmount(_sourceAmount), targetAmount(_targetAmount){}

    BaseEnums::Resource sourceRes, targetRes;
    unsigned sourceAmount, targetAmount;
};

QDataStream &operator<<(QDataStream &stream, const ActiveTransaction &transaction) noexcept;
QDataStream &operator>>(QDataStream &stream, ActiveTransaction &transaction) noexcept;

class DockingStation : public Building
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* recruitPreparedForQML MEMBER m_recruitPreparedForQML)
    Q_PROPERTY(Equipment* equipmentPreparedForQML MEMBER m_equipmentPreparedForQML)

    friend class Base;

public:
    explicit DockingStation(Base *base, unsigned level, const QVector <DockingStationLevelInfo> &levelsInfo) noexcept;

    Q_INVOKABLE unsigned maxLevel() const noexcept
    {
        return m_levelsInfo.size()-1;
    }

    Q_INVOKABLE int basicCostInEnergy() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).basicCostInEnergy;
    }
    Q_INVOKABLE int basicCostInEnergyAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).basicCostInEnergy;
    }
    Q_INVOKABLE int useCostInEnergy() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInBuildingMaterials() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int recruitsAmount() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).recruitsAmount;
    }
    Q_INVOKABLE int recruitsAmountAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).recruitsAmount;
    }
    Q_INVOKABLE int readyRecruitsAmount() const noexcept
    {
        return m_recruits.size();
    }
    void prepareRecruits() noexcept;
    Q_INVOKABLE void prepareRecruitForQML(unsigned slot) noexcept;
    Q_INVOKABLE void hireMercenary(const QString &name, unsigned eta) noexcept;
    void doRecrutationStuff() noexcept;
    QStringList getRecruitsNames() const noexcept;
    QVector <QPair <Mercenary *, unsigned> > arrivingMercenaries() noexcept
    {
        return m_arrivingMercenaries;
    }
    void cancelMercenaryArrival(const QString &name) noexcept;
    Q_INVOKABLE int waitingTime() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).waitingTime;
    }
    Q_INVOKABLE int waitingTimeAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).waitingTime;
    }

    Q_INVOKABLE int profitability() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).profitability;
    }
    Q_INVOKABLE int profitabilityAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).profitability;
    }

    Q_INVOKABLE int equipmentsAmount() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).equipmentsAmount;
    }
    Q_INVOKABLE int equipmentsAmountAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).equipmentsAmount;
    }

    Q_INVOKABLE int maxTier() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).maxTier;
    }
    Q_INVOKABLE int maxTierAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).maxTier;
    }

    void setLevelsInfo(const QVector <DockingStationLevelInfo> &info) noexcept
    {
        m_levelsInfo=info;
    }
    void setTradingTables(const QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > &tradingTables) noexcept
    {
        m_tradingTables=tradingTables;
    }

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    unsigned calculateTransaction(BaseEnums::Resource sourceRes, BaseEnums::Resource targetRes, unsigned sourceAmount) const noexcept;
    Q_INVOKABLE unsigned calculateTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) const noexcept;

    Q_INVOKABLE void startTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) noexcept;
    void handleActiveTransactions() noexcept;
    inline const QVector <QPair <ActiveTransaction, unsigned> > &activeTransactions() const noexcept
    {
        return m_activeTransactions;
    }

    QVector <QString> availableEquipmentsNames() const noexcept
    {
        QVector <QString> r;
        for (int i=0;i<m_equipments.size();++i)
            r+=m_equipments[i]->name();
        return r;
    }
    Q_INVOKABLE unsigned readyEquipmentsAmount() const noexcept
    {
        return m_equipments.size();
    }
    void prepareEquipments() noexcept;
    Q_INVOKABLE void prepareEquipmentForQML(unsigned pos) noexcept;
    Q_INVOKABLE void buyEquipment(unsigned pos, unsigned eta) noexcept;
    void doBuyingEquipmentStuff() noexcept;
    inline QVector <QPair <Equipment *, unsigned> > arrivingEquipments() noexcept
    {
        return m_arrivingEquipments;
    }

    Q_INVOKABLE int remainingDaysUntilMercenaryArrival(const QString &mercenaryName) const noexcept;

private:
    void loadRecruits() noexcept;
    void clearRecruits() noexcept;
    void addRecruitFromSave(Mercenary *mercenary) noexcept
    {
        m_recruits.push_back(mercenary);
    }
    void setActiveTransactionsFromSave(const QVector <QPair <ActiveTransaction, unsigned> > &transactions) noexcept
    {
        m_activeTransactions=transactions;
    }
    void addArrivingMercenaryFromSave(const QPair <Mercenary *, unsigned> &arrMercenary) noexcept
    {
        m_arrivingMercenaries+=arrMercenary;
    }
    void loadEquipments() noexcept;
    void clearEquipments() noexcept;
    void addEquipmentFromSave(Equipment *eq) noexcept;
    void addArrivingEquipmentFromSave(const QPair <Equipment *, unsigned> &arrEq) noexcept
    {
        m_arrivingEquipments+=arrEq;
    }

    QVector <DockingStationLevelInfo> m_levelsInfo;
    QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > m_tradingTables;
    QVector <Mercenary *> m_recruits;
    Mercenary *m_recruitPreparedForQML;
    QVector <QPair <Mercenary *, unsigned> > m_arrivingMercenaries;//mercenary, ETA
    QVector <QPair <ActiveTransaction, unsigned> > m_activeTransactions;
    QVector <Equipment *> m_equipments;
    Equipment *m_equipmentPreparedForQML;
    QVector <QPair <Equipment *, unsigned> > m_arrivingEquipments;//eq, ETA
};
