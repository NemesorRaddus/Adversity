#ifndef ASSETSPOOL_H
#define ASSETSPOOL_H

#include <QVector>

#include "hero.h"
#include "filereaderwriter.h"

#include <QDebug>

class AssetsPool
{
public:
    AssetsPool();

    void load(const QString &pathToAssets) noexcept;
    bool isReady() const noexcept;
    void clear() noexcept;

private:
    QVector <Hero *> m_heroes;
    QVector <Equipment *> m_equipment;

};

#endif // ASSETSPOOL_H
