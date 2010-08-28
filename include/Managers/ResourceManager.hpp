#ifndef RESOURCESMANAGER_HPP
#define	RESOURCESMANAGER_HPP

#include "Managers/LogManager.hpp"
#include "Core/Utils.hpp"

#include <Ogre.h>

#include <boost/serialization/singleton.hpp>
using namespace boost::serialization;

#define DEF_RESGROUP Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME

#define resourceManager (ResourceManager::get_mutable_instance())
#define resourceManagerConst (ResourceManager::get_const_instance())

class ResourceManager : public singleton<ResourceManager>
{
    public:
        void addResourceLocation(const string &resLocation, bool recursive = true, const string &resGroup = DEF_RESGROUP) const;
        void unloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName);
        void reloadResource(Ogre::ResourceManager* resMgr, const std::string& resourceName, const std::string& resourceGroup);
};

#endif	/* RESOURCESMANAGER_HPP */
