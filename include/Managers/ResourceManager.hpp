#ifndef RESOURCESMANAGER_HPP
#define	RESOURCESMANAGER_HPP

#include "Managers/LogManager.hpp"
#include "Core/Utils.hpp"

#include <Ogre.h>

#include <boost/serialization/singleton.hpp>
using namespace boost::serialization;

class ResourceManager : public singleton<ResourceManager>
{
    public:
        void addResourceLocationRecursive(Ogre::String path, Ogre::String group = "General") const;
        void unloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName);
        void reloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup);
};

#endif	/* RESOURCESMANAGER_HPP */