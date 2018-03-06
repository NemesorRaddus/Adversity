#pragma once

#include <QObject>
#include <QVector>

#include "basemanagerinterface.h"

class Equipment;

class EquipmentManager : public QObject, public BaseManagerInterface
{
    Q_OBJECT

    Q_PROPERTY(Equipment* preparedAvailableEquipment MEMBER m_preparedAvailableEquipment)

    friend class H4X;
    friend class Base;

public:
	explicit EquipmentManager(Base *base) noexcept;

    void initializeForNewBase() noexcept final;

    inline QVector <Equipment *> &availableEquipment() noexcept
    {
        return m_availableEquipment;
    }
    Q_INVOKABLE inline unsigned amountOfAvailableEquipment() const noexcept
    {
        return m_availableEquipment.size();
    }
    Q_INVOKABLE unsigned amountOfAvailableArmors() const noexcept;
    Q_INVOKABLE unsigned amountOfAvailableWeaponsTools() const noexcept;
    Q_INVOKABLE void prepareAvailableEquipment(unsigned index) noexcept;

private:
    QVector <Equipment *> m_availableEquipment;
    Equipment *m_preparedAvailableEquipment;
};
