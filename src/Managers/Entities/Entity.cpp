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
void Entity::setPosition(const vec3 &pos)
{
    mNode->setPosition(pos);
}
void Entity::setRotation(const quat &rot)
{
    mNode->setOrientation(rot);
}
void Entity::setScale(const vec3 &scale)
{
    mNode->setScale(scale);
}

// =============================================================================
// Settings loader
bool Entity::parseArguments(const string &argName, const string &argData, float *outData, vector<string> &storage)
{
	memset(outData, 0, sizeof(float)*3);
	storage.clear();
	unsigned short counter = 0;

	LOG_NOFORMAT(FORMAT("\t\t `%1%` ­— `%2%`\n", argName % argData));

	// The default value should be taken
	if (argData.find("Default") != string::npos) return false;

	boost::split(storage, argData, boost::is_any_of("\t, "));
	BOOST_FOREACH(string element, storage)
	{
		if (element != "")
		{
			outData[counter] = boost::lexical_cast<float>(element);
			counter++;
		}
	}

	return true;
}

ptree Entity::defaultLoader(const string &infoPath)
{
	LOG_NOFORMAT("\tDumping information, parsed from file:\n");

	ptree tree_handle;
	read_info(LOCATION(utilsConst.getMediaPath() + infoPath), tree_handle);

	setDrawable( tree_handle.get<bool>("common_settigns.visible", true) );

	// I don't think we need this
	// setName( tree_handle.get<string>("common_settigns.name", mEntityName) );

	string argName;
	vector<string> parseStorage;
	float storage[3];
	memset(storage, 0, sizeof(float)*3);

	// Position
	argName = tree_handle.get<string>("common_settigns.position", "0, 0, 0");
	if (parseArguments("position", argName, storage, parseStorage))
		setPosition(vec3(storage[0], storage[1], storage[2]));

	// Orientation
	argName = tree_handle.get<string>("common_settigns.orientation", "1, 1, 1");
	if (parseArguments("orientation", argName, storage, parseStorage))
		setRotation(quat(deg(storage[0]), Ogre::Vector3::UNIT_X) *
                    quat(deg(storage[1]), Ogre::Vector3::UNIT_Y) *
                    quat(deg(storage[2]), Ogre::Vector3::UNIT_Z));

	// Scale
	argName = tree_handle.get<string>("common_settigns.scale", "1, 1, 1");
	if (parseArguments("scale", argName, storage, parseStorage))
		setScale(vec3(storage[0], storage[1], storage[2]));

	return tree_handle;
}
