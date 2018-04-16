#pragma once

#include "xmlfilereaderbase.h"

template <typename T1, typename T2>
class QPair;
template <typename T>
class QVector;
template <typename T>
class QList;

struct DatabaseEntryDetails;
typedef QPair <QString, DatabaseEntryDetails> DatabaseEntry;
class EncountersContainer;
class Event;
class LandInfo;
class ValueRange;

class MissionsReader : private virtual XmlFileReaderBase
{
public:
    MissionsReader() noexcept = default;
    virtual ~MissionsReader() noexcept = default;

    QList <QString> getDatabaseFilesList(const QString &pathToDBDir) noexcept;
    QVector <DatabaseEntry> getDatabaseEntries(const QString &path) noexcept;

    QList <QString> getLandsNamesList(const QString &pathToLandsDir) noexcept;
    LandInfo getLandInfo(const QString &path) noexcept;

    EncountersContainer *getEncounters(const QString &path) noexcept;

private:
    Event *getEvent(bool alreadyRead) noexcept;
    static ValueRange parseValue(QString text) noexcept;
};
