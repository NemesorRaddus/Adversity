#pragma once

#include <QObject>
#include <QString>
#include <QVector>

#include "file_io/saves/save.h"

class SavesManager : public QObject
{
    Q_OBJECT

public:
    SavesManager() noexcept;
    ~SavesManager() noexcept;

    Q_INVOKABLE bool canCreateNewSave() const noexcept;
    Q_INVOKABLE bool isNameUnique(const QString &name) const noexcept;
    Q_INVOKABLE void createNewSave(const QString &name, const QString &pathToIcon) noexcept;

    Q_INVOKABLE void loadSave(const QString &name) noexcept;

    void updateSave(unsigned index, const SaveData &data) noexcept;
    Q_INVOKABLE void setSaveIcon(unsigned index, const QString &pathToIcon) noexcept;
    Q_INVOKABLE void duplicateSave(unsigned index, const QString &duplicateName) noexcept;
    Q_INVOKABLE void renameSave(unsigned index, const QString &newName) noexcept;
    Q_INVOKABLE void deleteSave(unsigned index) noexcept;
    Q_INVOKABLE unsigned amountOfSaves() const noexcept;

    Q_INVOKABLE QString nameOfSave(unsigned index) const noexcept;
    Q_INVOKABLE unsigned dayOfSave(unsigned index) const noexcept;
    Q_INVOKABLE QString pathToIconOfSave(unsigned index) const noexcept;
    Q_INVOKABLE QString lastPlayedTimeOfSave(unsigned index) const noexcept;

    inline int currentSaveInUseIndex() const noexcept
    {
        return m_currentSaveInUseIndex;
    }
    inline bool isSaveLoaded() const noexcept
    {
        return currentSaveInUseIndex() != -1;
    }

private:
    void loadSavesList() noexcept;
    static Save readSave(const QByteArray &data) noexcept;

    void writeAllSaves() noexcept;
    static void writeSave(QByteArray &array, const Save &save) noexcept;
    void writeSave(unsigned index) noexcept;

    int findSave(const QString &name) const noexcept;

    void loadSaveIntoGame(unsigned index) noexcept;

    QVector <Save> m_saves;
    const unsigned m_maxAmountOfSaves = 20;
    int m_currentSaveInUseIndex = -1;
};
