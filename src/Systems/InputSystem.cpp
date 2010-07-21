#include "Systems/InputSystem.hpp"

#include <iostream>

template<> InputSystem* ISingleton<InputSystem>::mInstance = 0;

InputSystem::InputSystem() { }

InputSystem::~InputSystem() { }

void InputSystem::init()
{
    GraphicSystem::get_const_instance().getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);
    LOG("\t- Got window handle from ogre");
    mInputWindow = boost::shared_ptr<sf::Window>( new sf::Window(mWindowHandle) );
    //mInputWindow->Create(mWindowHandle);
    LOG("\t- SFML window is created");
}

const sf::Input &InputSystem::Handle() const
{
	return mInputWindow.get()->GetInput();
}

sf::Window &InputSystem::Window()
{
	return *mInputWindow.get();
}

void InputSystem::update(float elapsed)
{
    sf::Event localEvent;

    while(mInputWindow->GetEvent(localEvent))
    {
        using namespace Engine::Events;
        sf::Event::EventType type = localEvent.Type;
        
        if (localEvent.Type == sf::Event::KeyPressed) {
            SIGNAL(KeyEvent, "KeyPressed", localEvent.Key);
        } else if (type == sf::Event::KeyReleased) {
            SIGNAL(KeyEvent, "KeyReleased", localEvent.Key);
        } else if (type == sf::Event::Resized) {
            SIGNAL(SizeEvent, "Resized", localEvent.Size);
        } else if (type == sf::Event::TextEntered) {
            SIGNAL(TextEvent, "TextEntered", localEvent.Text);
        } else if (type == sf::Event::MouseButtonPressed) {
            SIGNAL(MouseButtonEvent, "MouseButtonPressed", localEvent.MouseButton);
        } else if (type == sf::Event::MouseButtonReleased) {
            SIGNAL(MouseButtonEvent, "MouseButtonReleased", localEvent.MouseButton);
        } else if (type == sf::Event::MouseMoved) {
            SIGNAL(MouseMoveEvent, "MouseMoved", localEvent.MouseMove);
        } else if (type == sf::Event::MouseWheelMoved) {
            SIGNAL(MouseWheelEvent, "MouseWheelMoved", localEvent.MouseWheel);
        } else if (type == sf::Event::JoyButtonPressed) {
            SIGNAL(JoyButtonEvent, "JoyButtonPressed", localEvent.JoyButton);
        } else if (type == sf::Event::JoyButtonReleased) {
            SIGNAL(JoyButtonEvent, "JoyButtonReleased", localEvent.JoyButton);
        } else if (type == sf::Event::JoyMoved) {
            SIGNAL(JoyMoveEvent, "JoyMoved", localEvent.JoyMove);
        } else if (type == sf::Event::Closed) {
            SIGNAL(CloseEvent, "WindowClosed", );
        } else if (type == sf::Event::LostFocus) {
            SIGNAL(LostFocusEvent, "WindowLostFocus", );
        } else if (type == sf::Event::GainedFocus) {
            SIGNAL(GainFocusEvent, "WindowGainedFocus", );
        } else if (type == sf::Event::MouseEntered) {
            SIGNAL(MouseEnteredEvent, "WindowMouseEntered", );
        }
    }
}

std::string InputSystem::toString()
{
    return "InputSystem";
}
