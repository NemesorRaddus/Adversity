#include "database.h"

QDataStream &operator<<(QDataStream &stream, const DatabaseEntry &databaseEntry) noexcept
{
    stream<<databaseEntry.description;
    stream<<static_cast<quint8>(databaseEntry.type);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, DatabaseEntry &databaseEntry) noexcept
{
    quint8 n;

    stream>>databaseEntry.description;
    stream>>n;
    databaseEntry.type=static_cast<DatabaseEnums::EntryType>(n);

    return stream;
}

void Database::loadEntries(const QMap<Name, DatabaseEntry> &entries) noexcept
{
    m_entriesData=entries;
    for (auto e : entries.keys())
        m_unlocksInfo.insert(e, false);
}

void Database::unlockEntry(const Database::Name &entryName) noexcept
{
    if (m_unlocksInfo.contains(entryName))
        m_unlocksInfo.insert(entryName, true);
}

DatabaseEntry Database::readEntry(const Database::Name &entryName) const noexcept
{
    if (isEntryUnlocked(entryName))
        return m_entriesData.value(entryName);
    return {};
}

QVector<Database::Name> Database::unlockedEntries() const noexcept
{
    QVector <Name> r;
    for (auto e : m_unlocksInfo.keys())
        if (m_unlocksInfo.value(e))
            r+=e;
    return r;
}

QDataStream &Database::read(QDataStream &stream) noexcept
{
    stream>>m_entriesData;
    stream>>m_unlocksInfo;

    return stream;
}

QDataStream &Database::write(QDataStream &stream) const noexcept
{
    stream<<m_entriesData;
    stream<<m_unlocksInfo;

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const Database *database) noexcept
{
    database->write(stream);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Database *database) noexcept
{
    database->read(stream);

    return stream;
}
