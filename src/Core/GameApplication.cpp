#include "Core/GameApplication.hpp"

GameApplication::GameApplication()
{
    mSystemsList.push_back(new GraphicSystem());
    mSystemsList.push_back(new InputSystem());
    mSystemsList.push_back(new GuiSystem());

    mRunning = false;

    this->_init();
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }

void GameApplication::_init()
{
    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        curSystem.init();
        LOG(FORMAT("--------------- Initializating of `%1%` is finished", curSystem.toString()));
    }
}

void GameApplication::Start()
{
    mRunning = true;

    // Create game engine controllers
    // Create world
    // Load resource

    this->_loop();
}

void GameApplication::_loop()
{
    while(mRunning)
    {
        Ogre::WindowEventUtilities::messagePump();

        BOOST_FOREACH(ISystem &curSystem, mSystemsList)
        {
            curSystem.update();
        }

        //if (!GraphicSystem::getSingletonPtr()->getRoot()->renderOneFrame()) break;
        if (!GraphicSystem::get_const_instance().getRoot()->renderOneFrame()) break;
    }

    this->_shutdown();
}

void GameApplication::_shutdown()
{
    mSystemsList.clear();
}
