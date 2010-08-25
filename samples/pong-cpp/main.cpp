#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
    public:
        MenuState() {
            Systems::GetGui().loadLayout("Pseudoform.layout");

            MyGUI::StaticImagePtr button = Systems::GetGui().getGui()->findWidget<MyGUI::StaticImage>("ButtonPlay");
            button->eventMouseButtonClick = MyGUI::newDelegate(this, &MenuState::ButtoPlayClicked);
        }

        void update()
        {
        	MyGUI::StaticTextPtr fps = Systems::GetGui().getGui()->findWidget<MyGUI::StaticText>("FPS");
        	float fpsCount = GameApplication::get_const_instance().getFPS();

        	fps->setCaption("FPS:" + boost::lexical_cast<string>(fpsCount));
        }

        string type() { return "MenuState"; }
        void shutdown() {}

        // MyGUI Handlers
        void ButtoPlayClicked(MyGUI::WidgetPtr _sender)
        {
        	// Change game state here ...
        	std::cout << "Achtung! Button is clicked";
        }
};

class GameState : public State
{
    public:
        GameState() {
            World::MakeCamera("MenuCamera", true, Camera::DONT_USE);
            World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection( vec3(0, -1, 1) );
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
