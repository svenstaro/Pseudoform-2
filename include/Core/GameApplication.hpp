#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

#include "Systems/System.hpp"

#include "Core/Systems.hpp"
#include "Core/Utils.hpp"
#include "Managers/Events/Events.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/EventManager.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/format.hpp>

class GameApplication : public singleton<GameApplication>
{
    protected:
        boost::ptr_vector<ISystem> mSystemsList;
        bool mRunning;

        // Game update cycle
        sf::Clock mClock;
        const float mDt;
        float mAccumulator;

    public:
        GameApplication();
        ~GameApplication();

        void setGameState(bool running);

        void _init();
        void Start();
        void _loop();
        void _shutdown();

        // Slots
        void keyPressed(sf::Event::KeyEvent &eventData);
        void mouseMoved(sf::Event::MouseMoveEvent &eventData);
};

#endif
