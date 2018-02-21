#pragma once

#include <QMap>
#include <QObject>

#include "basemanagerinterface.h"

class MercenariesContainer;

class MercenariesManager : public QObject, public BaseManagerInterface
{
    Q_OBJECT

    Q_PROPERTY(MercenariesContainer* mercenaries MEMBER m_mercenaries)

    friend class H4X;
    friend class Base;

public:
    explicit MercenariesManager(Base * base) noexcept;
    ~MercenariesManager() noexcept;

    void initializeForNewBase() noexcept final;

    inline MercenariesContainer *mercenaries() noexcept
    {
        return m_mercenaries;
    }
    inline QMap <QString, unsigned> &mercenaryDockingStationBans() noexcept
    {
        return m_mercenaryDockingStationBans;
    }
    void recalculateAmountOfMercenarySlots() const noexcept;

private:
    MercenariesContainer *m_mercenaries;
    QMap <QString, unsigned> m_mercenaryDockingStationBans;//in days; when banned, mercenary won't appear in docking station menu
};
