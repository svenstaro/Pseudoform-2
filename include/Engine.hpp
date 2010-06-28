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
        void setDimension(const string &dimension) { Utils::get_mutable_instance().setDimension(dimension); }
    }
};

#endif	/* ENGINE_HPP */
