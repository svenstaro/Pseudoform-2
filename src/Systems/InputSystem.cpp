#include "Systems/InputSystem.hpp"

#include <iostream>

InputSystem::InputSystem() { }

InputSystem::~InputSystem() { }

void InputSystem::init()
{
    //GraphicSystem::getSingletonPtr()->getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);

    GraphicSystem::get_const_instance().getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);
    mInputWindow.Create(mWindowHandle);

    LOG("\t- SFML window is created");
}

void InputSystem::update()
{
    int x = mInputWindow.GetInput().GetMouseX();
    int y = mInputWindow.GetInput().GetMouseY();
    //cout << "X: " << x << " ; Y: " << y << std::endl;
    sf::Event localEvent;

    while(mInputWindow.GetEvent(localEvent))
    {
        if ((localEvent.Type == sf::Event::KeyPressed) && (localEvent.Key.Code == sf::Key::Escape))
        {
            std::cout << "Esc is pressed" << std::endl;
            GameApplication::get_mutable_instance().setGameState(false);
        }
        else if (localEvent.Type == sf::Event::Closed)
        {
            std::cout << "Hangg!";
            GameApplication::get_mutable_instance().setGameState(false);
        }
    }
}

std::string InputSystem::toString()
{
    return "InputSystem";
}
