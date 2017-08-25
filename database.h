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

    static EntryType fromQStringToEntryTypeEnum(const QString &entryType) noexcept;
    static QString fromEntryTypeEnumToQString(EntryType entryType) noexcept;
};

struct DatabaseEntryDetails
{
    QString description;
    DatabaseEnums::EntryType type;
};

typedef QPair <QString, DatabaseEntryDetails> DatabaseEntry;

class Database
{
public:
    typedef QString Name;

    void loadEntries(const QVector <DatabaseEntry> &entries) noexcept;

    void unlockEntry(const Name &entryName) noexcept;
    inline bool isEntryUnlocked(const Name &entryName) const noexcept
    {
        return m_unlocksInfo.value(entryName);
    }
    DatabaseEntryDetails readEntry(const Name &entryName) const noexcept;
    QVector <Name> unlockedEntries() const noexcept;
    inline QVector <DatabaseEntry> allEntries() const noexcept
    {
        return m_entriesData;
    }

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    QVector <DatabaseEntry> m_entriesData;
    QMap <Name, bool> m_unlocksInfo;
};

QDataStream &operator<<(QDataStream &stream, const Database *database) noexcept;
QDataStream &operator>>(QDataStream &stream, Database *database) noexcept;

#endif // DATABASE_H
