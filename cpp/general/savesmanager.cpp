#include "savesmanager.h"

#include <QSettings>

#include "base/base.h"
#include "file_io/saves/saveparser.h"
#include "general/game.h"

SavesManager::SavesManager() noexcept
{
    loadSavesList();
}

SavesManager::~SavesManager() noexcept
{
    writeAllSaves();
}

bool SavesManager::canCreateNewSave() const noexcept
{
    return m_saves.size() < m_maxAmountOfSaves;
}

bool SavesManager::isNameUnique(const QString &name) const noexcept
{
    for (const auto &e : m_saves)
        if (e.metadata.name == name)
            return 0;
    return 1;
}

void SavesManager::createNewSave(const QString &name, const QString &pathToIcon) noexcept
{
    if (canCreateNewSave() && isNameUnique(name))
    {
        Save save;
        if (m_saves.empty())
            save.metadata.id = 0;
        else
            save.metadata.id = m_saves.last().metadata.id+1;

        save.metadata.name = name;

        Base *base = new Base(Game::gameInstance());
        base->setupNewBase();
        save.data = base->getSaveData();
        delete base;

        save.metadata.pathToIcon = pathToIcon;

        m_saves += save;

        writeSave(m_saves.size()-1);

        loadSaveIntoGame(m_saves.size()-1);
    }
}

void SavesManager::loadSave(const QString &name) noexcept
{
    int pos = findSave(name);

    if (pos == -1)
        return;

    loadSaveIntoGame(pos);
}

void SavesManager::updateSave(unsigned index, const SaveData &data) noexcept
{
    if (index < m_saves.size())
    {
        m_saves[index].data = data;
        m_saves[index].metadata.lastPlayed = QDateTime::currentDateTime();

        writeSave(index);
    }
}

void SavesManager::setSaveIcon(unsigned index, const QString &pathToIcon) noexcept
{
    if (index < m_saves.size())
        m_saves[index].metadata.pathToIcon = pathToIcon;
}

void SavesManager::duplicateSave(unsigned index, const QString &duplicateName) noexcept
{
    if (index < m_saves.size() && canCreateNewSave() && isNameUnique(duplicateName))
        m_saves+=m_saves[index];
}

void SavesManager::renameSave(unsigned index, const QString &newName) noexcept
{
    if (index < m_saves.size())
    {
        auto t = m_saves[index].metadata.name;
        m_saves[index].metadata.name.clear();
        if (isNameUnique(newName))
            m_saves[index].metadata.name = newName;
        else
            m_saves[index].metadata.name = t;
    }
}

void SavesManager::deleteSave(unsigned index) noexcept
{
    if (index < m_saves.size())
    {
        QSettings().remove(QString{"save_"}+QString::number(m_saves[index].metadata.id));
        m_saves.remove(index);
    }
}

unsigned SavesManager::amountOfSaves() const noexcept
{
    return m_saves.size();
}

QString SavesManager::nameOfSave(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index].metadata.name;
}

unsigned SavesManager::dayOfSave(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index].data.overall.lastKnownDay;
}

QString SavesManager::pathToIconOfSave(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index].metadata.pathToIcon;
}

QString SavesManager::lastPlayedTimeOfSave(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index].metadata.lastPlayed.toString("yyyy-MM-dd");
}

void SavesManager::loadSavesList() noexcept
{
    m_saves.clear();

    auto ak = QSettings().allKeys();
    for (const auto &e : ak)
        if (e.contains("save_"))
            m_saves+=readSave(QSettings().value(e).toByteArray());
}

Save SavesManager::readSave(const QByteArray &data) noexcept
{
    QByteArray t = qUncompress(data);

    Save save;
    QDataStream str(&t, QIODevice::ReadOnly);
    quint16 uu;

    str>>uu;
    save.metadata.id=uu;

    str>>save.metadata.name;

    str>>save.metadata.lastPlayed;

    str>>save.metadata.pathToIcon;

    QByteArray ba;
    str>>ba;
    save.data=SaveParser::readData(ba);

    return save;
}

void SavesManager::writeAllSaves() noexcept
{
    for (const auto &e : m_saves)
    {
        QByteArray ba;
        writeSave(ba, e);
        QSettings().setValue("save_"+QString::number(e.metadata.id), ba);
    }
}

void SavesManager::writeSave(QByteArray &array, const Save &save) noexcept
{
    QDataStream str(&array, QIODevice::WriteOnly);

    str<<static_cast<quint16>(save.metadata.id);

    str<<save.metadata.name;

    str<<save.metadata.lastPlayed;

    str<<save.metadata.pathToIcon;

    QByteArray ba;
    SaveParser::writeData(ba, save.data);
    str<<ba;

    array=qCompress(array);
}

void SavesManager::writeSave(unsigned index) noexcept
{
    if (index < m_saves.size())
    {
        QByteArray ba;
        writeSave(ba, m_saves[index]);
        QSettings().setValue("save_"+QString::number(m_saves[index].metadata.id), ba);
    }
}

int SavesManager::findSave(const QString &name) const noexcept
{
    for (int i=0;i<m_saves.size();++i)
        if (m_saves[i].metadata.name == name)
            return i;
    return -1;
}

void SavesManager::loadSaveIntoGame(unsigned index) noexcept
{
    if (index >= m_saves.size())
        return;

    if (m_currentSaveInUseIndex != -1)
    {
        updateSave(m_currentSaveInUseIndex, Game::gameInstance()->getSave());
        Game::gameInstance()->closeSave();
    }
    Game::gameInstance()->loadSave(m_saves[index].data);
    m_currentSaveInUseIndex=index;
}
