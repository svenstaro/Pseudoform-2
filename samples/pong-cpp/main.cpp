#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
    public:
        MenuState() {
            Systems::GetGui().loadLayout("Pseudoform.layout");
        }

        void update() {}
        void shutdown() {}
};

class GameState : public State
{
    public:
        GameState() {
            World::MakeCamera("MenuCamera", true, Camera::DONT_USE);
            World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection( vec3(0, -1, 1) );
            World::MakeObject("background")->setScale(vec3(100, 100, 100));
        }

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
