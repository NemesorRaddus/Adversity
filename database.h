#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QDataStream>
#include <QMap>

struct DatabaseEnums
{
    enum EntryType
    {
        ET_Land,
        ET_Animal,
        ET_Plant,
        ET_END
    };
};

struct DatabaseEntry
{
    QString description;
    DatabaseEnums::EntryType type;
};

QDataStream &operator<<(QDataStream &stream, const DatabaseEntry &databaseEntry) noexcept;
QDataStream &operator>>(QDataStream &stream, DatabaseEntry &databaseEntry) noexcept;

class Database
{
public:
    typedef QString Name;

    void loadEntries(const QMap <Name, DatabaseEntry> &entries) noexcept;
    void unlockEntry(const Name &entryName) noexcept;
    inline bool isEntryUnlocked(const Name &entryName) const noexcept
    {
        return m_unlocksInfo.value(entryName);
    }
    DatabaseEntry readEntry(const Name &entryName) const noexcept;
    QVector <Name> unlockedEntries() const noexcept;
    inline QMap <Name, DatabaseEntry> allEntries() const noexcept
    {
        return m_entriesData;
    }

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    QMap <Name, DatabaseEntry> m_entriesData;
    QMap <Name, bool> m_unlocksInfo;
};

QDataStream &operator<<(QDataStream &stream, const Database *database) noexcept;
QDataStream &operator>>(QDataStream &stream, Database *database) noexcept;

#endif // DATABASE_H
