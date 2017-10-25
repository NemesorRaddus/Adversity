#pragma once

#include <QString>
#include <QDataStream>
#include <QMap>
#include <QVector>

#include "enums.h"

struct DatabaseEntryDetails
{
    QString description;
    DatabaseEnums::EntryType type;
    QVector <QString> inhabitancies;
};

typedef QPair <QString, DatabaseEntryDetails> DatabaseEntry;

struct DatabaseUnlocksInfo
{
    void clear() noexcept;

    QVector <QString> unlockedEntries;
    QVector <QVector <bool> > unlockedInhabitancies;
};

QDataStream &operator<<(QDataStream &stream, const DatabaseUnlocksInfo &unlocks) noexcept;
QDataStream &operator>>(QDataStream &stream, DatabaseUnlocksInfo &unlocks) noexcept;

class Database : public QObject
{
    Q_OBJECT

public:
    typedef QString Name;

    Database *copyDBWithoutUnlocks() const noexcept;

    Q_INVOKABLE void prepareCategory(const QString &cat) noexcept;
    Q_INVOKABLE inline unsigned amountOfEntriesInCurrentCategory() const noexcept
    {
        return m_entriesFromCurrentCategory.size();
    }
    Q_INVOKABLE QString nameOfEntry(unsigned index) const noexcept;
    Q_INVOKABLE QString descriptionOfEntry(unsigned index) const noexcept;
    Q_INVOKABLE QString inhabitancyTextOfEntry(unsigned index) const noexcept;

    void loadEntries(const QVector <DatabaseEntry> &entries) noexcept;

    void unlockEntry(const Name &entryName) noexcept; // for H4x
    void unlockEntry(const Name &entryName, const QString &landName) noexcept;
    inline bool isEntryUnlocked(const Name &entryName) const noexcept
    {
        return m_unlocksInfo.unlockedEntries.contains(entryName);
    }
    bool isEntryUnlocked(const Name &entryName, const QString &landName) const noexcept;
    DatabaseEntryDetails readEntry(const Name &entryName) const noexcept;
    inline DatabaseUnlocksInfo unlockedEntries() const noexcept
    {
        return m_unlocksInfo;
    }
    inline QVector <DatabaseEntry> allEntries() const noexcept
    {
        return m_entriesData;
    }

    void setUnlocksInfo(const DatabaseUnlocksInfo &info) noexcept;

    QString pathToEntryArt(const Name &entryName) const noexcept;

    Q_INVOKABLE void setAreThereNewUnlockedEntries(bool areThere) noexcept;
    Q_INVOKABLE inline bool areThereNewEntries() const noexcept
    {
        return m_areThereNewEntries;
    }

private:
    QVector <DatabaseEntry> m_entriesData;
    DatabaseUnlocksInfo m_unlocksInfo;
    bool m_areThereNewEntries;

    QVector <DatabaseEntry> m_entriesFromCurrentCategory;
};
