#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
    private:
        MyGUI::StaticImagePtr mPlayButton;

    public:
        void init() {
            Systems::GetGui().loadLayout("Pseudoform.layout");

            mPlayButton = Systems::GetGui().handle()->findWidget<MyGUI::StaticImage>("ButtonPlay");
            mPlayButton->eventMouseButtonClick = MyGUI::newDelegate(this, &MenuState::ButtoPlayClicked);
        }

        void update() {}

        string type() { return "MenuState"; }
        void shutdown()
        {
            Systems::GetGui().unloadLayout("Pseudoform.layout");
        }

        // MyGUI Handlers
        void ButtoPlayClicked(MyGUI::WidgetPtr _sender)
        {
            // Change game state here ...
            READY_TO_ADVANCE();
        }
};

class GameState : public State
{
    public:
        void init() {
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
