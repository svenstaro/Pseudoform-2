#include "GuiSystem.h"

template<> GuiSystem* ISingleton<GuiSystem>::mInstance = 0;

GuiSystem::GuiSystem() { }

GuiSystem::~GuiSystem() { }

void GuiSystem::init() { }

void GuiSystem::update() { }

std::string GuiSystem::toString()
{
	return "GuiSystem";
}
