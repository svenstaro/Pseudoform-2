#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "Core/Managers.hpp"
#include "Core/GameApplication.hpp"

namespace Engine
{
    GameApplication &Application() { return GameApplication::get_mutable_instance(); }

    namespace Managers
    {
        ConfigManager &GetConfig() { return Utils::get_mutable_instance().configHandle(); }
        LogManager &GetLog() { return Utils::get_mutable_instance().logHandle(); }
        ResourcesManager &GetResources() { return Utils::get_mutable_instance().resourceHandle(); }
    }
};

#endif	/* ENGINE_HPP */
