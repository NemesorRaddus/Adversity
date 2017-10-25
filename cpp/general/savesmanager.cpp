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

SaveInfo SavesManager::createNewSave(const QString &name) noexcept
{
    if (canCreateNewSave())
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

        return save;
    }
}

SaveInfo SavesManager::getSave(unsigned index) noexcept
{
    if (index<m_saves.size())
        return m_saves[index];
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

    str>>uu;
    info.day=uu;

    QByteArray ba;
    str>>ba;
    info.data=SaveParser::readData(ba);

    return info;
}
