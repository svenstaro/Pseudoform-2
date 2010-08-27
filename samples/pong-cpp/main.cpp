#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
    public:
        void init() {
            Systems::GetGui().loadLayout("Pseudoform.layout");

            World::findWidget<MyGUI::StaticImage>("ButtonPlay")->eventMouseButtonClick =
            		MyGUI::newDelegate(this, &MenuState::ButtoPlayClicked);
        }

        void shutdown() {
            Systems::GetGui().unloadLayout("Pseudoform.layout");
        }

        // MyGUI Handlers
        void ButtoPlayClicked(MyGUI::WidgetPtr _sender)
        {
            // Change game state here ...
            READY_TO_ADVANCE();
        }

        void update() {}
        string type() { return "MenuState"; }
};

class GameState : public State
{
    public:
        void init() {
            World::MakeCamera("MenuCamera", true, Camera::FREE);
            //World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection(vec3(0, 100, 0));

            World::MakeLight("PointLight", Ogre::Light::LT_POINT,
            		colour(1.0, 0.0, 0.0), colour(1.0, 0.0, 0.0))->lightHandle()->setPosition(vec3(0, 150, 250));
            World::MakeLight("DirectionalLight", Ogre::Light::LT_DIRECTIONAL,
            		colour(.25, .25, 0), colour(.25, .25, 0))->lightHandle()->setDirection(vec3(0, -1, 1));
            World::MakeLight("SpotLight", Ogre::Light::LT_SPOTLIGHT,
            		colour(0, 0, 1.0), colour(0, 0, 1.0))->lightHandle()->setDirection(vec3(-1, -1, 0));
            World::GetLight("SpotLight")->lightHandle()->setPosition(vec3(300, 300, 0));

            World::MakeObject("ErrorObject");
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
