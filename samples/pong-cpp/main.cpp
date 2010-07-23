#include "Engine.hpp"

using namespace std;
using namespace Engine;

const float fMove = 350;
const float fRotate = 0.13;
const string sLogName = "pong.log";

void onKeyPressed(sf::Event::KeyEvent &eventData)
{
    using namespace sf;

    vec3 translation = vec3::ZERO;

    if (eventData.Code == Key::W)
        translation.z -= fMove;
    else if (eventData.Code == Key::S)
        translation.z += fMove;
    else if (eventData.Code == Key::A)
        translation.x -= fMove;
    else if (eventData.Code == Key::D)
        translation.x += fMove;
    else if (eventData.Code == Key::Q)
    	translation.y += fMove;
    else if (eventData.Code == Key::E)
    	translation -= fMove;

    Ogre::SceneNode *camNode = World::GetCamera("MainCamera")->getNode();
    camNode->translate(camNode->getOrientation() * translation * World::GetElapsed());
}

void onMouseMoved(sf::Event::MouseMoveEvent &eventData)
{
	int offsetX = eventData.X - World::GetWidth()/2;
	int offsetY = eventData.Y - World::GetHeight()/2;

	Ogre::SceneNode *camNode = World::GetCamera("MainCamera")->getNode();

    camNode->yaw(deg(fRotate * -offsetX));
    camNode->getChild(0)->pitch(deg(fRotate * -offsetY));
}

void onInited()
{
	using namespace World;
	LOG(FORMAT("The size of the screen is (%1%; %2%)", GetWidth() % GetHeight()));

	Systems::GetInput().Window().SetCursorPosition(GetWidth()/2, GetHeight()/2);
	Systems::GetInput().Window().ShowMouseCursor(false);
}

void onUpdated()
{
	// We need in this until we will not have script system
	using namespace World;

	Systems::GetInput().Window().SetCursorPosition(GetWidth()/2, GetHeight()/2);
}

int main() {
    CONNECT_SINGLE(Engine::Events::KeyEvent, "KeyPressed", &onKeyPressed);
    CONNECT_SINGLE(Engine::Events::MouseMoveEvent, "MouseMoved", &onMouseMoved);
    CONNECT_SINGLE(Engine::Events::GlobalUpdateEvent, "Updated", &onUpdated);
    CONNECT_SINGLE(Engine::Events::GlobalInitEvent, "Inited", &onInited);

    Managers::GetLog().write("Adding new source location...", sLogName);
    Managers::GetResource().addResourceLocation("pong-media", true);

    World::MakeCamera("MainCamera", true);
    World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL)->lightHandle()->setDirection( vec3(0, -1, 1) );
    World::MakeObject("background")->setScale(vec3(100, 100, 100));

    World::Application().Start();

    return 0;
}
