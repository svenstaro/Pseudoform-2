#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "Core/GameApplication.hpp"

#include "Managers/ConfigManager.hpp"
#include "Managers/LogManager.hpp"
#include "Managers/ResourceManager.hpp"
#include "Managers/EntityManager.hpp"
#include "Managers/EventManager.hpp"

namespace Engine
{
    namespace Managers
    {
        ConfigManager &GetConfig() { return ConfigManager::get_mutable_instance(); }
        LogManager &GetLog() { return LogManager::get_mutable_instance(); }
        ResourceManager &GetResource() { return ResourceManager::get_mutable_instance(); }
        EntityManager &GetEntity() { return EntityManager::get_mutable_instance(); }
        EventManager &GetEvent() { return EventManager::get_mutable_instance(); }
    }

    namespace World
    {
        GameApplication &Application() { return GameApplication::get_mutable_instance(); }
        void setDimension(string &dimension) { Utils::get_mutable_instance().setDimension(dimension); }

        Entity3D *Make3DEntity(const string &entityName)
        {
            return EntityManager::get_mutable_instance().Make3DEntity(entityName);
        }
        Entity2D *Make2DEntity(const string &entityName)
        {
            return EntityManager::get_mutable_instance().Make2DEntity(entityName);
        }

        Entity3D *Get3DEntity(const string &entityName)
        {
            return Get3DEntity(entityName);
        }
        Entity2D *Get2DEntity(const string &entityName)
        {
            return Get2DEntity(entityName);
        }
    }
};

#endif	/* ENGINE_HPP */
