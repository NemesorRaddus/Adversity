#pragma once

#include <QVector>

#include "libs/RBoundedValue_v0_1_1-Beta/rboundedvalue.h"

#include "enums.h"

typedef QString EventReport;
class Mercenary;

typedef RBoundedValue<int, 0, 100, false> Chance;

class Event
{
public:
    virtual ~Event() noexcept = default;

    inline EventEnums::Type eventType() const noexcept
    {
        return m_eventType;
    }
    inline QString eventText() const noexcept
    {
        return m_eventText;
    }
    inline QVector <QString> unlockedDatabaseEntries() const noexcept
    {
        return m_unlockedDatabaseEntries;
    }

    QVector <EventReport> execute(Mercenary *context) noexcept;

protected:
    explicit Event(EventEnums::Type eventType, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : m_eventType(eventType), m_eventText(text), m_unlockedDatabaseEntries(dbEntries) {}

    void setEventText(const QString &text) noexcept;

private:
    void unlockDatabaseEntries(Mercenary *context) noexcept;
    virtual QVector <EventReport> executeSpecificOps(Mercenary *context) noexcept = 0;

    EventEnums::Type m_eventType;
    QString m_eventText;
    QVector <QString> m_unlockedDatabaseEntries;
};
