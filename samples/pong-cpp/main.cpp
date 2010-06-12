#include "Engine.hpp"

using namespace std;

int main() {
    string logName = "pong.log";

    Engine::Log().write("Resolving render library type from config...", logName);
    string test = Engine::Config().getValue<string>("ogre.renderLib");

    Engine::Log().write("Adding new source location...", logName);
    Engine::Resources().addResourceLocationRecursive("pong-media/");

    Engine::Application().Start();
    
    return 0;
}