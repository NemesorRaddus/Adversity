#pragma once

#include <QVariant>

#include "event.h"
#include "base/enums.h"
#include "equipment/enums.h"
#include "mercenaries/enums.h"
#include "missions/events/value_scripts/valuerange.h"

class Equipment;

class ActionEvent : public Event
{
public:
    virtual ~ActionEvent() noexcept = default;

    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override = 0;
    EventEnums::Action eventSubtype() const noexcept
    {
        return m_eventSubtype;
    }

protected:
    explicit ActionEvent(EventEnums::Action eventSubtype, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : Event(EventEnums::T_Action,text,dbEntries), m_eventSubtype(eventSubtype) {}

private:
    EventEnums::Action m_eventSubtype;
};

class NullEventResult final : public ActionEvent
{
public:
    NullEventResult(QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_Null,text,dbEntries) {}
    ~NullEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *) noexcept;
};

class GiveHealthEventResult final : public ActionEvent
{
public:
    explicit GiveHealthEventResult(const ValueRange &addedValue, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveHealthEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_value;
};

class GiveStressEventResult final : public ActionEvent
{
public:
    explicit GiveStressEventResult(const ValueRange &addedValue, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveStressEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_value;
};

struct AttributeModification
{
    enum Type
    {
        T_Add,
        T_Subtract,
        T_Multiply,
        T_Divide,
        T_Set,
        T_END
    };

    MercenaryEnums::Attribute attribute;
    Type type;
    QVariant value;
    int duration;
};

struct AttributeModificationHelper
{
    MercenaryEnums::Attribute attribute;
    AttributeModification::Type type;
    ValueRange expressionRange;
    ValueRange durationRange;
};

class ModifyAttributeEventResult final : public ActionEvent
{
public:
    explicit ModifyAttributeEventResult(const AttributeModificationHelper &modification, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~ModifyAttributeEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    AttributeModificationHelper m_modification;
};

class KillMercenaryEventResult final : public ActionEvent
{
public:
    KillMercenaryEventResult(QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_KillMercenary,text,dbEntries) {}
    ~KillMercenaryEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;
};

class AddEquipmentEventResult : public ActionEvent
{
public:
    explicit AddEquipmentEventResult(Equipment *equipment, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_AddEquipment,text,dbEntries), m_equipmentToAdd(equipment) {}
    virtual ~AddEquipmentEventResult() noexcept = default;

    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override;

    Equipment *equipmentToAdd() const noexcept
    {
        return m_equipmentToAdd;
    }

protected:
    Equipment *m_equipmentToAdd;
};

class AddEquipmentRandomEventResult final : public AddEquipmentEventResult
{
public:
    AddEquipmentRandomEventResult(ValueRange tier, int equipmentTypeFlags, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~AddEquipmentRandomEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_tier;
    int m_eqTypes;
};

class RemoveEquipmentEventResult final : public ActionEvent
{
public:
    explicit RemoveEquipmentEventResult(EquipmentEnums::Type type, int slot, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_RemoveEquipment,text,dbEntries), m_equipmentType(type), m_equipmentSlot(slot) {}
    ~RemoveEquipmentEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    auto equipmentType() const noexcept
    {
        return m_equipmentType;
    }
    int equipmentSlot() const noexcept
    {
        return m_equipmentSlot;
    }

private:
    EquipmentEnums::Type m_equipmentType;
    int m_equipmentSlot;
};

class GiveResourceEventResult : public ActionEvent
{
public:
    explicit GiveResourceEventResult(BaseEnums::Resource resource, const ValueRange &amount, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    virtual ~GiveResourceEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    inline BaseEnums::Resource resource() const noexcept
    {
        return m_resource;
    }
    inline ValueRange addedAmount() const noexcept
    {
        return m_amount;
    }

protected:
    BaseEnums::Resource m_resource;
    ValueRange m_amount;
};

class GiveResourceRandomEventResult final : public GiveResourceEventResult
{
public:
    explicit GiveResourceRandomEventResult(const ValueRange &amount, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveResourceRandomEventResult() noexcept = default;
};

class NoSignalEventResult final : public ActionEvent
{
public:
    explicit NoSignalEventResult(const ValueRange &durationInDays, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~NoSignalEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    inline ValueRange durationInDays() const noexcept
    {
        return m_durationInDays;
    }

private:
    ValueRange m_durationInDays;
};
