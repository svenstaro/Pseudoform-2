#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "Core/GameApplication.hpp"
#include "Core/Systems.hpp"

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

    namespace Systems
    {
		GraphicSystem &GetGraphic() { return GraphicSystem::get_mutable_instance(); }
		InputSystem &GetInput() { return InputSystem::get_mutable_instance(); }
		GuiSystem &GetGui() { return GuiSystem::get_mutable_instance(); }
    }

    namespace World
    {
        GameApplication &Application() { return GameApplication::get_mutable_instance(); }
        void setDimension(string &dimension) { Utils::get_mutable_instance().setDimension(dimension); }

        Object *MakeObject(const string& entityName)
        {
            return EntityManager::get_mutable_instance().MakeObject(entityName);
        }

        Object *GetObject(const string& entityName)
        {
            return EntityManager::get_mutable_instance().GetObject(entityName);
        }
    }
};

#endif	/* ENGINE_HPP */
