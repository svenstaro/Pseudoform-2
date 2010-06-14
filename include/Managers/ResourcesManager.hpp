#ifndef RESOURCESMANAGER_HPP
#define	RESOURCESMANAGER_HPP

#include "Managers/LogManager.hpp"
#include "Core/Utils.hpp"

#include <boost/serialization/singleton.hpp>
using namespace boost::serialization;

class ResourceManager : public singleton<ResourceManager>
{
    public:
        void addResourceLocationRecursive(Ogre::String path, Ogre::String group = "General")
        {
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, "FileSystem", group);

            Ogre::Archive *arch = Ogre::ArchiveManager::getSingleton().load(path, "FileSystem");
            Ogre::StringVectorPtr files = arch->find("*", true, true);
            for (Ogre::StringVector::iterator iter = files->begin(); iter != files->end(); ++iter)
            {
                Ogre::String resource = path + "/" + *iter;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resource, "FileSystem", group);
            }

            files = arch->find("*.zip", true, false);
            for (Ogre::StringVector::iterator iter = files->begin(); iter != files->end(); ++iter)
            {
                Ogre::String resource = path + "/" + *iter;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resource, "Zip", group);
            }
        }

        void UnloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName)
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
        
        void ReloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup)
        {
            Ogre::ResourcePtr rPtr = resMgr->load(resourceName, resourceGroup);
            if (rPtr.isNull()) LOG(FORMAT("The resource '%1%' no longer exists!", resourceName));

            rPtr->reload();
            if (rPtr->isLoaded())
                LOG(FORMAT("The resource '%1%' wasn`t unloaded!", resourceName));
            else
                LOG(FORMAT("The resource '%1%' was unloaded!", resourceName));
        }
};

#endif	/* RESOURCESMANAGER_HPP */

