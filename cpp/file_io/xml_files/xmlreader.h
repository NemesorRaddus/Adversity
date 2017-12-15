#pragma once

#include "readers/buildingsreader.h"
#include "readers/mercenariesreader.h"
#include "readers/miscreader.h"
#include "readers/missionsreader.h"

class XmlFileReader : public BuildingsReader, public MercenariesReader, public MiscReader, public MissionsReader
{
public:
    XmlFileReader() noexcept = default;
    ~XmlFileReader() noexcept = default;
};

