#include "Engine.hpp"

using namespace std;
using namespace Engine;

int main() {
    string logName = "pong.log";

    Managers::GetLog().write("Resolving render library type from config...", logName);
    string test = Managers::GetConfig().getValue<string>("ogre.renderLib");

    Managers::GetLog().write("Adding new source location...", logName);
    Managers::GetResource().addResourceLocationRecursive("pong-media/");

    Engine::Application().Start();
    
    return 0;
}