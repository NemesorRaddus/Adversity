#pragma once

#include "event.h"
#include "equipment/enums.h"
#include "missions/events/value_scripts/expression.h"

class CheckEventResults
{
    friend class CheckEventResultsBuilder;

public:
    ~CheckEventResults() noexcept;

    inline QVector <QPair <Event *, Chance> > positive() const noexcept
    {
        return m_positive;
    }
    inline QVector <QPair <Event *, Chance> > negative() const noexcept
    {
        return m_negative;
    }

private:
    CheckEventResults() noexcept {}

    QVector <QPair <Event *, Chance> > m_positive;
    QVector <QPair <Event *, Chance> > m_negative;
};

class CheckEventResultsBuilder
{
public:
    CheckEventResultsBuilder() noexcept;
    ~CheckEventResultsBuilder() noexcept;

    CheckEventResults *get() noexcept;

    void addPositive(const QPair <Event *, Chance> &result) noexcept;
    void addNegative(const QPair <Event *, Chance> &result) noexcept;

private:
    void validateJustBeforeReturning() noexcept;

    CheckEventResults *m_results;
};

class CheckEvent : public Event
{
public:
    ~CheckEvent() noexcept = default;

    inline auto eventResultType() const noexcept
    {
        return m_eventSubtype;
    }
    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override = 0;

protected:
    explicit CheckEvent(EventEnums::Check eventSubtype, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;

    CheckEventResults *m_results;

private:
    EventEnums::Check m_eventSubtype;
};

class ValueCheckEvent final : public CheckEvent
{
public:
    explicit ValueCheckEvent(const Expression &condition, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~ValueCheckEvent() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    Expression m_condition;
};

class EquipmentCheckEvent final : public CheckEvent
{
public:
    explicit EquipmentCheckEvent(EquipmentEnums::Category neededEq, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~EquipmentCheckEvent() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    EquipmentEnums::Category m_neededEquipment;
};
