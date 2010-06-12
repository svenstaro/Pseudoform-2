#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "System.hpp"
#include "Core/GameApplication.hpp"

#include <SFML/Window.hpp>
#include <boost/serialization/singleton.hpp>

using namespace boost::serialization;

class InputSystem : public ISystem, public singleton<InputSystem>
{
    private:
        size_t mWindowHandle;
        sf::Window mInputWindow;

    public:
        InputSystem();
        ~InputSystem();

        // Inherited from ISystem
        void init();
        void update();
        std::string toString();
};

#endif
