#include "GameApplication.h"

GameApplication::GameApplication()
{
	mSystemsList.push_back(new GraphicSystem());
	mSystemsList.push_back(new InputSystem());
	mSystemsList.push_back(new GuiSystem());

	// ...

	mRunning = true;
}

GameApplication::~GameApplication() { }

bool GameApplication::init()
{
	bforeach(ISystem &curSystem, mSystemsList)
	{
		curSystem.init();
		LOG(FORMAT("Initializating of `%1%` ---------------\n", curSystem.toString()));
	}

	//mGameListener = new GameListener();
	//mMaterialListener = new MaterialListener();

	// TODO: Set event callbacks for keyboard, mouse

	// TODO: We really needn't in listeners?
	//GraphicSystem::getPtr()->getRoot()->addFrameListener(mGameListener);
	//Ogre::MaterialManager::getSingletonPtr()->addListener(mMaterialListener);

	return true;
}

void GameApplication::start()
{
	// Create game engine controllers
	// Create world
	// Load resource
}

void GameApplication::loop()
{
	while(GraphicSystem::getPtr()->getRoot()->renderOneFrame())
	{
		Ogre::WindowEventUtilities::messagePump();

		// Capture keyboard and mouse
		bforeach(ISystem &curSystem, mSystemsList)
		{
			curSystem.update();
		}
		// Check world state in StateManager

		//if (!) break;
	}
}

void GameApplication::shutdown()
{
	// Delete managers
	// Clean script system

	// We needn't in deleting manually singleton-objects like:
	// delete GraphicSystem::getPtr();
	// We've done this manually in ISingleton interface!

	// TODO: Clear mSystemsList

	//delete mGameListener;
	//delete mMaterialListener;
}
