#include "Managers/EntityManager.hpp"

Object *EntityManager::MakeObject(const string& entityName)
{
    return this->MakeEntity<Object>(entityName);
}

Object *EntityManager::GetObject(const string& entityName)
{
    return this->GetEntity<Object>(entityName);
}

Light *EntityManager::MakeLight(const string& entityName)
{
    return this->MakeEntity<Light>(entityName);
}

Light *EntityManager::GetLight(const string& entityName)
{
    return this->GetEntity<Light>(entityName);
}

Camera *EntityManager::MakeCamera(const string& cameraName)
{
    return this->MakeEntity<Camera>(cameraName);
}

Camera *EntityManager::GetCamera(const string& cameraName)
{
    return this->GetEntity<Camera>(cameraName);
}


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
