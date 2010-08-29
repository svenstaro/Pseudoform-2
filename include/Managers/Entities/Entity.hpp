#ifndef ENTITIES_HPP
#define	ENTITIES_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"
#include "Core/Utils.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using boost::property_tree::ptree;
using namespace std;

class Entity : private boost::noncopyable
{
    protected:
        string mEntityName;
        string mEntityMesh;
        string mResGroup;
        bool mDrawable;

        // TODO: Move entity object to entity class only
        Ogre::Entity *mEntity;
        Ogre::SceneNode *mNode;

        bool parseArguments(const string &argName, const string &argData, float *outData, vector<string> &storage);

        ptree defaultLoader(const string &infoPath); 			 // Predefined loading of common settings
        virtual Entity *loadFromFile(const string &filePath) = 0;   // Loading entity type-derived settings

        void defaultDump(); 			// Dumping default entity settings
        virtual void dump() = 0;	    // Dumping type-related entity settings

    public:
        virtual ~Entity();
        virtual void update(float elapsed) = 0;
        virtual string type() = 0;

        const string getResGroup() const;
        const string getName() const;
        const string getMeshName() const;
        bool isDrawable() const;

        Ogre::SceneNode *getNode() const;
        Ogre::Entity *getEntity() const;

        const vec3 &getPosition() const;
        const quat &getOrientation() const;
        const vec3 &getScale() const;

        void setName(const string &entityName);
        void setMeshName(const string &meshPath);
        void setDrawable(bool state);

        void setMaterial(const string &matName, const string &group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        void setPosition(const vec3 &pos = vec3());
        void setRotation(const quat &rot = quat());
        void setScale(const vec3 &scale = vec3());
};


#endif	/* ENTITIES_HPP */
