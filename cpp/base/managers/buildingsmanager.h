#pragma once

#include <QMap>
#include <QObject>

#include "basemanagerinterface.h"
#include "base/buildings/building.h"
#include "base/buildings/enums.h"

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
class BuildingsRequirementsHandler;
typedef QMap <QPair <BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> BuildingsRequirementsMap;

class BuildingsManager : public QObject, public BaseManagerInterface
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

    friend class H4X;
    friend class Base;

public:
    explicit BuildingsManager(Base * base) noexcept;
    ~BuildingsManager() noexcept;

    void initializeForNewBase() noexcept final;

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

    unsigned buildingLevel(BuildingEnums::Building buildingName) const noexcept;
    BuildingUpgradeRequirements buildingRequirements(BuildingEnums::Building buildingName, unsigned level) const noexcept;
    QString buildingDescription(BuildingEnums::Building buildingName) const noexcept;

    void setBuildingLevel(BuildingEnums::Building buildingName, unsigned level) noexcept;
    void setBuildingDescription(BuildingEnums::Building buildingName, const QString &desc) noexcept;
    void setBuildingDescriptions(const QMap <BuildingEnums::Building, QString> &descs) noexcept;

    void setBuildingRequirements(const BuildingsRequirementsMap &reqs) noexcept;

    Building *getBuilding(BuildingEnums::Building buildingName) noexcept;

private:
    //maps for buildings
    BuildingsRequirementsHandler *m_buildingRequirements;
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
};
