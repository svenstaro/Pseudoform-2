#include "Managers/Entities/Light.hpp"

Light::Light(const string entityName)
{
	_defaultLoader(entityName);	// Loading from info file

	Ogre::SceneManager *sceneMgr = GraphicSystem::get_const_instance().getSceneMgr();

	mLight = sceneMgr->createLight("Light:" + entityName);

	mNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Node:" + entityName);
	mNode->attachObject(mLight);
}

void Light::configure(Ogre::Light::LightTypes lt,
		colour diffuse, colour specular,
		float attenuation, float power)
{
	mLight->setType(lt);
	mLight->setAttenuation(attenuation, 0, 0, 0);
	mLight->setDiffuseColour(diffuse);
	mLight->setSpecularColour(specular);
	mLight->setPowerScale(power);
}

Ogre::Light *Light::lightHandle() { return mLight; }

// Setters
void Light::setDiffuse(const colour &diffuse) { mLight->setDiffuseColour(diffuse); }
void Light::setSpecular(const colour &specular) { mLight->setSpecularColour(specular); }
void Light::setRadius(float value) { mLight->setAttenuation(value, 0, 0, 0); }
void Light::setPower(float value) { mLight->setPowerScale(value); }

// Getters
colour Light::getDiffuse() { return mLight->getDiffuseColour(); }
colour Light::getSpecular() { return mLight->getSpecularColour(); }
float Light::getRadius() { return mLight->getAttenuationRange(); }
float Light::getPower() { return mLight->getPowerScale(); }

string Light::type() { return "light"; }
void Light::_loadData() { }
void Light::update(float elapsed) { }
