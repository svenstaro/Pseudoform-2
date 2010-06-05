#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "PseudoformCore.hpp"
#include "Managers/ConfigManager.hpp"

class Engine
{
    public:
        GameApplication &Application() { return GameApplication::get_mutable_instance(); }
};

#endif	/* ENGINE_HPP */
