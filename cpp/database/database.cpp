#include "database.h"

#include <QDebug>

#include "general/game.h"
#include "general/globalutilities.h"
#include "logging/loggershandler.h"
#include "reports/unifiedreport.h"

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
    bool firstInh=1;
    switch (entry.second.type)
    {
    case DatabaseEnums::ET_Animals:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
            {
                if (firstInh)
                    firstInh=0;
                else
                    r+=", ";
                r+=entry.second.inhabitancies[i];
            }
        break;
    case DatabaseEnums::ET_Plants:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
            {
                if (firstInh)
                    firstInh=0;
                else
                    r+=", ";
                r+=entry.second.inhabitancies[i];
            }
        break;
    case DatabaseEnums::ET_Fungi:
        r="Noticed inhabitant of:\n";
        for (int i=0;i<entry.second.inhabitancies.size();++i)
            if (m_unlocksInfo.unlockedInhabitancies[posInUnlocks][i])
            {
                if (firstInh)
                    firstInh=0;
                else
                    r+=", ";
                r+=entry.second.inhabitancies[i];
            }
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
            m_areThereNewEntries=1;
        }
    }
    else
    {
        if (m_unlocksInfo.unlockedInhabitancies[index].contains(0))
            m_areThereNewEntries=1;
        m_unlocksInfo.unlockedInhabitancies[index].fill(1);
    }
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
            m_areThereNewEntries=1;
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
                if (!m_unlocksInfo.unlockedInhabitancies[index][i])
                    m_areThereNewEntries=1;
                m_unlocksInfo.unlockedInhabitancies[index][i]=1;
                break;
            }
    }
}

bool Database::isEntryUnlocked(const Database::Name &entryName, const QString &landName) const noexcept
{
    if (!isEntryUnlocked(entryName))
        return 0;

    auto inhs = m_unlocksInfo.unlockedInhabitancies[m_unlocksInfo.unlockedEntries.indexOf(entryName)];
    int pos = -1;
    for (int i=0;i<m_entriesData.size();++i)
        if (m_entriesData[i].first == entryName)
        {
            pos = i;
            break;
        }
    for (int i=0;i<inhs.size();++i)
        if (m_entriesData[pos].second.inhabitancies[i] == landName)
            return inhs[i];

    return 0;// no such inhabitancy
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

QString Database::pathToEntryArt(const Database::Name &entryName) const noexcept
{
    DatabaseEnums::EntryType type = DatabaseEnums::ET_END;
    for (const auto &e : m_entriesData)
        if (e.first == entryName)
        {
            type = e.second.type;
            break;
        }
    if (type == DatabaseEnums::ET_END)
        return "";
    return "qrc:/graphics/Database/"+DatabaseEnums::fromEntryTypeEnumToQString(type)+"/"+GlobalUtilities::alterNormalTextToInternal(entryName)+".png";
}

void Database::setAreThereNewUnlockedEntries(bool areThere) noexcept
{
    m_areThereNewEntries=areThere;
}
