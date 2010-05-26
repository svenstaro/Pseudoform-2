#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

// Listeners
#include "Listeners/GameListener.h"
#include "Listeners/MaterialListener.h"

// Systems
#include "Systems/GraphicSystem.h"
/*
#include "Systems/GuiSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/SoundSystem.h"
*/

#include "Systems/System.h"
#include "Core/OgreIncludes.h"
#include "Core/BoostIncludes.h"

class GameApplication
{
	protected:
		// Store for systems list
		boost::ptr_vector<ISystem> mSystemsList;

		// Listeners
		GameListener *mGameListener;
		MaterialListener *mMaterialListener;

		// Additional stuff
		bool mRunning;
	
	public:
		GameApplication();
		~GameApplication();

		bool init();
		void start();
		void loop();
		void shutdown();
};

#endif
