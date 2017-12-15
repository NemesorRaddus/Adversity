#pragma once

#include "xmlfilereaderbase.h"

template <typename T>
class QVector;
template <typename T>
class QList;

class Equipment;
class Mercenary;

class MercenariesReader : private virtual XmlFileReaderBase
{
public:
    MercenariesReader() noexcept = default;
    virtual ~MercenariesReader() noexcept = default;

    QList <QString> getMercenariesNamesList(const QString &pathToMercenariesDir) noexcept;
    Mercenary *getMercenary(const QString &path) noexcept;

    QVector <Equipment *> getEquipment(const QString &path) noexcept;
};
