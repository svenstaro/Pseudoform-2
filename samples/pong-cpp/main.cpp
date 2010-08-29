#include "Engine.hpp"

using namespace std;
using namespace Engine;

class MenuState : public State
{
    public:
        void init() {
            guiSystem.loadLayout("Pseudoform.layout");

            World::findWidget<MyGUI::StaticImage>("ButtonPlay")->eventMouseButtonClick =
                    MyGUI::newDelegate(this, &MenuState::ButtoPlayClicked);
        }

        void shutdown() {
            guiSystem.unloadLayout("Pseudoform.layout");
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
        	MakeCamera("MainCamera")->loadFromFile("Entities/MainCamera.info")->dump();
        	MakeLight("DirectionalLight")->dump();
        	MakeObject("ErrorObject")->loadFromFile("Entities/ErrorObject.info")->dump();
        	MakeObject("TestLight")->loadFromFile("Entities/Light.info")->dump()->setPosition(vec3(0, 50, 0));

        	//GetCamera("MainCamera")->dump();
        	//GetObject("ErrorObject")->dump();
        }

        string type() { return "GameState"; }
        void update() {}
        void shutdown() {}
};

int main()
{
    stateManager.push(new(MenuState));
    stateManager.push(new(GameState));

    gameApplication.Start();

    return 0;
}
