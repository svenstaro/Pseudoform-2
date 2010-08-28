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
        StateManager &GetState() { return StateManager::get_mutable_instance(); }
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
        const float GetElapsed() { return gameApplicationConst.getElapsed(); }
/*
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

        Camera *MakeCamera(const string &cameraName, bool attachViewport = false, Camera::CameraType camType = Camera::DONT_USE,
                const float nearClip = 1, const float farClip = 1000,
                bool autoAR = true, const float FOV = 90, vec3 pos = vec3(0, 1000, 1000), vec3 lookAt = vec3(0, 0, 0))
        {
            Camera *localTemp = EntityManager::get_mutable_instance().MakeCamera(cameraName);
            localTemp->configure(nearClip, farClip, autoAR, FOV, pos, lookAt);
            if (attachViewport)
            {
                GraphicSystem::get_mutable_instance().getViewport()->setCamera(localTemp->cameraHandle());
            }

            localTemp->setCameraType(camType);

            return localTemp;
        }

        Camera *MakeCamera(const string &name, const string filename)
        {
            Camera *localTemp = EntityManager::get_mutable_instance().MakeCamera(name);
            localTemp->loadFromFile(filename);
            return localTemp;
        }

        Camera *GetCamera(const string &cameraName)
        {
            return EntityManager::get_mutable_instance().GetCamera(cameraName);
        }
*/
        unsigned int GetWidth() { return graphicSystem.getWindow()->getWidth(); }
        unsigned int GetHeight() { return graphicSystem.getWindow()->getHeight(); }

        template<typename WidgetType>
        WidgetType *findWidget(const string &name)
        {
        	return GuiSystem::get_mutable_instance().handle()->findWidget<WidgetType>(name);
        }
    }
};

#endif	/* ENGINE_HPP */
