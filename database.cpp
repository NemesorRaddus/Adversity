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

Database *Database::copyDBWithoutUnlocks() const noexcept
{
    Database *r=new Database;
    r->m_entriesData=m_entriesData;
    return r;
}

void Database::prepareCategory(const QString &cat) noexcept
{
    m_entriesFromCurrentCategory.clear();
    DatabaseEnums::EntryType t=DatabaseEnums::fromQStringToEntryTypeEnum(cat);
    for (auto e : m_entriesData)
        if (m_unlocksInfo.contains(e.first) && e.second.type == t)
            m_entriesFromCurrentCategory+=e;
}

QString Database::nameOfEntry(unsigned index) const noexcept
{
    if (index>=m_entriesFromCurrentCategory.size())
        return {};
    return m_entriesFromCurrentCategory[index].first;
}

QString Database::descriptionOfEntry(unsigned index) const noexcept
{
    if (index>=m_entriesFromCurrentCategory.size())
        return {};
    return m_entriesFromCurrentCategory[index].second.description;
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
