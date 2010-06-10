#include "Engine.hpp"

using namespace std;

int main() {
    string logName = "pong.log";

    string test = Engine::Config().getValue<string>("ogre.renderLib");
    if (Engine::Application().Init())
    {
        //Engine::Log().write("Starting game initializating...", logName);
        Engine::Application().Start();
        Engine::Application().Shutdown();
    }
    return 0;
}