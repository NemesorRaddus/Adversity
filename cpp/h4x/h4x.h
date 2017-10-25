#pragma once

#include <QObject>
#include <QVariant>

class QQmlApplicationEngine;

#ifdef ENABLE_CONSOLE_WINDOW
class MainWindowEventFilter : public QObject
{
    Q_OBJECT
public:
    MainWindowEventFilter(QObject *consoleWindow, bool *lock) noexcept
        : m_consoleWindow(consoleWindow), m_lock(lock) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) noexcept;

private:
    QObject *m_consoleWindow;
    bool *m_lock;
};

class ConsoleWindowEventFilter : public QObject
{
    Q_OBJECT
public:
    ConsoleWindowEventFilter(QObject *mainWindow, bool *lock) noexcept
        : m_mainWindow(mainWindow), m_lock(lock) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) noexcept;

private:
    QObject *m_mainWindow;
    bool *m_lock;
};
#endif

static QQmlApplicationEngine *_h4xQmlEngine;

class H4X : public QObject
{
    Q_OBJECT

public:
    H4X(QQmlApplicationEngine *engine);//first use!
    H4X();//use it later on
    
    //time hacks
    Q_INVOKABLE void doTimeTravel(int days, int hours, int minutes) noexcept;//only forward
    Q_INVOKABLE void speedUpTime(float multiplier) noexcept;
    Q_INVOKABLE void slowDownTime(float multiplier) noexcept;
    Q_INVOKABLE void freezeTime() noexcept;
    Q_INVOKABLE void unfreezeTime() noexcept;

    //resource hacks
    Q_INVOKABLE void setAetherite(unsigned amount) noexcept;
    Q_INVOKABLE void setBuildingMaterials(unsigned amount) noexcept;
    Q_INVOKABLE void setEnergy(unsigned amount) noexcept;
    Q_INVOKABLE void setFoodSupplies(unsigned amount) noexcept;
    Q_INVOKABLE void refill() noexcept;

    //docking station hacks
    Q_INVOKABLE void getFreshMeat() noexcept;
    Q_INVOKABLE void getNewStuff() noexcept;
    
    //building hacks
    Q_INVOKABLE void upgradeBuilding(const QString &buildingName) noexcept;
    Q_INVOKABLE void setBuildingLevel(const QString &buildingName, unsigned level) noexcept;
    Q_INVOKABLE void completeUpgrade(const QString &buildingName) noexcept;
    Q_INVOKABLE void burnItDown() noexcept;
    
    //mercenary hacks
    Q_INVOKABLE void setMercenaryAttribute(const QString &mercenaryName, const QString &attribute, QVariant value) noexcept;
    Q_INVOKABLE void hire(const QString &mercenaryName) noexcept;
    Q_INVOKABLE void kill(const QString &mercenaryName) noexcept;
    Q_INVOKABLE void dismiss(const QString &mercenaryName, unsigned banTime) noexcept;
    Q_INVOKABLE void killThemAll() noexcept;
    Q_INVOKABLE void engulfThemInPain() noexcept;
    Q_INVOKABLE void chaosComesForYou() noexcept;
    Q_INVOKABLE void setMercenaryVariable(const QString &mercenaryName, const QString &varName, QVariant value) noexcept;

    //database hacks
    Q_INVOKABLE void unlockDBEntry(const QString &entryName) noexcept;

    //report hacks
    Q_INVOKABLE void receiveReport(const QString &msg, const QString &art = {}) noexcept;
    Q_INVOKABLE void clearReports() noexcept;

    //mission hacks
    Q_INVOKABLE void finishMission(const QString &mercenaryName) noexcept;
    
    //ui hacks
    Q_INVOKABLE void forceUIUpdate() noexcept;
    Q_INVOKABLE void fps() noexcept;

    //app hacks
    Q_INVOKABLE void destroyEverything() noexcept;
    Q_INVOKABLE void freezeGameProgress() noexcept;

    //hacks settings
    Q_INVOKABLE void enableAutoUpdate(bool enable) noexcept;
    Q_INVOKABLE inline bool isAutoUpdateEnabled() const noexcept
    {
        return m_autoUpdate;
    }
    
private:
    QQmlApplicationEngine *m_qmlEngine;
    bool m_autoUpdate;
};
