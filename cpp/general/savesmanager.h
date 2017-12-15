#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QDateTime>

#include "file_io/saves/savedata.h"

struct SaveInfo
{
    unsigned id;
    QString name;
    unsigned day;
    QString pathToIcon;
    QDateTime lastPlayed;
    SaveData data;
};

class SavesManager : public QObject
{
    Q_OBJECT

public:
    SavesManager() noexcept;

    bool canCreateNewSave() const noexcept;
    bool isNameUnique(const QString &name) const noexcept;

    int findSave(const QString &name) const noexcept;

    SaveInfo createNewSave(const QString &name, const QString &pathToIcon) noexcept;
    SaveInfo getSave(unsigned index) const noexcept;
    QString getSaveIconPath(unsigned index) const noexcept;
    void setSaveIcon(unsigned index, const QString &pathToIcon) noexcept;
    void updateSave(unsigned index, const SaveData &data) noexcept;
    Q_INVOKABLE void duplicateSave(unsigned index, const QString &duplicateName) noexcept;
    Q_INVOKABLE void renameSave(unsigned index, const QString &newName) noexcept;
    Q_INVOKABLE void deleteSave(unsigned index) noexcept;
    Q_INVOKABLE unsigned amountOfSaves() const noexcept;

private:
    void loadSavesList() noexcept;
    static SaveInfo readSaveInfo(const QByteArray &data) noexcept;

    QVector <SaveInfo> m_saves;
    const unsigned m_maxAmountOfSaves = 20;
};
