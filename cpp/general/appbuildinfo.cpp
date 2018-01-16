#include "appbuildinfo.h"

void AppBuildInfo::setVersionNumber(const QString &versionNumber) noexcept
{
    m_versionNumber = versionNumber;
}

void AppBuildInfo::setBuildTime(const QString &buildTime) noexcept
{
    m_buildTime = buildTime;
}

void AppBuildInfo::setBuildType(const QString &buildType) noexcept
{
    m_buildType = buildType;
}

void AppBuildInfo::setToolkitName(const QString &toolkitName) noexcept
{
    m_toolkitName = toolkitName;
}

void AppBuildInfo::setAdditionBuildInfo(const QString &additionBuildInfo) noexcept
{
    m_additionBuildInfo = additionBuildInfo;
}
