#include "database.h"

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
    for (auto e : entries)
        m_unlocksInfo.insert(e.first, false);
}

void Database::unlockEntry(const Database::Name &entryName) noexcept
{
    if (m_unlocksInfo.contains(entryName))
        m_unlocksInfo.insert(entryName, true);
}

DatabaseEntryDetails Database::readEntry(const Database::Name &entryName) const noexcept
{
    if (isEntryUnlocked(entryName))
        for (auto e : m_entriesData)
            if (e.first == entryName)
                return e.second;
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
    stream>>m_unlocksInfo;

    return stream;
}

QDataStream &Database::write(QDataStream &stream) const noexcept
{
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
