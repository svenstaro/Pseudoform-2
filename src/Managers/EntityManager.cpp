#include "Managers/EntityManager.hpp"

bool EntityManager::DeleteEntity(const string& entityName)
{
    if (mEntityList.count(entityName) == 0)
    {
        LOG_META(FORMAT("Can`t delete entity '%1%', because it doesn`t exsist!", entityName));
        return false;
    }
    mEntityList.erase(entityName);
    return true;
}
