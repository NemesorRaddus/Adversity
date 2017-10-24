#pragma once

#include <QObject>

class Encounter;
class EncountersContainer;

struct LandInfo
{
    QString name;
    QString description;
    QPair <int, int> position;
};

class Land : public QObject
{
    Q_OBJECT

    friend class LandBuilder;

public:
    explicit Land(const LandInfo &info) noexcept;
    ~Land() noexcept;

    Q_INVOKABLE inline QString name() const noexcept
    {
        return m_info.name;
    }
    Q_INVOKABLE inline QString description() const noexcept
    {
        return m_info.description;
    }
    Q_INVOKABLE inline int posX() const noexcept
    {
        return m_info.position.first;
    }
    Q_INVOKABLE inline int posY() const noexcept
    {
        return m_info.position.second;
    }

    Encounter *makeRandomEncounter() const noexcept;
    inline const EncountersContainer *encounters() const noexcept
    {
        return m_encounters;
    }

private:
    void setInfo(const LandInfo &info) noexcept;

    void setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept;

    LandInfo m_info;
    EncountersContainer *m_encounters;
};

class LandBuilder
{
public:
    LandBuilder() noexcept;
    ~LandBuilder() noexcept;

    Land *getLand() noexcept;
    void resetLand() noexcept;

    void setInfo(const LandInfo &info) noexcept;

    void setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept;

private:
    Land *m_land;
};

class LandsInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Land* preparedLand MEMBER m_preparedLand)

public:
    explicit LandsInfo(const QVector <Land *> *lands) noexcept;

    Q_INVOKABLE unsigned amountOfLands() const noexcept;

    Q_INVOKABLE void prepareLandAt(unsigned index) noexcept;

private:
    const QVector <Land *> *m_lands;
    Land *m_preparedLand;
};
