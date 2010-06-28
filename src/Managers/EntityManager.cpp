#include "Managers/EntityManager.hpp"

Entity3D *EntityManager::Make3DEntity(const string& entityName)
{
    return MakeEntity<Entity3D>(entityName);
}

Entity2D *EntityManager::Make2DEntity(const string& entityName)
{
    return MakeEntity<Entity2D>(entityName);
}

Entity3D *EntityManager::Get3DEntity(const string &entityName)
{
    return GetEntity<Entity3D>(entityName);
}
Entity2D *EntityManager::Get2DEntity(const string &entityName)
{
    return GetEntity<Entity2D>(entityName);
}

bool EntityManager::DeleteEntity(const string& entityName)
{
    if (mEntityList.count(entityName) == 0)
    {
        LOG(FORMAT("Can`t delete entity '%1%', because it doesn`t exsist!", entityName));
        return false;
    }
    mEntityList.erase(entityName);
    return true;
}