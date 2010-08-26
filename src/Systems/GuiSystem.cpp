#include "Systems/GuiSystem.hpp"

template<> GuiSystem* ISingleton<GuiSystem>::mInstance = 0;

GuiSystem::GuiSystem() { }

GuiSystem::~GuiSystem()
{
	mGUI->shutdown();
	delete mGUI;
	mGUI = 0;

	mPlatform->shutdown();
	delete mPlatform;
	mPlatform = 0;
}

void GuiSystem::init()
{
	mPlatform = new MyGUI::OgrePlatform();
	LOG("\t- Platform object is created");
	mPlatform->initialise(GraphicSystem::get_const_instance().getWindow(), GraphicSystem::get_const_instance().getSceneMgr());
	LOG("\t- Platform is initialised");

	mGUI = new MyGUI::Gui();
	LOG("\t- MyGUI object is created");
	mGUI->initialise();
	LOG("\t- MyGUI is initialised");
}

void GuiSystem::update(float elapsed) { }

std::string GuiSystem::toString()
{
    return "GuiSystem";
}
void GuiSystem::loadLayout(const string &name)
{
	// TODO: [GuiSystem::loadLayout] Check the name is already in map!
	mWidgetLayouts[name] = MyGUI::LayoutManager::getInstance().load(name);
}

void GuiSystem::unloadLayout(const string &name)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mWidgetLayouts[name]);
}
