#pragma once

#include <QObject>

class AppBuildInfo : public QObject
{
    Q_OBJECT

    friend class H4X;

public:
    Q_INVOKABLE inline QString versionNumber() const noexcept
    {
        return m_versionNumber;
    }
    Q_INVOKABLE inline QString buildTime() const noexcept
    {
        return m_buildTime;
    }
    Q_INVOKABLE inline QString buildType() const noexcept
    {
        return m_buildType;
    }
    Q_INVOKABLE inline QString toolkitName() const noexcept
    {
        return m_toolkitName;
    }
    Q_INVOKABLE inline QString additionalBuildInfo() const noexcept
    {
        return m_additionBuildInfo;
    }

    void setVersionNumber(const QString &versionNumber) noexcept;
    void setBuildTime(const QString &buildTime) noexcept;
    void setBuildType(const QString &buildType) noexcept;
    void setToolkitName(const QString &toolkitName) noexcept;
    void setAdditionBuildInfo(const QString &additionBuildInfo) noexcept;

private:
    QString m_versionNumber, m_buildTime, m_buildType, m_toolkitName, m_additionBuildInfo;
};
