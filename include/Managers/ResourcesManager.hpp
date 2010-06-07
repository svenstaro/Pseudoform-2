#ifndef RESOURCESMANAGER_HPP
#define	RESOURCESMANAGER_HPP

#include "PseudoformAdditional.hpp"
#include "PseudoformCore.hpp"

class ResourcesManager
{
    public:
        // ============================================================================================
        void addResourceLocationRecursive(Ogre::String path, Ogre::String group = "General")
        {
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, "FileSystem", group);

            Ogre::Archive *arch = Ogre::ArchiveManager::getSingleton().load(path, "FileSystem");
            Ogre::StringVectorPtr files = arch->find("*", true, true);
            for (Ogre::StringVector::iterator iter = files->begin(); iter != files->end(); ++iter)
            {
                Ogre::String resource = path + "/" + *iter;
                LOG("Adding resource directory: " + resource);
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resource, "FileSystem", group);
            }

            files = arch->find("*.zip", true, false);
            for (Ogre::StringVector::iterator iter = files->begin(); iter != files->end(); ++iter)
            {
                Ogre::String resource = path + "/" + *iter;
                LOG("Adding .zip archive: " + resource);
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resource, "Zip", group);
            }
        }

        // ============================================================================================
        void UnloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName)
        {
            Ogre::ResourcePtr rPtr = resMgr->getByName(resourceName);
            if (rPtr.isNull())
            {
                LOG(FORMAT("Resource `%1%` no longer exists", resourceName));
                return;
            }

            rPtr->unload();
            if (rPtr->isLoaded()) {
                LOG(FORMAT("Resource `%1%` was not unloaded", resourceName));
            } else {
                LOG(FORMAT("Resource `%1%` was unloaded", resourceName));
            }

            resMgr->remove(resourceName);
        }
        // ============================================================================================
        void ReloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup)
        {
            Ogre::ResourcePtr rPtr = resMgr->load(resourceName, resourceGroup);
            if (rPtr.isNull())
            {
                    LOG(FORMAT("Resource `%1%` no longer exists", resourceName));
                    return;
            }

            rPtr->reload();
            if (rPtr->isLoaded()) {
                LOG(FORMAT("Resource `%1%` was reloaded", resourceName));
            } else {
                LOG(FORMAT("Resource `%1%` was not reloaded", resourceName));
            }
        }
        // ============================================================================================
};

#endif	/* RESOURCESMANAGER_HPP */

