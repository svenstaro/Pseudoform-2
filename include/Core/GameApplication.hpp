#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

#include "Systems/System.hpp"

#include "Core/Systems.hpp"
#include "Core/Utils.hpp"
#include "Managers/Events/Events.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/StateManager.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/format.hpp>

class GameApplication : public singleton<GameApplication>
{
    protected:
        boost::ptr_vector<ISystem> mSystemsList;
        bool mRunning;

        // Game update cycle
        sf::Clock mClock;
        float mDt;
        float mAccumulator;
        float mElapsed;
        float mFrameRate;
        bool mDrawn;

    public:
        GameApplication();
        ~GameApplication();

        void setGameState(bool running);
        const float getElapsed() const;
        const float getFPS() const;

        void _init();
        void Start();
        void _loop();
        void _shutdown();

        // Slots
        void keyPressed(sf::Event::KeyEvent &eventData);
};

#endif
