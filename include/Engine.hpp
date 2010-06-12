#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "Core/Managers.hpp"
#include "Core/GameApplication.hpp"

namespace Engine
{
    GameApplication &Application() { return GameApplication::get_mutable_instance(); }

    namespace Managers
    {
        ConfigManager &Config() { return Utils::get_mutable_instance().configHandle(); }
        LogManager &Log() { return Utils::get_mutable_instance().logHandle(); }
        ResourcesManager &Resources() { return Utils::get_mutable_instance().resourceHandle(); }
    }
};

#endif	/* ENGINE_HPP */
