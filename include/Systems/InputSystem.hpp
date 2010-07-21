#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "System.hpp"
#include "Core/GameApplication.hpp"
#include "Core/Singleton.hpp"
#include "Managers/Events/Events.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/EventManager.hpp"

#include <SFML/Window.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::serialization;

//class InputSystem : public ISystem, public singleton<InputSystem>
class InputSystem : public ISystem, public ISingleton<InputSystem>
{
    private:
        size_t mWindowHandle;
        boost::shared_ptr<sf::Window> mInputWindow;

    public:
        InputSystem();
        ~InputSystem();
        
        const sf::Input &Handle() const;
        sf::Window &Window();

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
