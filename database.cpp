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

void DatabaseUnlocksInfo::clear() noexcept
{
    unlockedEntries.clear();
    unlockedInhabitancies.clear();
}

QDataStream &operator<<(QDataStream &stream, const DatabaseUnlocksInfo &unlocks) noexcept
{
    stream<<unlocks.unlockedEntries;
    stream<<unlocks.unlockedInhabitancies;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, DatabaseUnlocksInfo &unlocks) noexcept
{
    stream>>unlocks.unlockedEntries;
    stream>>unlocks.unlockedInhabitancies;

    return stream;
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
        if (m_unlocksInfo.unlockedEntries.contains(e.first) && e.second.type == t)
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

    const auto &entry=m_entriesFromCurrentCategory[index];
    int posInUnlocks=m_unlocksInfo.unlockedEntries.indexOf(entry.first);

    QString r;
    switch (entry.second.type)
    {
    case DatabaseEnums::ET_Animals:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
                r+=entry.second.inhabitancies[i]+'\n';
        break;
    case DatabaseEnums::ET_Plants:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
                r+=entry.second.inhabitancies[i]+'\n';
        break;
    case DatabaseEnums::ET_Fungi:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
                r+=entry.second.inhabitancies[i]+'\n';
        break;
    case DatabaseEnums::ET_Lands:
        r="";
        break;
    default:
        qWarning()<<"Wrong enum value encountered in Database::inhabitancyTextOfEntry(unsigned).";
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
    int index=m_unlocksInfo.unlockedEntries.indexOf(entryName);
    if (index==-1)
    {
        int pos=-1;
        for (int i=0;i<m_entriesData.size();++i)
            if (m_entriesData[i].first == entryName)
            {
                pos=i;
                break;
            }
        if (pos!=-1)
        {
            m_unlocksInfo.unlockedEntries+=entryName;
            QVector <bool> vb;
            vb.fill(1,m_entriesData[pos].second.inhabitancies.size());
            m_unlocksInfo.unlockedInhabitancies+=vb;
        }
    }
    else
        m_unlocksInfo.unlockedInhabitancies[index].fill(1);
}

void Database::unlockEntry(const Database::Name &entryName, const QString &landName) noexcept
{
    int index=m_unlocksInfo.unlockedEntries.indexOf(entryName);
    if (index==-1)
    {
        int pos=-1;
        for (int i=0;i<m_entriesData.size();++i)
            if (m_entriesData[i].first == entryName)
            {
                pos=i;
                break;
            }
        if (pos!=-1)
        {
            m_unlocksInfo.unlockedEntries+=entryName;
            QVector <bool> vb;
            vb.fill(0,m_entriesData[pos].second.inhabitancies.size());
            for (int i=0;i<vb.size();++i)
                if (m_entriesData[pos].second.inhabitancies[i] == landName)
                {
                    vb[i]=1;
                    break;
                }
            m_unlocksInfo.unlockedInhabitancies+=vb;
        }
    }
    else
    {
        int pos=-1;
        for (int i=0;i<m_entriesData.size();++i)
            if (m_entriesData[i].first == entryName)
            {
                pos=i;
                break;
            }
        for (int i=0;i<m_entriesData[pos].second.inhabitancies.size();++i)
            if (m_entriesData[pos].second.inhabitancies[i] == landName)
            {
                m_unlocksInfo.unlockedInhabitancies[index][i]=1;
                break;
            }
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
