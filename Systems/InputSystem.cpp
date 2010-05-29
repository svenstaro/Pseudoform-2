#include "InputSystem.h"

#include <iostream>

InputSystem::InputSystem() { }

InputSystem::~InputSystem() { }

void InputSystem::init()
{
	GraphicSystem::get_const_instance();
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
	if (mInputWindow.IsOpened())
		cout << "Opened\n";
	else
		cout << "Unopened";

	while(mInputWindow.GetEvent(localEvent))
	{
		if ((localEvent.Type == sf::Event::KeyPressed) && (localEvent.Key.Code == sf::Key::Escape))
		{
			std::cout << "!! lol press !!" << std::endl;
		}
		else if (localEvent.Type == sf::Event::Closed)
		{
			std::cout << "Hangg!";
			Utils::get_mutable_instance().mRunning = false;
		}
	}
}

std::string InputSystem::toString()
{
	return "InputSystem";
}
