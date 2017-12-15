#pragma once

#include <QVector>
#include <QMap>
#include <QObject>

#include "base/buildings/enums.h"
#include "base/buildings/building.h"

class BuildingsManager;
class EquipmentManager;
class MercenariesManager;
class MissionsManager;
class ReportsManager;
class ResourcesManager;
class Database;
class GameClock;
class Game;
class SaveData;

class Base : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BuildingsManager* buildings MEMBER m_buildingsManager)
    Q_PROPERTY(EquipmentManager* equipment MEMBER m_equipmentManager)
    Q_PROPERTY(MercenariesManager* mercenaries MEMBER m_mercenariesManager)
    Q_PROPERTY(MissionsManager* missions MEMBER m_missionsManager)
    Q_PROPERTY(ReportsManager* reports MEMBER m_reportsManager)
    Q_PROPERTY(ResourcesManager* resources MEMBER m_resourcesManager)

    Q_PROPERTY(GameClock* gameClock MEMBER m_gameClock)

    Q_PROPERTY(Database* database MEMBER m_database)

    friend class H4X;

public:
    explicit Base(Game *gameObject) noexcept;
    void setupNewBase() noexcept;
    ~Base() noexcept;

    //save
    void loadSaveData(const SaveData &data) noexcept;//only use before proper game start
    SaveData getSaveData() noexcept;

    Q_INVOKABLE void startNewDay() noexcept;//not used in QML

    Q_INVOKABLE void startNewWeek() noexcept;//not used in QML

    inline BuildingsManager *buildings() noexcept
    {
        return m_buildingsManager;
    }
    inline EquipmentManager *equipment() noexcept
    {
        return m_equipmentManager;
    }
    inline MercenariesManager *mercenaries() noexcept
    {
        return m_mercenariesManager;
    }
    inline MissionsManager *missions() noexcept
    {
        return m_missionsManager;
    }
    inline ReportsManager *reports() noexcept
    {
        return m_reportsManager;
    }
    inline ResourcesManager *resources() noexcept
    {
        return m_resourcesManager;
    }

    inline Database *database() noexcept
    {
        return m_database;
    }

    //game clock
    inline GameClock *gameClock() noexcept
    {
        return m_gameClock;
    }

    //game
    inline Game *gameObject() noexcept
    {
        return m_gameObject;
    }

private:
    BuildingsManager *m_buildingsManager;
    EquipmentManager *m_equipmentManager;
    MercenariesManager *m_mercenariesManager;
    MissionsManager *m_missionsManager;
    ReportsManager *m_reportsManager;
    ResourcesManager *m_resourcesManager;

    //game clock/timer
    void activateBuildingsAtDayEnd() noexcept;
    void handleMercenariesAtDayEnd() noexcept;
    void handleMercenariesAtWeekEnd() noexcept;

    GameClock *m_gameClock;

    Database *m_database;

    //game
    void loadAssets() noexcept;

    Game *m_gameObject;
    bool m_freezeGameProgress;
};
