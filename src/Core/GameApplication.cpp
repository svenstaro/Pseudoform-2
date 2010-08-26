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

    mStatsVisible = false;

    CONNECT(Engine::Events::KeyEvent, "KeyPressed", &GameApplication::keyPressed);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }
const float GameApplication::getElapsed() const { return mElapsed; }
const float GameApplication::getFPS() const { return floor(mFrameRate+0.5); }

void GameApplication::_init()
{
	LOG_NOFORMAT("Systems initialization:\n=======================\n\n");
	Utils::get_mutable_instance().writeTimestamp();

    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        LOG(FORMAT("--------------- Start initialization of `%1%` system", curSystem.toString()));
        curSystem.init();
        LOG(FORMAT("--------------- Initialization of `%1%` is finished\n", curSystem.toString()));
    }

    LOG_NOFORMAT("Finished in: [" + Utils::get_mutable_instance().getTimeDifference() + "]\n\n");
	LOG_NOFORMAT("Game initialization:\n====================\n\n");
	Utils::get_mutable_instance().writeTimestamp();
}

void GameApplication::Start()
{
    mRunning = true;

    SIGNAL(Engine::Events::GlobalInitEvent, "Inited", );

    LOG_NOFORMAT("\nFinished in: [" + Utils::get_mutable_instance().getTimeDifference() + "]\n");
	LOG_NOFORMAT("\nGame Loop:\n==========\n\n");
	Utils::get_mutable_instance().writeTimestamp();

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
    LOG_NOFORMAT("\nFinished in: [" + Utils::get_mutable_instance().getTimeDifference() + "]\n");
    mSystemsList.clear();
}

void GameApplication::keyPressed(const OIS::KeyEvent &e)
{
	if (e.key == OIS::KC_ESCAPE) mRunning = false;

	if (e.key == OIS::KC_I)
	{
		if (InputSystem::get_mutable_instance().getKeyboard()->isModifierDown(OIS::Keyboard::Ctrl))
		{
			mStatsVisible = !mStatsVisible;

			if (mStatsVisible)
			{
				GuiSystem::get_mutable_instance().loadLayout("Statistic.layout");
				mStatsUpdate = CONNECT0(Engine::Events::GlobalUpdateEvent, "Updated", &GameApplication::showStats);
			}
			else
			{
				if (mStatsUpdate.connected()) mStatsUpdate.disconnect();
				GuiSystem::get_mutable_instance().unloadLayout("Statistic.layout");
			}
		}
	}
}

void GameApplication::showStats()
{
	if (mStatsVisible)
	{
		using namespace MyGUI;

		string fps = boost::lexical_cast<string>(getFPS());
		string batches = boost::lexical_cast<string>(GraphicSystem::get_mutable_instance().getWindow()->getBatchCount());
		string triangles = boost::lexical_cast<string>(GraphicSystem::get_mutable_instance().getWindow()->getTriangleCount());

		Gui *handle = GuiSystem::get_mutable_instance().handle();

		handle->findWidget<Widget>("fps_statistic")->setCaption("#FFFFFF fps: #ffe1bd" + fps);
		handle->findWidget<Widget>("batches_statistic")->setCaption("#FFFFFF batches: #ffe1bd" + batches);
		handle->findWidget<Widget>("triangles_statistic")->setCaption("#FFFFFF triangles: #ffe1bd" + triangles);
	}
}
