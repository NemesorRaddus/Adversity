#pragma once

#include "event.h"

typedef QString EventReport;

class MultiEvent final : public Event
{
public:
    MultiEvent(const QVector <Event *> &events, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : Event(EventEnums::T_Multi,text,dbEntries), m_eventsToExecute(events) {}
    ~MultiEvent() noexcept;

    QVector <EventReport> executeSpecificOps(Mercenary *context) noexcept final;

private:
    QVector <Event *> m_eventsToExecute;
};

class PossibilityEvent final : public Event
{
public:
    explicit PossibilityEvent(Chance chance, Event *event, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~PossibilityEvent() noexcept;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    Chance m_chance;
    Event *m_event;
};
