#ifndef PseudoformAdditional_INCLUDED
#define PseudoformAdditional_INCLUDED

/*
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/serialization/singleton.hpp>

#include <SFML/Window.hpp>

#include <Ogre.h>
*/

#include "Core/Utils.hpp"

#define LOG(message) Utils::get_const_instance().logHandle().write(message)
#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define CONFIG(key, type, def) Utils::get_const_instance().configHandle().getValue<type>(key, def)

#endif
