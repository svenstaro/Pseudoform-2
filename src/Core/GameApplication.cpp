#include "Core/GameApplication.hpp"

GameApplication::GameApplication()
{
    mSystemsList.push_back(new GraphicSystem());
    mSystemsList.push_back(new InputSystem());
    mSystemsList.push_back(new GuiSystem());

    mRunning = false;

    mAccumulator = 0.0f;
    mElapsed = 0.0f;
    mDrawn = false;
    mDt = 1.f / 60.f;

    this->_init();

    CONNECT(Engine::Events::KeyEvent, "KeyPressed", &GameApplication::keyPressed);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }
const float GameApplication::getElapsed() const
{
	return mElapsed;
}

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

    bool showCursor = CONFIG("window.showCursor", bool, false);
    InputSystem::get_mutable_instance().Window().ShowMouseCursor(showCursor);

    SIGNAL(Engine::Events::GlobalInitEvent, "Inited", );

    this->_loop();
}

void GameApplication::_loop()
{
    while(mRunning)
    {
        Ogre::WindowEventUtilities::messagePump();

        mElapsed = mClock.GetElapsedTime();
        mAccumulator += mElapsed;
        mClock.Reset();

        while (mAccumulator >= mDt)
        {
            BOOST_FOREACH(ISystem &curSystem, mSystemsList)
            {
                curSystem.update(mElapsed);
            }
            SIGNAL(Engine::Events::GlobalUpdateEvent, "Updated", );
            StateManager::get_mutable_instance().getActiveState()->update();

            mAccumulator -= mDt;
            mDrawn = false;
        }

        if (mDrawn)
        {
        	sf::Sleep(mDt);
        }
        else
        {
        	if (!GraphicSystem::get_const_instance().getRoot()->renderOneFrame())
        		LOG("Something bad happened in the render cycle!");

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
