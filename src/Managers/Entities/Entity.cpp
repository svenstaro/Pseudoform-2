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

Ogre::SceneNode *Entity::getNode() const
{ 
    return mNode;
}
Ogre::Entity *Entity::getEntity() const
{
    return mEntity;
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

// =============================================================================
// Settings loader
float *Entity::parseArguments(const string &argName)
{
	std::vector<std::string> storage;
	float *data = new float[3];
	unsigned int counter = 0;

	boost::split(storage, argName, boost::is_any_of("\t, "));

	BOOST_FOREACH(string element, storage)
	{
		if (element != "")
		{
			data[counter] = boost::lexical_cast<float>(element);
			counter++;
		}
	}
	return data;
}

void Entity::_defaultLoader(string entityName)
{
	mEntityName = entityName;

	string mediaPath = CONFIG("resources.MediaFolder", string, "Media");
	string entityData = mediaPath + "Entities/" + mEntityName;

	if (!boost::filesystem::exists(entityData))
	{
		LOG_META(FORMAT("There isn't media-folder for the entity with `%1%` name", entityName));
		return;
	}

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(entityData, "FileSystem", "General", true);

	ptree tree_handle;
	read_info(mediaPath + "Entities/" +  mEntityName + "/init.info", tree_handle);

	setDrawable( tree_handle.get<bool>("common_settigns.visible", true) );
	setName( tree_handle.get<string>("common_settigns.name", mEntityName) );

	string position = tree_handle.get<string>("common_settigns.position", "0, 0, 0");
	string orientation = tree_handle.get<string>("common_settigns.orientation", "0, 0, 0");
	string scale = tree_handle.get<string>("common_settigns.scale", "1, 1, 1");

	float *storage = parseArguments(position);
	this->setPosition(vec3(storage[0], storage[1], storage[2]));

	storage = parseArguments(orientation);
	this->setRotation(quat(storage[0], storage[1], storage[2]));

	storage = parseArguments(scale);
	this->setScale(vec3(storage[0], storage[1], storage[2]));

	delete []storage;
}
