#pragma once

#include <QString>
#include <QDateTime>

#include "file_io/saves/savedata.h"

struct SaveMetadata
{
    unsigned id;
    QString name;
    QString pathToIcon;
    QDateTime lastPlayed;
};

struct Save
{
    SaveMetadata metadata;
    SaveData data;
};
