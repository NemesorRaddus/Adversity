#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSettings>

#include "base.h"
#include "filereaderwriter.h"
#include "saveparser.h"
#include "timer.h"

#include <QDebug>

class QQmlEngine;
class QJSEngine;

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Base* base MEMBER m_base)
public:
    explicit Game(QObject *parent = 0) noexcept;

    Q_INVOKABLE void createNewBase(const QString &pathToAssetsDir/*with ending / */) noexcept;//WARNING NEVER USED
    Q_INVOKABLE void loadExistingBase(const QString &pathToAssetsDir) noexcept;
    Q_INVOKABLE void saveBase() noexcept;

public slots:
    void saveBase_slot() noexcept;

private:
    void connectAutosave() noexcept;
    void disconnectAutosave() noexcept;

    void loadAssets(const QString &pathToDir) noexcept;

    Base *m_base;
    QString m_currentPathToAssets;
};

static QObject *gameQObjectSingletontypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Game *game =new Game();
    return game;
}

#endif // GAME_H
