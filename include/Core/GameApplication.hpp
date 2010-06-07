#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

#include "Systems/System.hpp"
#include "PseudoformSystems.hpp"
#include "PseudoformAdditional.hpp"
#include "PseudoformCore.hpp"

class GameApplication : public singleton<GameApplication>
{
	protected:
		// Store for systems list
		boost::ptr_vector<ISystem> mSystemsList;
	
	public:
		GameApplication();
		~GameApplication();

		bool Init();
		void Start();
		void _loop();
		void Shutdown();
};

#endif
