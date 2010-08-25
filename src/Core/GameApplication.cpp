#include "Core/GameApplication.hpp"

GameApplication::GameApplication()
{
    mSystemsList.push_back(new GraphicSystem());
    mSystemsList.push_back(new InputSystem());
    mSystemsList.push_back(new GuiSystem());

    mRunning = false;

    mAccumulator = mElapsed = mFrameRate = 0.0f;
    mDrawn = false;
    mDt = 1.f / 60.f;

    this->_init();

    CONNECT(Engine::Events::KeyEvent, "KeyPressed", &GameApplication::keyPressed);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }
const float GameApplication::getElapsed() const { return mElapsed; }
const float GameApplication::getFPS() const { return floor(mFrameRate+0.5); }

void GameApplication::_init()
{
	LOG_NOFORMAT("\t\t\t\t|||||||||||||||||||||||||||| Systems initialization ||||||||||||||||||||||||||||\n\n");
    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        LOG(FORMAT("--------------- Start initialization of `%1%` system", curSystem.toString()));
        curSystem.init();
        LOG(FORMAT("--------------- Initialization of `%1%` is finished\n", curSystem.toString()));
    }
	LOG_NOFORMAT("\t\t\t\t||||||||||||||||||||||||||||||| Game initialization ||||||||||||||||||||||||||||||\n\n");
}

void GameApplication::Start()
{
    mRunning = true;

    SIGNAL(Engine::Events::GlobalInitEvent, "Inited", );

	LOG_NOFORMAT("\n\t\t\t\t|||||||||||||||||||||||||||||||||| Game Loop |||||||||||||||||||||||||||||||||||||\n\n");
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

        mFrameRate = 1.f / mElapsed;

        while (mAccumulator >= mDt)
        {
            BOOST_FOREACH(ISystem &curSystem, mSystemsList)
            {
                curSystem.update(mElapsed);
            }
            SIGNAL(Engine::Events::GlobalUpdateEvent, "Updated", );
            StateManager::get_mutable_instance().update();

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

void GameApplication::keyPressed(const OIS::KeyEvent &e)
{
	if (e.key == OIS::KC_ESCAPE) mRunning = false;
}
