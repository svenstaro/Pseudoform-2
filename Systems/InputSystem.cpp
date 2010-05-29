#include "InputSystem.h"

#include <iostream>

template<> InputSystem* ISingleton<InputSystem>::mInstance = 0;

InputSystem::InputSystem()
{
	// ...
}

InputSystem::~InputSystem()
{
	mInputWindow.reset();
}

void InputSystem::init()
{
	GraphicSystem::getPtr()->getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);
	// sf::Window has private copy constructor so we can't just create it. So
	// I put the instance to the heap. We have to use it carefully (so I chose
	// boost::shared_ptr)
	mInputWindow = boost::shared_ptr<sf::Window>(new sf::Window(mWindowHandle));
}

void InputSystem::update()
{
	//cout << "X: " << mInputWindow.get()->GetInput().GetMouseX() << " ; Y: " << mInputWindow.get()->GetInput().GetMouseY() << std::endl;
	sf::Event localEvent;
	while(mInputWindow.get()->GetEvent(localEvent))
	{
		if ((localEvent.Type == sf::Event::KeyPressed) && (localEvent.Key.Code == sf::Key::Escape))
			std::cout << "!! lol press !!" << std::endl;
	}
}

std::string InputSystem::toString()
{
	return "InputSystem";
}
