#ifndef RESOURCESMANAGER_HPP
#define	RESOURCESMANAGER_HPP

class ResourcesManager
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
            resMgr->remove(resourceName);
        }
        
        void ReloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup)
        {
            Ogre::ResourcePtr rPtr = resMgr->load(resourceName, resourceGroup);
            if (rPtr.isNull()) return;

            rPtr->reload();
        }
};

#endif	/* RESOURCESMANAGER_HPP */

