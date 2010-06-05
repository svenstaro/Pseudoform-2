#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

#include "Systems/System.hpp"
#include "PseudoformSystems.hpp"

class GameApplication : public singleton<GameApplication>
{
	protected:
		// Store for systems list
		boost::ptr_vector<ISystem> mSystemsList;
	
	public:
		GameApplication();
		~GameApplication();

		bool init();
		void start();
		void loop();
		void shutdown();
};

#endif
