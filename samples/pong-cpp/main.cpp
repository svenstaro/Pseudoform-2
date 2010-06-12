#include "Engine.hpp"

using namespace std;
using namespace Engine;

int main() {
    string logName = "pong.log";

    Managers::Log().write("Resolving render library type from config...", logName);
    string test = Managers::Config().getValue<string>("ogre.renderLib");

    Managers::Log().write("Adding new source location...", logName);
    Managers::Resources().addResourceLocationRecursive("pong-media/");

    Engine::Application().Start();
    
    return 0;
}