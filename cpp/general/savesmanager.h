#pragma once

#include <QString>
#include <QVector>

#include "file_io/saves/savedata.h"

struct SaveInfo
{
    unsigned id;
    QString name;
    unsigned day;
    SaveData data;
};

class SavesManager
{
public:
    SavesManager() noexcept;

    bool canCreateNewSave() const noexcept;
    SaveInfo createNewSave(const QString &name) noexcept;
    SaveInfo getSave(unsigned index) noexcept;
    void deleteSave(unsigned index) noexcept;
    unsigned amountOfSaves() const noexcept;

private:
    void loadSavesList() noexcept;
    static SaveInfo readSaveInfo(const QByteArray &data) noexcept;

    QVector <SaveInfo> m_saves;
    const unsigned m_maxAmountOfSaves = 10;
};
