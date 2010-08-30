#include "Managers/Entities/Entity.hpp"

Entity::~Entity()
{
    deleteOgre();
}

void Entity::deleteOgre()
{
    if(mNode)
        graphicSystem.getSceneMgr()->getRootSceneNode()->removeAndDestroyChild(mNode->getName());
    mNode = NULL;
    if(mEntity)
        graphicSystem.getSceneMgr()->destroyEntity(mEntity);
    mEntity = NULL;
    if(mDebugEntity)
        graphicSystem.getSceneMgr()->destroyEntity(mDebugEntity);
    mDebugEntity = NULL;
}

// =============================================================================
// Getters
const string Entity::getName() const
{
    return mEntityName;
}

const string Entity::getResGroup() const
{
	return mResGroup;
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
Entity *Entity::setName(const string &entityName)
{
    mEntityName = entityName;
    return this;
}
Entity *Entity::setMeshName(const string &meshPath)
{
    mEntityMesh = meshPath;
    return this;
}
Entity *Entity::setDrawable(bool state)
{
    mDrawable = state;
    return this;
}

Entity *Entity::setMaterial(const string &matName, const string &group)
{
    mEntity->setMaterialName(matName, group);
    return this;
}
Entity *Entity::setPosition(const vec3 &pos)
{
    mNode->setPosition(pos);
    return this;
}
Entity *Entity::setRotation(const quat &rot)
{
    mNode->setOrientation(rot);
    return this;
}
Entity *Entity::setScale(const vec3 &scale)
{
    mNode->setScale(scale);
    return this;
}

Entity *Entity::showDebug(const bool show)
{
    if(!mDebugEntity) return this;
    if(show)
        mNode->attachObject(mDebugEntity);
    else
    	mNode->detachObject(mDebugEntity);
    return this;
}

// =============================================================================
// Settings loader
bool Entity::parseArguments(const string &argName, const string &argData, float *outData, vector<string> &storage)
{
	memset(outData, 0, sizeof(float)*3);
	storage.clear();
	unsigned short counter = 0;

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
    if (!boost::filesystem::exists(utils.getMediaPath() + infoPath))
    {
    	LOG_META(FORMAT("The given location: %1% is invalid!", infoPath));
    	return ptree();
    }

	ptree tree_handle;
	read_info(LOCATION(utilsConst.getMediaPath() + infoPath), tree_handle);

	setDrawable( tree_handle.get<bool>("common_settigns.visible", true) );

	string argName;
	vector<string> parseStorage;
	float storage[4];
	memset(storage, 0, sizeof(float)*4);

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

void Entity::defaultDump()
{
	LOG(FORMAT("Dumping %1% entity settings of type %2%:", mEntityName % type()));
	LOG_NOFORMAT("\t ---Common settings---\n");
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Resource group" % mResGroup));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Entity mesh" % mEntityMesh));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Visible" % isDrawable()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Position" % getPosition()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Orientation" % getOrientation()));
	LOG_NOFORMAT(FORMAT("\t%1%: %2%\n", "Scale" % getScale()));
}
