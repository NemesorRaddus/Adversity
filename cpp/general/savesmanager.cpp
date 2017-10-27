#include "savesmanager.h"

#include <QSettings>

#include "base/base.h"
#include "file_io/saves/saveparser.h"
#include "general/game.h"

SavesManager::SavesManager() noexcept
{
    loadSavesList();
}

bool SavesManager::canCreateNewSave() const noexcept
{
    return m_saves.size() < m_maxAmountOfSaves;
}

bool SavesManager::isNameUnique(const QString &name) const noexcept
{
    for (const auto &e : m_saves)
        if (e.name == name)
            return 0;
    return 1;
}

int SavesManager::findSave(const QString &name) const noexcept
{
    for (int i=0;i<m_saves.size();++i)
        if (m_saves[i].name == name)
            return i;
    return -1;
}

SaveInfo SavesManager::createNewSave(const QString &name, const QString &pathToIcon) noexcept
{
    if (canCreateNewSave() && isNameUnique(name))
    {
        SaveInfo save;
        if (m_saves.empty())
            save.id=0;
        else
            save.id=m_saves.last().id;

        save.name = name;

        Base *base = new Base(Game::gameInstance());
        base->setupNewBase();
        save.data = base->getSaveData();
        delete base;

        save.day = save.data.overall.lastKnownDay;

        save.pathToIcon = pathToIcon;

        return save;
    }
}

SaveInfo SavesManager::getSave(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index];
}

QString SavesManager::getSaveIconPath(unsigned index) const noexcept
{
    if (index < m_saves.size())
        return m_saves[index].pathToIcon;
}

void SavesManager::setSaveIcon(unsigned index, const QString &pathToIcon) noexcept
{
    if (index < m_saves.size())
        m_saves[index].pathToIcon = pathToIcon;
}

void SavesManager::updateSave(unsigned index, const SaveData &data) noexcept
{
    if (index < m_saves.size())
    {
        m_saves[index].data = data;
        m_saves[index].day = data.overall.lastKnownDay;
        m_saves[index].lastPlayed = QDateTime::currentDateTime();
    }
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
        auto t = m_saves[index].name;
        m_saves[index].name.clear();
        if (isNameUnique(newName))
            m_saves[index].name = newName;
        else
            m_saves[index].name = t;
    }
}

void SavesManager::deleteSave(unsigned index) noexcept
{
    if (index<m_saves.size())
    {
        QSettings().remove(QString{"save_"}+QString::number(m_saves[index].id));
        m_saves.remove(index);
    }
}

void SavesManager::loadSavesList() noexcept
{
    m_saves.clear();

    auto ak = QSettings().allKeys();
    for (const auto &e : ak)
        if (e.contains("save_"))
            m_saves+=readSaveInfo(QSettings().value(e).toByteArray());
}

SaveInfo SavesManager::readSaveInfo(const QByteArray &data) noexcept
{
    QByteArray t=qUncompress(data);

    SaveInfo info;
    QDataStream str(&t,QIODevice::ReadOnly);
    quint16 uu;

    str>>uu;
    info.id=uu;

    str>>info.name;

    QByteArray ba;
    str>>ba;
    info.data=SaveParser::readData(ba);

    info.day = info.data.overall.lastKnownDay;

    return info;
}
