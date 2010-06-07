#include "Core/GameApplication.hpp"

GameApplication::GameApplication()
{
    mSystemsList.push_back(new GraphicSystem());
	mSystemsList.push_back(new InputSystem());
	mSystemsList.push_back(new GuiSystem());
}

GameApplication::~GameApplication() { }

bool GameApplication::Init()
{
	bforeach(ISystem &curSystem, mSystemsList)
	{
		curSystem.init();
		LOG(FORMAT("--------------- Initializating of `%1%` is finished", curSystem.toString()));
	}
	return true;
}

void GameApplication::Start()
{
	Utils::get_mutable_instance().mRunning = true;

	// Create game engine controllers
	// Create world
	// Load resource

    this->_loop();
}

void GameApplication::_loop()
{
	while(Utils::get_const_instance().mRunning)
	{
		Ogre::WindowEventUtilities::messagePump();

		bforeach(ISystem &curSystem, mSystemsList)
		{
			curSystem.update();
		}

        if (!GraphicSystem::getSingletonPtr()->getRoot()->renderOneFrame()) break;
	}
}

void GameApplication::Shutdown()
{
    mSystemsList.clear();
}
