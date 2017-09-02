#include "database.h"

#include <QDebug>

DatabaseEnums::EntryType DatabaseEnums::fromQStringToEntryTypeEnum(const QString &entryType) noexcept
{
    if (entryType == "Lands")
        return ET_Lands;
    if (entryType == "Animals")
        return ET_Animals;
    if (entryType == "Plants")
        return ET_Plants;
    if (entryType == "Fungi")
        return ET_Fungi;
    qWarning()<<"QString->enum conversion failed for "<<entryType;
}

QString DatabaseEnums::fromEntryTypeEnumToQString(DatabaseEnums::EntryType entryType) noexcept
{
    if (entryType == ET_Lands)
        return "Lands";
    if (entryType == ET_Animals)
        return "Animals";
    if (entryType == ET_Plants)
        return "Plants";
    if (entryType == ET_Fungi)
        return "Fungi";
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

QString Database::inhabitancyTextOfEntry(unsigned index) const noexcept
{
    if (index>=m_entriesFromCurrentCategory.size())
        return {};

    QString r;
    switch (m_entriesFromCurrentCategory[index].second.type)
    {
    case DatabaseEnums::ET_Animals:
        r="\n";// TODO inh texts
        for (auto e : m_entriesFromCurrentCategory[index].second.inhabitancies)
            r+=e+'\n';
        break;
    case DatabaseEnums::ET_Plants:
        r="\n";
        for (auto e : m_entriesFromCurrentCategory[index].second.inhabitancies)
            r+=e+'\n';
        break;
    case DatabaseEnums::ET_Fungi:
        r="\n";
        for (auto e : m_entriesFromCurrentCategory[index].second.inhabitancies)
            r+=e+'\n';
        break;
    case DatabaseEnums::ET_Lands:
        r="\n";
        for (auto e : m_entriesFromCurrentCategory[index].second.inhabitancies)
            r+=e+'\n';
        break;
    }

    return r;
}

void Database::loadEntries(const QVector<DatabaseEntry> &entries) noexcept
{
    m_entriesData=entries;
    m_unlocksInfo.clear();
}

void Database::unlockEntry(const Database::Name &entryName) noexcept
{
    if (!m_unlocksInfo.contains(entryName))
    {
        bool ok=0;
        for (const auto &e : m_entriesData)
            if (e.first == entryName)
            {
                ok=1;
                break;
            }
        if (ok)
            m_unlocksInfo+=entryName;
    }
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
