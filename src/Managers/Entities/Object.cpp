#include "Managers/Entities/Object.hpp"

#include <OgreMeshManager.h>
#include <OgreMaterial.h>

Object::Object(const string entityName, const string &entityMesh, const string &res)
{
    mEntityName = entityName;

    string entMesh = entityName + ".mesh";
    if (entityMesh != "") entMesh = entityMesh;

    // Attaching new mesh (with name entMesh) to the entity
    if (Ogre::ResourceGroupManager::getSingletonPtr()->resourceExists(res, entMesh))
    {
        Ogre::ResourceGroupManager::getSingleton().declareResource(entMesh, "Mesh", res);
        Ogre::SceneManager *sceneMgr = GraphicSystem::get_mutable_instance().getSceneMgr();

        mEntity = sceneMgr->createEntity(entityName, entMesh);
        mNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Node:" + mEntityName);
        mNode->attachObject(mEntity);
    }
    else
    {
        LOG(FORMAT("Mesh with name '%1%' doesn`t exist in resources list!", entMesh));
    }
}

void Object::setImage(const string& imgPath)
{
    Ogre::MaterialPtr textureMat = Ogre::MaterialManager::getSingleton().create("Material:" + mEntityName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    textureMat->getTechnique(0)->getPass(0)->createTextureUnitState(imgPath);

    GraphicSystem::get_mutable_instance().getSceneMgr()->getEntity(mEntityName)->setMaterial(textureMat);
}

string Object::type() { return "object"; }
void Object::_loadData() { }
void Object::update(float elapsed) { }
