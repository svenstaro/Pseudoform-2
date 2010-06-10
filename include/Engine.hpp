#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "PseudoformCore.hpp"
#include "PseudoformManagers.hpp"

namespace Engine
{
    GameApplication &Application() { return GameApplication::get_mutable_instance(); }

    ConfigManager &Config() { return Utils::get_mutable_instance().configHandle(); }
    LogManager &Log() { return Utils::get_mutable_instance().logHandle(); }
    ResourcesManager &Resources() { return Utils::get_mutable_instance().resourceHandle(); }
};

#endif	/* ENGINE_HPP */
