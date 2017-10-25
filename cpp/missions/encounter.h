#pragma once

#include <QVector>

#include <QString>

class Event;
class EncounterReport;
class Time;
class Mercenary;

class Encounter
{
public:
    explicit Encounter(const QString &name, Event *rootEvent, unsigned probability) noexcept;

    EncounterReport *execute(Mercenary *mercenary, const Time &currentTime) const noexcept;

    inline QString name() const noexcept
    {
        return m_name;
    }

    inline unsigned probability() const noexcept
    {
        return m_probability;
    }

private:
    QString m_name;
    Event *m_rootEvent;
    unsigned m_probability;
};

class EncountersContainer
{
public:
    ~EncountersContainer() noexcept;

    void addEncounter(Encounter *enc) noexcept;
    void removeEncounter(unsigned index) noexcept;
    inline const QVector <Encounter *> &encounters() const noexcept
    {
        return m_encounters;
    }

private:
    QVector <Encounter *> m_encounters;
};
