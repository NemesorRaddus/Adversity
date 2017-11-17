#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"
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

typedef QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > DockingStationTradingTables;

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
    explicit DockingStation(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

    Q_INVOKABLE inline int useCostInEnergy() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInBuildingMaterials() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInAetherite() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int recruitsAmount() const noexcept;
    Q_INVOKABLE int recruitsAmountAfterUpgrade() const noexcept;
    Q_INVOKABLE int readyRecruitsAmount() const noexcept;
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
    Q_INVOKABLE int waitingTime() const noexcept;
    Q_INVOKABLE int waitingTimeAfterUpgrade() const noexcept;

    Q_INVOKABLE int profitability() const noexcept;
    Q_INVOKABLE int profitabilityAfterUpgrade() const noexcept;

    Q_INVOKABLE int equipmentsAmount() const noexcept;
    Q_INVOKABLE int equipmentsAmountAfterUpgrade() const noexcept;

    Q_INVOKABLE int maxTier() const noexcept;
    Q_INVOKABLE int maxTierAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <DockingStationLevelInfo *> &info) noexcept;
    void setTradingTables(const DockingStationTradingTables &tradingTables) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    unsigned calculateTransaction(BaseEnums::Resource sourceRes, BaseEnums::Resource targetRes, unsigned sourceAmount) const noexcept;
    Q_INVOKABLE unsigned calculateTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) const noexcept;

    Q_INVOKABLE void startTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) noexcept;
    void handleActiveTransactions() noexcept;
    inline const QVector <QPair <ActiveTransaction, unsigned> > &activeTransactions() const noexcept
    {
        return m_activeTransactions;
    }

    QVector <QString> availableEquipmentsNames() const noexcept;
    Q_INVOKABLE unsigned readyEquipmentsAmount() const noexcept;
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
    DockingStationLevelInfo *currentLevelInfo() const noexcept;
    DockingStationLevelInfo *nextLevelInfo() const noexcept;

    void loadRecruits() noexcept;
    void clearRecruits() noexcept;
    void addRecruitFromSave(Mercenary *mercenary) noexcept;
    void setActiveTransactionsFromSave(const QVector <QPair <ActiveTransaction, unsigned> > &transactions) noexcept;
    void addArrivingMercenaryFromSave(const QPair <Mercenary *, unsigned> &arrMercenary) noexcept;
    void loadEquipments() noexcept;
    void clearEquipments() noexcept;
    void addEquipmentFromSave(Equipment *eq) noexcept;
    void addArrivingEquipmentFromSave(const QPair <Equipment *, unsigned> &arrEq) noexcept;

    DockingStationTradingTables m_tradingTables;
    QVector <Mercenary *> m_recruits;
    Mercenary *m_recruitPreparedForQML;
    QVector <QPair <Mercenary *, unsigned> > m_arrivingMercenaries;//mercenary, ETA
    QVector <QPair <ActiveTransaction, unsigned> > m_activeTransactions;
    QVector <Equipment *> m_equipments;
    Equipment *m_equipmentPreparedForQML;
    QVector <QPair <Equipment *, unsigned> > m_arrivingEquipments;//eq, ETA
};
