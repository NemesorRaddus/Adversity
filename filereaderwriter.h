#ifndef FILEREADERWRITER_H
#define FILEREADERWRITER_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

#include "base.h"
#include "equipment.h"
#include "event.h"
#include "hero.h"

class FileReader
{
public:
    bool openXmlFile(const QString &path) noexcept;
    bool isXmlFileOpened() const noexcept;

    TechTree *getTechTree() noexcept;
    TechTree *getTechTree(const QString &path) noexcept;

private:
    QXmlStreamReader m_xmlReader;
};

class FileWriter
{
public:
    bool openXmlFile(const QString &path) noexcept;
    bool isXmlFileOpened() const noexcept;

private:
    QXmlStreamWriter m_xmlWriter;
};

#endif // FILEREADERWRITER_H
