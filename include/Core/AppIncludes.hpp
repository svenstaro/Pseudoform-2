#ifndef _APP_INCLUDES_
#define _APP_INCLUDES_

/* *********** RENDER/OGRE *********** */
#include <Ogre.h>

/* *********** BOOST *********** */
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/serialization/singleton.hpp>

#define bforeach BOOST_FOREACH
#define FORMAT(parentString, params) (boost::format(parentString) % params).str()

/* ************ SFML ************* */
#include <SFML/Window.hpp>

/* *********** ENGINE *********** */
#include "Managers/ConfigManager.hpp"
#define CONFIG(key, type, def) Utils::get_const_instance().configHandle().getValue<type>(key, def);

#include "Managers/LogManager.hpp"
#define LOG(message) Utils::get_const_instance().logHandle().write(message);

#include "Core/Types.hpp"
#include "Core/Utils.hpp"

/* ************ SYSTEMS *********** */
#include "Systems/GraphicSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/GuiSystem.hpp"

#endif
