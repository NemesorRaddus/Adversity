#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QDataStream>
#include <QMap>

#include <QDebug>

struct DatabaseEnums
{
    enum EntryType
    {
        ET_Land,
        ET_Animal,
        ET_Plant,
        ET_END
    };

    static EntryType fromQStringToEntryTypeEnum(const QString &entryType) noexcept;
    static QString fromEntryTypeEnumToQString(EntryType entryType) noexcept;
};

struct DatabaseEntryDetails
{
    QString description;
    DatabaseEnums::EntryType type;
};

typedef QPair <QString, DatabaseEntryDetails> DatabaseEntry;

typedef QVector <QString> DatabaseUnlocksInfo;

class Database
{
public:
    typedef QString Name;

    void loadEntries(const QVector <DatabaseEntry> &entries) noexcept;

    void unlockEntry(const Name &entryName) noexcept;
    inline bool isEntryUnlocked(const Name &entryName) const noexcept
    {
        return m_unlocksInfo.contains(entryName);
    }
    DatabaseEntryDetails readEntry(const Name &entryName) const noexcept;
    inline QVector <Name> unlockedEntries() const noexcept
    {
        return m_unlocksInfo;
    }
    inline QVector <DatabaseEntry> allEntries() const noexcept
    {
        return m_entriesData;
    }

    void setUnlocksInfo(const DatabaseUnlocksInfo &info) noexcept;

private:
    QVector <DatabaseEntry> m_entriesData;
    DatabaseUnlocksInfo m_unlocksInfo;
};

#endif // DATABASE_H
