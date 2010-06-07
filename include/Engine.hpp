#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "PseudoformCore.hpp"
#include "PseudoformManagers.hpp"

class Engine
{
    public:
        GameApplication &Application() { return GameApplication::get_mutable_instance(); }
        ConfigManager &Config() { return Utils::get_mutable_instance().configHandle(); }
		LogManager &Log() { return Utils::get_const_instance().logHandle(); }

};

#endif	/* ENGINE_HPP */
