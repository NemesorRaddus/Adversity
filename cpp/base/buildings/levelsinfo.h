#pragma once

#include <QVector>

struct BuildingLevelInfo
{
public:
    virtual ~BuildingLevelInfo() noexcept = default;

    unsigned basicCostInEnergy;

protected:
    BuildingLevelInfo()
        : basicCostInEnergy(0) {}
};

class AnyBuildingLevelsInfo
{
public:
    template <typename LevelInfo>
    AnyBuildingLevelsInfo(const QVector <LevelInfo *> &levelsInfo, std::enable_if_t<std::is_base_of < BuildingLevelInfo, LevelInfo>::value>* = 0) noexcept
    {
        m_levelsInfo.reserve(levelsInfo.size());
        for (auto &e : levelsInfo)
            m_levelsInfo += static_cast < BuildingLevelInfo *>(e);
    }

    template <typename LevelInfo>
    AnyBuildingLevelsInfo(const QVector <LevelInfo *> &, std::enable_if_t<!std::is_base_of < BuildingLevelInfo, LevelInfo>::value>* = 0) noexcept
    {
        reportFailure();
    }

    ~AnyBuildingLevelsInfo() noexcept;

    template <typename LevelInfo>
    LevelInfo *getLevel(unsigned level) const noexcept
    {
        return static_cast < LevelInfo *>(m_levelsInfo[level]);
    }

    unsigned maxLevel() const noexcept;

private:
    void reportFailure() noexcept;

    QVector <BuildingLevelInfo *> m_levelsInfo;
};
