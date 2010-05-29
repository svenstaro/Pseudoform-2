#include "InputSystem.h"

#include <iostream>

template<> InputSystem* ISingleton<InputSystem>::mInstance = 0;

InputSystem::InputSystem()
{
	// ...
}

InputSystem::~InputSystem()
{
}

void InputSystem::init()
{
	GraphicSystem::getPtr()->getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);
	// sf::Window has private copy constructor so we can't just create it. So
	// I put the instance to the heap. We have to use it carefully (so I chose
	// boost::shared_ptr)
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
			std::cout << "!! lol press !!" << std::endl;
		}
		else if (localEvent.Type == sf::Event::Closed)
		{
			std::cout << "Hangg!";
			Utils::getPtr()->mRunning = false;
		}
	}
}

std::string InputSystem::toString()
{
	return "InputSystem";
}
