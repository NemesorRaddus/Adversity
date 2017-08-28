#include "database.h"

#include <QDebug>

DatabaseEnums::EntryType DatabaseEnums::fromQStringToEntryTypeEnum(const QString &entryType) noexcept
{
    if (entryType == "Land")
        return ET_Land;
    if (entryType == "Animal")
        return ET_Animal;
    if (entryType == "Plant")
        return ET_Plant;
    qWarning()<<"QString->enum conversion failed for "<<entryType;
}

QString DatabaseEnums::fromEntryTypeEnumToQString(DatabaseEnums::EntryType entryType) noexcept
{
    if (entryType == ET_Land)
        return "Land";
    if (entryType == ET_Animal)
        return "Animal";
    if (entryType == ET_Plant)
        return "Plant";
    qWarning()<<"enum->QString conversion failed for "<<entryType;
}

void Database::loadEntries(const QVector<DatabaseEntry> &entries) noexcept
{
    m_entriesData=entries;
    m_unlocksInfo.clear();
}

void Database::unlockEntry(const Database::Name &entryName) noexcept
{
    if (m_unlocksInfo.contains(entryName))
        m_unlocksInfo+=entryName;
}

DatabaseEntryDetails Database::readEntry(const Database::Name &entryName) const noexcept
{
    if (isEntryUnlocked(entryName))
        for (auto e : m_entriesData)
            if (e.first == entryName)
                return e.second;
    return {};
}

void Database::setUnlocksInfo(const DatabaseUnlocksInfo &info) noexcept
{
    m_unlocksInfo=info;
}
