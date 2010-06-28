#include "Managers/Entities/Entity.hpp"

Entity::~Entity() { }

// =============================================================================
// Getters
const string Entity::getName() const
{ 
    return mEntityName;
}
const string Entity::getMeshName() const
{ 
    return mEntityMesh;
}
bool Entity::isDrawable() const
{ 
    return mDrawable;
}

Ogre::SceneNode &Entity::getNode() const
{ 
    return *mNode;
}
Ogre::Entity &Entity::getEntity() const
{
    return *mEntity;
}

const vec3 &Entity::getPosition() const
{ 
    return mNode->getPosition();
}
const quat &Entity::getOrientation() const
{ 
    return mNode->getOrientation();
}
const vec3 &Entity::getScale() const
{ 
    return mNode->getScale();
}

// =============================================================================
// Setters
void Entity::setName(const string &entityName)
{ 
    mEntityName = entityName;
}
void Entity::setMeshName(const string &meshPath)
{ 
    mEntityMesh = meshPath;
}
void Entity::setDrawable(bool state)
{ 
    mDrawable = state;
}

void Entity::setMaterial(const string &matName, const string &group)
{ 
    mEntity->setMaterialName(matName, group);
}
void Entity::setPosition(const vec3 pos)
{
    mNode->setPosition(pos);
}
void Entity::setRotation(const quat rot)
{ 
    mNode->setOrientation(rot);
}
void Entity::setScale(const vec3 scale)
{ 
    mNode->setScale(scale);
}