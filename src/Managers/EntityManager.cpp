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

int EntityManager::DeleteAllEntities()
{
    int i = 0;
    LOG("=====Deleting all entitys!======");
    BOOST_FOREACH(TEntityList::value_type entity, mEntityList)
    {
        LOG("\tDeleting " + entity.first);
        mEntityList.erase(entity.first);
        i++;
    }
    LOG(FORMAT("Deleted %1% entitys", i));

    return i;
}
