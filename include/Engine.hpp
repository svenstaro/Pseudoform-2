#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include "PseudoformCore.hpp"
#include "Managers/ConfigManager.hpp"

class Engine
{
    public:
        const GameApplication &Application() const { return GameApplication::get_const_instance(); }
};

#endif	/* ENGINE_HPP */

