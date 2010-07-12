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
        const float GetElapsed() { return GameApplication::get_const_instance().getElapsed(); }

        Object *MakeObject(const string& entityName)
        {
            return EntityManager::get_mutable_instance().MakeObject(entityName);
        }

        Object *GetObject(const string& entityName)
        {
            return EntityManager::get_mutable_instance().GetObject(entityName);
        }

        Light *MakeLight(const string& entityName, Ogre::Light::LightTypes lt = Ogre::Light::LT_POINT,
        		colour diffuse = colour(1, 1, 1), colour specular = colour(1, 1, 1),
        		float attenuation = 10, float power = 1)
        {
			Light *localTemp = EntityManager::get_mutable_instance().MakeLight(entityName);
			localTemp->configure(lt, diffuse, specular, attenuation, power);
			return localTemp;
        }

        Light *GetLight(const string &entityName)
        {
        	return EntityManager::get_mutable_instance().GetLight(entityName);
        }

        unsigned int GetWidth() { return Systems::GetGraphic().getWindow()->getWidth(); }
        unsigned int GetHeight() { return Systems::GetGraphic().getWindow()->getHeight(); }
    }
};

#endif	/* ENGINE_HPP */
