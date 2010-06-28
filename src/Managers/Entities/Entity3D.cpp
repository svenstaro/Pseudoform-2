#include "Managers/Entities/Entity3D.hpp"

Entity3D::Entity3D(const string entityName, const string& entityMesh)
{
    // If we wanna use mesh with name different from entity's name
    if (entityMesh == "")
        mEntityMesh = mEntityName + ".mesh";
    else
        mEntityMesh = entityMesh;

    GraphicSystem::get_mutable_instance().getSceneMgr()->createEntity(mEntityName, mEntityMesh);
    GraphicSystem::get_mutable_instance().getSceneMgr()->getRootSceneNode()->createChildSceneNode("Node:" + mEntityName);

    this->_loadData();
}

void Entity3D::_loadData() { }