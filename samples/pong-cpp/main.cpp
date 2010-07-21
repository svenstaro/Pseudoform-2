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

    Ogre::SceneNode *camNode = Systems::GetGraphic().getSceneMgr()->getSceneNode("Node:Camera");
    camNode->translate(camNode->getOrientation() * translation * World::GetElapsed());
}

void onMouseMoved(sf::Event::MouseMoveEvent &eventData)
{
    Ogre::SceneNode *camNode = Systems::GetGraphic().getSceneMgr()->getSceneNode("Node:Camera");

    camNode->yaw(deg(fRotate * -eventData.X * World::GetElapsed()), Ogre::Node::TS_WORLD);
    camNode->pitch(deg(fRotate * -eventData.Y * World::GetElapsed()), Ogre::Node::TS_LOCAL);
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

	int x = Systems::GetInput().Handle().GetMouseX();
	int y = Systems::GetInput().Handle().GetMouseY();
	cout << "Mouse: (" << x << ";" << y << ")";
}

int main() {
    CONNECT_SINGLE(Engine::Events::KeyEvent, "KeyPressed", &onKeyPressed);
    CONNECT_SINGLE(Engine::Events::MouseMoveEvent, "MouseMoved", &onMouseMoved);
    CONNECT_SINGLE(Engine::Events::GlobalUpdateEvent, "Updated", &onUpdated);
    CONNECT_SINGLE(Engine::Events::GlobalInitEvent, "Inited", &onInited);

    Managers::GetLog().write("Adding new source location...", sLogName);
    Managers::GetResource().addResourceLocation("pong-media", true);

    Ogre::Camera *ogCamera = Systems::GetGraphic().getCamera();
    ogCamera->setPosition(vec3(0, 1000, 500));
    ogCamera->lookAt(vec3(0, 0, 0));

    World::MakeLight("MainLight", Ogre::Light::LT_DIRECTIONAL, colour(.25, .25, 0), colour(.25, .25, 0));
    World::GetLight("MainLight")->lightHandle()->setDirection( vec3(0, -1, 1) );

    World::MakeObject("background");

    Ogre::Plane plane( vec3::UNIT_Y, 0 );
    Ogre::MeshManager::getSingleton().createPlane("ground",
    	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
    	1500,1500,20,20,true,1,5,5,vec3::UNIT_Z);

    Ogre::Entity *ent = Systems::GetGraphic().getSceneMgr()->createEntity( "GroundEntity", "ground" );
    Systems::GetGraphic().getSceneMgr()->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    World::Application().Start();

    return 0;
}
