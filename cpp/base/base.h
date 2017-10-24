#pragma once

#include <QVector>
#include <QMap>
#include <QObject>

#include "base/buildings/enums.h"
#include "base/buildings/building.h"

class AetheriteSilo;
class Bar;
class Barracks;
class CentralUnit;
class CoolRoom;
class DockingStation;
class Factory;
class Gym;
class Hospital;
class Laboratory;
class PlayingField;
class Powerplant;
class Seclusion;
class Shrine;
class StorageRoom;
class TrainingGround;
class Database;
class Equipment;
class GameClock;
class Game;
class MercenariesContainer;
class Mission;
class MissionInitializer;
class SaveData;
class UnifiedReport;

class Base : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CentralUnit* centralUnit MEMBER m_centralUnit)
    Q_PROPERTY(Hospital* hospital MEMBER m_hospital)
    Q_PROPERTY(TrainingGround* trainingGround MEMBER m_trainingGround)
    Q_PROPERTY(Gym* gym MEMBER m_gym)
    Q_PROPERTY(Laboratory* laboratory MEMBER m_laboratory)
    Q_PROPERTY(PlayingField* playingField MEMBER m_playingField)
    Q_PROPERTY(Bar* bar MEMBER m_bar)
    Q_PROPERTY(Shrine* shrine MEMBER m_shrine)
    Q_PROPERTY(Seclusion* seclusion MEMBER m_seclusion)
    Q_PROPERTY(Powerplant* powerplant MEMBER m_powerplant)
    Q_PROPERTY(Factory* factory MEMBER m_factory)
    Q_PROPERTY(CoolRoom* coolRoom MEMBER m_coolRoom)
    Q_PROPERTY(StorageRoom* storageRoom MEMBER m_storageRoom)
    Q_PROPERTY(AetheriteSilo* aetheriteSilo MEMBER m_aetheriteSilo)
    Q_PROPERTY(Barracks* barracks MEMBER m_barracks)
    Q_PROPERTY(DockingStation* dockingStation MEMBER m_dockingStation)

    Q_PROPERTY(GameClock* gameClock MEMBER m_gameClock)

    Q_PROPERTY(MercenariesContainer* mercenaries MEMBER m_mercenaries)

    Q_PROPERTY(Equipment* preparedAvailableEquipment MEMBER m_preparedAvailableEquipment)

    Q_PROPERTY(MissionInitializer* missionInitializer MEMBER m_missionInitializer)

    Q_PROPERTY(Database* database MEMBER m_database)

    Q_PROPERTY(Mission* preparedMission MEMBER m_preparedMission)
    Q_PROPERTY(UnifiedReport* preparedReport MEMBER m_preparedReport)

    friend class H4X;

public:
    explicit Base(Game *gameObject) noexcept;
    void setupNewBase() noexcept;
    ~Base() noexcept;

    //save
    void loadSaveData(const SaveData &data) noexcept;//only use before proper game start
    SaveData getSaveData() noexcept;

    //buildings
    CentralUnit *centralUnit() noexcept;
    Hospital *hospital() noexcept;
    TrainingGround *trainingGround() noexcept;
    Gym *gym() noexcept;
    Laboratory *laboratory() noexcept;
    PlayingField *playingField() noexcept;
    Bar *bar() noexcept;
    Shrine *shrine() noexcept;
    Seclusion *seclusion() noexcept;
    Powerplant *powerplant() noexcept;
    Factory *factory() noexcept;
    CoolRoom *coolRoom() noexcept;
    StorageRoom *storageRoom() noexcept;
    AetheriteSilo *aetheriteSilo() noexcept;
    Barracks *barracks() noexcept;
    DockingStation *dockingStation() noexcept;

    Q_INVOKABLE void startNewDay() noexcept;

    Q_INVOKABLE void startNewWeek() noexcept;

    unsigned buildingLevel(BuildingEnums::Building buildingName) const noexcept
    {
        return m_buildingLevels.value(buildingName,0);
    }
    BuildingUpgradeRequirements buildingRequirements(BuildingEnums::Building buildingName, unsigned level) const noexcept;
    QString buildingDescription(BuildingEnums::Building buildingName) const noexcept
    {
        return m_buildingDescriptions.value(buildingName);
    }

    //resources
    Q_INVOKABLE inline int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    Q_INVOKABLE inline int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    Q_INVOKABLE inline int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    Q_INVOKABLE inline int currentAetheriteAmount() const noexcept
    {
        return m_aetherite;
    }

    Q_INVOKABLE int currentTotalSalary() const noexcept;

    void setCurrentEnergyAmount(unsigned amount) noexcept;
    void setCurrentFoodSuppliesAmount(unsigned amount) noexcept;
    void setCurrentBuildingMaterialsAmount(unsigned amount) noexcept;
    void setCurrentAetheriteAmount(unsigned amount) noexcept;

    inline bool canDecreaseEnergyAmount(unsigned amount) const noexcept
    {
        return m_energy>=amount;
    }
    inline bool canDecreaseFoodSuppliesAmount(unsigned amount) const noexcept
    {
        return m_foodSupplies>=amount;
    }
    inline bool canDecreaseBuildingMaterialsAmount(unsigned amount) const noexcept
    {
        return m_buildingMaterials>=amount;
    }
    inline bool canDecreaseAetheriteAmount(unsigned amount) const noexcept
    {
        return m_aetherite>=amount;
    }

    void decreaseEnergyAmount(unsigned amount) noexcept;
    void decreaseFoodSuppliesAmount(unsigned amount) noexcept;
    void decreaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void decreaseAetheriteAmount(unsigned amount) noexcept;

    void increaseEnergyAmount(unsigned amount) noexcept;
    void increaseFoodSuppliesAmount(unsigned amount) noexcept;
    void increaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void increaseAetheriteAmount(unsigned amount) noexcept;

    Q_INVOKABLE int currentEnergyIncome() const noexcept;
    Q_INVOKABLE int currentFoodSuppliesIncome() const noexcept;
    Q_INVOKABLE int currentBuildingMaterialsIncome() const noexcept;
    Q_INVOKABLE int currentAetheriteIncome() const noexcept;

    Q_INVOKABLE inline int currentEnergyLimit() noexcept;
    Q_INVOKABLE inline int currentFoodSuppliesLimit() noexcept;
    Q_INVOKABLE inline int currentBuildingMaterialsLimit() noexcept;
    Q_INVOKABLE inline int currentAetheriteLimit() noexcept;

    void setBuildingLevel(BuildingEnums::Building buildingName, unsigned level) noexcept;
    void setBuildingDescription(BuildingEnums::Building buildingName, const QString &desc) noexcept;
    void setBuildingDescriptions(const QVector <QPair <BuildingEnums::Building, QString> > &desc) noexcept;

    void setBuildingRequirements(const QMap <QPair <BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> &reqs) noexcept;

    Building *getBuilding(BuildingEnums::Building buildingName) noexcept;

    //mercenaries
    inline MercenariesContainer *mercenaries() noexcept
    {
        return m_mercenaries;
    }
    inline QMap <QString, unsigned> &mercenaryDockingStationBans() noexcept
    {
        return m_mercenaryDockingStationBans;
    }
    void recalculateAmountOfMercenarySlots() const noexcept;

    //equipment
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

    //game clock
    inline GameClock *gameClock() noexcept
    {
        return m_gameClock;
    }

    //missions
    void startMission(Mission *mission) noexcept;
    inline const QVector <Mission *> &missions() const noexcept
    {
        return m_missions;
    }
    inline Database *database() noexcept
    {
        return m_database;
    }
    void removeMission(Mission *mission) noexcept;

    Q_INVOKABLE inline unsigned amountOfMissions() const noexcept
    {
        return m_missions.size();
    }
    Q_INVOKABLE void prepareMission(unsigned index) noexcept;

    //reports
    Q_INVOKABLE inline unsigned amountOfReports() const noexcept
    {
        return m_reports.size();
    }
    Q_INVOKABLE inline unsigned amountOfNewReports() const noexcept
    {
        return m_newReports.size();
    }
    Q_INVOKABLE void prepareReport(unsigned index) noexcept;
    Q_INVOKABLE void prepareNewReport(unsigned index) noexcept;
    void addReport(UnifiedReport *report) noexcept;
    void registerLatestReportInMission(Mission *mission) noexcept;
    inline QVector <UnifiedReport *> &reports() noexcept
    {
        return m_reports;
    }
    Q_INVOKABLE void markAllAsRead() noexcept;
    Q_INVOKABLE void removeReport(unsigned index) noexcept;
    Q_INVOKABLE void clearReports() noexcept;

    Q_INVOKABLE int remainingMissionDaysForMercenary(const QString &mercenaryName);

    //game
    inline Game *gameObject() noexcept
    {
        return m_gameObject;
    }

private:
    //maps for buildings
    QMap <BuildingEnums::Building, unsigned> m_buildingLevels;
    QMap <QPair <BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> m_buildingRequirements;
    QMap <BuildingEnums::Building, QString> m_buildingDescriptions;
    QMap <BuildingEnums::Building, Building *> m_buildings;

    //direct pointers to specific buildings for QML
    CentralUnit *m_centralUnit;
    Hospital *m_hospital;
    TrainingGround *m_trainingGround;
    Gym *m_gym;
    Laboratory *m_laboratory;
    PlayingField *m_playingField;
    Bar *m_bar;
    Shrine *m_shrine;
    Seclusion *m_seclusion;
    Powerplant *m_powerplant;
    Factory *m_factory;
    CoolRoom *m_coolRoom;
    StorageRoom *m_storageRoom;
    AetheriteSilo *m_aetheriteSilo;
    Barracks *m_barracks;
    DockingStation *m_dockingStation;

    //resources
    unsigned m_energy;
    unsigned m_foodSupplies;
    unsigned m_buildingMaterials;
    unsigned m_aetherite;

    //mercenaries
    MercenariesContainer *m_mercenaries;
    QMap <QString, unsigned> m_mercenaryDockingStationBans;//in days; when banned, mercenary won't appear in docking station menu

    //equipment
    QVector <Equipment *> m_availableEquipment;
    Equipment *m_preparedAvailableEquipment;

    //game clock/timer
    void activateBuildingsAtDayEnd() noexcept;
    void handleMercenariesAtDayEnd() noexcept;
    void handleMercenariesAtWeekEnd() noexcept;

    GameClock *m_gameClock;

    //missions
    MissionInitializer *m_missionInitializer;
    Database *m_database;
    QVector <Mission *> m_missions;
    Mission *m_preparedMission;
    QVector <UnifiedReport *> m_reports;
    const unsigned m_maxReportsAmount=50;
    QVector <UnifiedReport *> m_newReports;
    UnifiedReport *m_preparedReport;

    //game
    Game *m_gameObject;
    bool m_freezeGameProgress;
};
