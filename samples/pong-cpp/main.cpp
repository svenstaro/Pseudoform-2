#include "Engine.hpp"
#include "Core/GameApplication.hpp"

int main() {
    Engine EngineHandle;
    GameApplication &Application = EngineHandle.Application();
    
    if (Application.Init())
    {
        Application.Start();
        Application.Shutdown();
    }
    return 0;
}