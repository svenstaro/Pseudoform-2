#include "Engine.hpp"

using namespace std;
using namespace Engine;

const float fMove = 250;
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

int main() {
    Managers::GetLog().write("Adding new source location...", sLogName);
    Managers::GetResource().addResourceLocation("pong-media", true);

    Ogre::Camera *ogCamera = Systems::GetGraphic().getCamera();
    ogCamera->setPosition(vec3(0, 1000, 500));
    ogCamera->lookAt(vec3(0, 0, 0));

    Ogre::Light *ogLight = Systems::GetGraphic().getSceneMgr()->createLight( "Light3" );
    ogLight->setType( Ogre::Light::LT_DIRECTIONAL );
    ogLight->setDiffuseColour( colour( .25, .25, 0 ) );
    ogLight->setSpecularColour( colour( .25, .25, 0 ) );
    ogLight->setDirection( vec3( 0, -1, 1 ) );

    World::MakeObject("background");

    Ogre::Plane plane( vec3::UNIT_Y, 0 );
    Ogre::MeshManager::getSingleton().createPlane("ground",
    	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
    	1500,1500,20,20,true,1,5,5,vec3::UNIT_Z);

    Ogre::Entity *ent = Systems::GetGraphic().getSceneMgr()->createEntity( "GroundEntity", "ground" );
    Systems::GetGraphic().getSceneMgr()->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    CONNECT_SINGLE(Engine::Events::KeyEvent, "KeyPressed", &onKeyPressed);

    World::Application().Start();

    return 0;
}
