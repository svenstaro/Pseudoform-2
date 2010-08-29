#include "Managers/Entities/Object.hpp"

#include <OgreMeshManager.h>
#include <OgreMaterial.h>

Object::Object(const string &entityName, const string &resGroup)
{
	LOG(FORMAT("Loading new entity `%1%` of type `%2%`", entityName % type()));
	mEntityName = entityName;
	mResGroup = resGroup;

    mEntity = graphicSystem.getSceneMgr()->createEntity("Error:" + entityName, CONFIG("resorces.ErrorMesh", string, "Engine/Error.mesh"));
    mNode = graphicSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode("Node:" + entityName);

    mNode->attachObject(mEntity);
}

void Object::loadFromFile(const string &filePath)
{
	ptree tree_handle = defaultLoader(filePath);

	// Detaching default node with real one
	mNode->detachObject(mEntity);

	// Get the path for the real mesh
	string meshLocation = tree_handle.get<string>("type_settings.mesh", CONFIG("resorces.ErrorMesh", string, "Engine/Error.mesh"));
	// Declare it in need resource group
	Ogre::ResourceGroupManager::getSingleton().declareResource(meshLocation, "Mesh", mResGroup);

	mEntityMesh = meshLocation;
	mEntity = graphicSystem.getSceneMgr()->createEntity(mEntityName, mEntityMesh);

	mNode->attachObject(mEntity);
}

void Object::setImage(const string& imgPath)
{
    Ogre::MaterialPtr textureMat = Ogre::MaterialManager::getSingleton().create("Material:" + mEntityName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    textureMat->getTechnique(0)->getPass(0)->createTextureUnitState(imgPath);

    graphicSystem.getSceneMgr()->getEntity(mEntityName)->setMaterial(textureMat);
}

string Object::type() { return "object"; }
void Object::update(float elapsed) { }
