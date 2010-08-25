#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
	private:
		MyGUI::VectorWidgetPtr mListWidgets;

    public:
        void init() {
            mListWidgets = Systems::GetGui().loadLayout("Pseudoform.layout");

            MyGUI::StaticImagePtr button = Systems::GetGui().handle()->findWidget<MyGUI::StaticImage>("ButtonPlay");
            button->eventMouseButtonClick = MyGUI::newDelegate(this, &MenuState::ButtoPlayClicked);
        }

        void update()
        {
        	MyGUI::StaticTextPtr fps = Systems::GetGui().handle()->findWidget<MyGUI::StaticText>("FPS");
        	float fpsCount = GameApplication::get_const_instance().getFPS();

        	fps->setCaption("FPS:" + boost::lexical_cast<string>(fpsCount));
        }

        string type() { return "MenuState"; }
        void shutdown()
        {
        	Systems::GetGui().unloadLayout(mListWidgets);
        }

        // MyGUI Handlers
        void ButtoPlayClicked(MyGUI::WidgetPtr _sender)
        {
        	// Change game state here ...
        	std::cout << "Achtung! Button is clicked";
        	READY_TO_ADVANCE();
        }
};

class GameState : public State
{
    public:
        void init() {
        	cout << "in Game state init function!";
            World::MakeCamera("MenuCamera", true, Camera::FREE);
            World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection(vec3(0, -1, 1));
            World::MakeObject("background")->setScale(vec3(100, 100, 100));
        }

        string type() { return "GameState"; }
        void update() {}
        void shutdown() {}
};

int main()
{
    Managers::GetState().push(new(MenuState));
    Managers::GetState().push(new(GameState));

    World::Application().Start();

    return 0;
}
