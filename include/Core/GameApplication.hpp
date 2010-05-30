#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

// Listeners
#include "Listeners/GameListener.hpp"
#include "Listeners/MaterialListener.hpp"

// Systems
// Moved to the AppIncludes.hpp!

/*
#include "Systems/InputSystem.hpp"
#include "Systems/PhysicSystem.hpp"
#include "Systems/SoundSystem.hpp"
*/

#include "Systems/System.hpp"
#include "Core/AppIncludes.hpp"

class GameApplication
{
	protected:
		// Store for systems list
		boost::ptr_vector<ISystem> mSystemsList;

		// Listeners
		GameListener *mGameListener;
		MaterialListener *mMaterialListener;
	
	public:
		GameApplication();
		~GameApplication();

		bool init();
		void start();
		void loop();
		void shutdown();
};

#endif
