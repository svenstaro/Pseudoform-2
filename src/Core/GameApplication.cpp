#include "Core/GameApplication.hpp"

GameApplication::GameApplication():
	mDt(0.0f)
{
    mSystemsList.push_back(new GraphicSystem());
    mSystemsList.push_back(new InputSystem());
    mSystemsList.push_back(new GuiSystem());

    mRunning = false;

    mAccumulator = 0.0f;
    mDrawn = false;

    this->_init();

    CONNECT(Engine::Events::KeyEvent, "KeyPressed", &GameApplication::keyPressed);
    CONNECT(Engine::Events::MouseMoveEvent, "MouseMoved", &GameApplication::mouseMoved);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }

void GameApplication::_init()
{
    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        LOG(FORMAT("--------------- Start initializating of `%1%` system", curSystem.toString()));
        curSystem.init();
        LOG(FORMAT("--------------- Initializating of `%1%` is finished\n", curSystem.toString()));
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

        float localElapsed = mClock.GetElapsedTime();
        mAccumulator += localElapsed;
        mClock.Reset();

        while (mAccumulator >= mDt)
        {
            BOOST_FOREACH(ISystem &curSystem, mSystemsList)
            {
                curSystem.update(localElapsed);
            }

            mAccumulator -= mDt;
            mDrawn = false;
        }

        if (mDrawn)
        {
        	sf::Sleep(mDt);
        }
        else
        {
        	if (!GraphicSystem::get_const_instance().getRoot()->renderOneFrame()) break;
        	mDrawn = true;
        }
    }

    this->_shutdown();
}

void GameApplication::_shutdown()
{
    mSystemsList.clear();
}

void GameApplication::keyPressed(sf::Event::KeyEvent &eventData)
{
    if (eventData.Code == sf::Key::Escape) mRunning = false;
}

void GameApplication::mouseMoved(sf::Event::MouseMoveEvent& eventData)
{
    cout << FORMAT("New mouse coordinates: (%1%;%2%)\n", eventData.X % eventData.Y);
}
