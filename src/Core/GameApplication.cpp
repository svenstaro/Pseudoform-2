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
    CONNECT2(Events::ClosingEvent, "WindowClosing", &GameApplication::WindowClosing);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }
const float GameApplication::getElapsed() const { return mElapsed; }
const float GameApplication::getFPS() const { return floor(mFrameRate+0.5); }

void GameApplication::_init()
{
	LOG_NOFORMAT("Systems initialization:\n=======================\n\n");
	utils.writeTimestamp();

    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        LOG(FORMAT("--------------- Start initialization of `%1%` system", curSystem.toString()));
        curSystem.init();
        LOG(FORMAT("--------------- Initialization of `%1%` is finished\n", curSystem.toString()));
    }

    LOG_NOFORMAT("Finished in: [" + utils.getTimeDifference() + "]\n\n");
	LOG_NOFORMAT("Game initialization:\n====================\n\n");
	utils.writeTimestamp();
}

void GameApplication::Start()
{
    mRunning = true;

    utils.setMediaPath(CONFIG("resources.MediaFolder", string, "Media"));

    SIGNAL(Engine::Events::GlobalInitEvent, "Inited", );

    LOG_NOFORMAT("\nFinished in: [" + utils.getTimeDifference() + "]\n");
	LOG_NOFORMAT("\nGame Loop:\n==========\n\n");
	utils.writeTimestamp();

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
            stateManager.update();

            mAccumulator -= mDt;
            mDrawn = false;
        }

        if (mDrawn)
        {
            sf::Sleep(mDt);
        }
        else
        {
            if (!graphicSystem.getRoot()->renderOneFrame())
                LOG("Something bad happened in the render cycle!");

            mDrawn = true;
        }
    }

    this->_shutdown();
}

void GameApplication::_shutdown()
{
    LOG_NOFORMAT("\nFinished in: [" + utils.getTimeDifference() + "]\n");
    mSystemsList.clear();
}

void GameApplication::WindowClosing(Ogre::RenderWindow *rw, bool &shouldClose)
{
    if(shouldClose){
        LOG("Clicked on [X] -> closing");
        mRunning = false;
    }
}

void GameApplication::keyPressed(const OIS::KeyEvent &e)
{
	//if (e.key == OIS::KC_ESCAPE) mRunning = false; //Game wants it

	if (e.key == OIS::KC_I)
	{
		if (inputSystem.getKeyboard()->isModifierDown(OIS::Keyboard::Ctrl))
		{
			mStatsVisible = !mStatsVisible;

			if (mStatsVisible)
			{
				guiSystem.loadLayout("Statistic.layout");
				mStatsUpdate = CONNECT0(Engine::Events::GlobalUpdateEvent, "Updated", &GameApplication::showStats);
			}
			else
			{
				if (mStatsUpdate.connected()) mStatsUpdate.disconnect();
				guiSystem.unloadLayout("Statistic.layout");
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
		string batches = boost::lexical_cast<string>(graphicSystem.getWindow()->getBatchCount());
		string triangles = boost::lexical_cast<string>(graphicSystem.getWindow()->getTriangleCount());

		Gui *handle = guiSystem.handle();

		handle->findWidget<Widget>("fps_statistic")->setCaption("#FFFFFF fps: #ffe1bd" + fps);
		handle->findWidget<Widget>("batches_statistic")->setCaption("#FFFFFF batches: #ffe1bd" + batches);
		handle->findWidget<Widget>("triangles_statistic")->setCaption("#FFFFFF triangles: #ffe1bd" + triangles);
	}
}
