#include "Managers/Entities/Entity2D.hpp"

Entity2D::Entity2D(const string entityName, const string& entityMesh, const string& resourceGroup, real width, real height)
{
    mEntityName = entityName;
    mResGroup = resourceGroup;

    string entMesh = "Mesh:" + entityName;
    if (entityMesh != "") entMesh = entityMesh;

    Ogre::MeshManager::getSingleton().createPlane(entMesh, resourceGroup, *mPlane, width, height);

    // Attaching new mesh (with name entMesh) to the entity
    GraphicSystem::get_mutable_instance().getSceneMgr()->createEntity(entityName, entMesh);
    GraphicSystem::get_mutable_instance().getSceneMgr()->getRootSceneNode()->createChildSceneNode("Node:" + mEntityName);
}

void Entity2D::setImage(const string& imgPath)
{
    mTextureMat = Ogre::MaterialManager::getSingleton().create("Material:" + mEntityName, mResGroup);
    mTextureMat->getTechnique(0)->getPass(0)->createTextureUnitState(imgPath);

    GraphicSystem::get_mutable_instance().getSceneMgr()->getEntity(mEntityName)->setMaterial(mTextureMat);
}

Ogre::MaterialPtr &Entity2D::getMaterial()
{
    return mTextureMat;
}

void Entity2D::_loadData() { }