#include "Engine.hpp"

using namespace std;
using namespace Engine;

int main()
{
    Managers::GetLog().write("Adding new source location...", "pong.log");
    
    World::MakeCamera("MainCamera", true, Camera::FREE);
    World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection( vec3(0, -1, 1) );
    World::MakeObject("background")->setScale(vec3(100, 100, 100));

    Systems::GetGui().loadLayout("Pseudoform.layout");

    World::Application().Start();

    return 0;
}
