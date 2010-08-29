#include "Managers/Entities/Light.hpp"

Light::Light(const string &entityName)
{
	LOG(FORMAT("Loading new entity `%1%` of type `%2%`", entityName % type()));

	mEntityName = entityName;

	// TODO: Load not Error mesh in Light class (get some other mesh type)
	mLight = graphicSystem.getSceneMgr()->createLight("Light:" + entityName);
	mEntity = graphicSystem.getSceneMgr()->createEntity("Error:" + entityName, CONFIG("resorces.ErrorMesh", string, "Engine/Error.mesh"));
	mNode = graphicSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode("Node:" + entityName);

	mNode->attachObject(mEntity);
}

void Light::loadFromFile(const string &filePath)
{
	ptree tree_handle = defaultLoader(filePath);

	string argName;
	vector<string> parseStorage;
	float storage[3];
	memset(storage, 0, sizeof(float)*3);

	argName = tree_handle.get<string>("type_settigns.diffuse", "1, 1, 1");
	if (parseArguments("diffuse", argName, storage, parseStorage))
		setDiffuse(colour(storage[0], storage[1], storage[2]));

	argName = tree_handle.get<string>("type_settigns.specular", "1, 1, 1");
	if (parseArguments("specular", argName, storage, parseStorage))
		setSpecular(colour(storage[0], storage[1], storage[2]));

	setRadius(tree_handle.get<float>("type_settings.radius", 10));
	setPower(tree_handle.get<float>("type_settings.power", 1));

	mNode->detachObject(mEntity);
	mNode->attachObject(mLight);
}

void Light::dump()
{
	defaultDump();
	// TODO: typeDump light
}

Ogre::Light *Light::handle() { return mLight; }

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
void Light::update(float elapsed) { }
