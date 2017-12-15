#pragma once

#include "xmlfilereaderbase.h"

template <typename T1, typename T2>
class QMap;

class MiscReader : private virtual XmlFileReaderBase
{
public:
    MiscReader() noexcept = default;
    virtual ~MiscReader() noexcept = default;

    QMap <QString, QMap<QString,QString> > getTranslations(const QString &path) noexcept;
};
