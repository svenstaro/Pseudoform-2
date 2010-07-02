#include "Managers/ResourceManager.hpp"

void ResourceManager::addResourceLocation(const string &resLocation, bool recursive, const string &resGroup) const
{
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resLocation, "FileSystem", resGroup, recursive);
    LOG(FORMAT("Resource with location '%1%' was loaded into group '%2%' with recursive flag '%3%'",
            resLocation % resGroup % recursive));
}

void ResourceManager::unloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName)
{
    Ogre::ResourcePtr rPtr = resMgr->getByName(resourceName);
    if (rPtr.isNull()) return

    rPtr->unload();
    if (rPtr->isLoaded())
        LOG(FORMAT("The resource '%1%' wasn`t unloaded!", resourceName));
    else
        LOG(FORMAT("The resource '%1%' was unloaded!", resourceName));

    resMgr->remove(resourceName);
    rPtr = resMgr->getByName(resourceName);
    if (!rPtr.isNull())
        LOG(FORMAT("The resource '%1%' wasn`t removed!", resourceName));
    else
        LOG(FORMAT("The resource '%1%' was removed!", resourceName));
}

void ResourceManager::reloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup)
{
    Ogre::ResourcePtr rPtr = resMgr->load(resourceName, resourceGroup);
    if (rPtr.isNull()) LOG(FORMAT("The resource '%1%' no longer exists!", resourceName));

    rPtr->reload();
    if (rPtr->isLoaded())
        LOG(FORMAT("The resource '%1%' wasn`t unloaded!", resourceName));
    else
        LOG(FORMAT("The resource '%1%' was unloaded!", resourceName));
}