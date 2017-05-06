#ifndef ASSETSPOOL_H
#define ASSETSPOOL_H

#include <QVector>

#include "hero.h"
#include "filereaderwriter.h"

#include <QDebug>

class AssetsPool
{
public:
    AssetsPool() noexcept;
    ~AssetsPool() noexcept;

    void load(const QString &pathToAssets) noexcept;
    bool isReady() const noexcept;
    void clear() noexcept;

private:
    void loadHeroes(const QString &path) noexcept;
    void loadEquipment(const QString &path) noexcept;

    bool m_isReady;
    QVector <Hero *> m_heroes;
    QVector <Equipment *> m_equipment;
    XmlFileReader m_reader;
};

#endif // ASSETSPOOL_H
