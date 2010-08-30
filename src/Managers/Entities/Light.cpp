#include "Managers/Entities/Light.hpp"

Light::Light(const string &entityName):Entity()
{
	LOG(FORMAT("Loading new entity `%1%` of type `%2%`", entityName % type()));

	mEntityName = entityName;

	// TODO: Load not Error mesh in Light class (get some other mesh type)
	mLight = graphicSystem.getSceneMgr()->createLight("Light:" + entityName);
	mDebugEntity = graphicSystem.getSceneMgr()->createEntity("LightMesh:" + entityName, CONFIG("resorces.LightMesh", string, "Engine/Light.mesh"));
	mNode = graphicSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode("Node:" + entityName);

	showDebug(true);
    mNode->attachObject(mLight);
}

Light::~Light()
{
    if(mLight)
        graphicSystem.getSceneMgr()->destroyLight(mLight);
}

Light *Light::loadFromFile(const string &filePath)
{
	ptree tree_handle = defaultLoader(filePath);

	string argName;
	vector<string> parseStorage;
	float storage[4];
	memset(storage, 0, sizeof(float)*4);

	argName = tree_handle.get<string>("type_settings.diffuse", "1, 1, 1, 1");
	if (parseArguments("diffuse", argName, storage, parseStorage))
		setDiffuse(colour(storage[0], storage[1], storage[2], storage[3]));

	argName = tree_handle.get<string>("type_settings.specular", "0, 0, 0, 1");
	if (parseArguments("specular", argName, storage, parseStorage))
		setSpecular(colour(storage[0], storage[1], storage[2], storage[3]));

    setRadius(tree_handle.get<float>("type_settings.radius", 100000));
	setPower(tree_handle.get<float>("type_settings.power", 1));

	showDebug(false);

	return this;
}

Light *Light::dump()
{
	defaultDump();
	LOG_NOFORMAT("\t ---Type settings---\n");
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Diffuse" % mLight->getDiffuseColour()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Specular" % mLight->getSpecularColour()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Radius" % mLight->getAttenuationRange()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Power" % mLight->getPowerScale()));
	switch(mLight->getType())
	{
	    case Ogre::Light::LT_DIRECTIONAL:
            LOG_NOFORMAT("\tType: DIRECTIONAL\n");
            break;
        case Ogre::Light::LT_SPOTLIGHT:
            LOG_NOFORMAT("\tType: SPOTLIGHT\n");
            break;
        case Ogre::Light::LT_POINT:
            LOG_NOFORMAT("\tType: POINT\n");
            break;
	}

	return this;
}

Ogre::Light *Light::handle() { return mLight; }

// Setters
Light *Light::setDiffuse(const colour &diffuse) { mLight->setDiffuseColour(diffuse); return this; }
Light *Light::setSpecular(const colour &specular) { mLight->setSpecularColour(specular); return this; }
Light *Light::setRadius(float value) { mLight->setAttenuation(value, 1, 0.007, 0); return this; }
Light *Light::setPower(float value) { mLight->setPowerScale(value); return this; }

// Getters
colour Light::getDiffuse() { return mLight->getDiffuseColour(); }
colour Light::getSpecular() { return mLight->getSpecularColour(); }
float Light::getRadius() { return mLight->getAttenuationRange(); }
float Light::getPower() { return mLight->getPowerScale(); }

string Light::type() { return "light"; }
void Light::update(float elapsed) { }
