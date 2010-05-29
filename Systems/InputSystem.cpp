#include "InputSystem.h"

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

void InputSystem::update() { }

std::string InputSystem::toString()
{
	return "InputSystem";
}
