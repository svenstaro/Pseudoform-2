#ifndef _GAME_APPLICATION_H_
#define _GAME_APPLICATION_H_

#include "Systems/System.hpp"
#include "Core/Systems.hpp"

#include "Predefines.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/format.hpp>

class GameApplication : public singleton<GameApplication>
{
    protected:
        boost::ptr_vector<ISystem> mSystemsList;
        bool mRunning;

    public:
        GameApplication();
        ~GameApplication();

        void setGameState(bool running);

        void _init();
        void Start();
        void _loop();
        void _shutdown();
};

#endif
