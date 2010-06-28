#ifndef ENTITIES_HPP
#define	ENTITIES_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

using namespace std;

class Entity : private boost::noncopyable
{
    protected:
        string mEntityName;
        string mEntityMesh;
        bool mDrawable;

        Ogre::Entity *mEntity;
        Ogre::SceneNode *mNode;

    public:
        virtual ~Entity();
        virtual void _loadData() = 0;  // From info-file

        // =====================================================================
        // Doings
        template<typename EventType>
        void AddBehavior(const string &eventName, const typename EventType::SignatureSlotType &eventSlot)
        {
            CONNECT(EventType, eventName, eventSlot);
        }

        template<typename EventType>
        void RemoveBehavior()
        {
            // TODO: Implement me!
        }

        // =====================================================================
        // Getters
        const string getName() const { return mEntityName; }
        const string getMeshName() const { return mEntityMesh; }
        bool isDrawable() const { return mDrawable; }

        Ogre::SceneNode &getNode() const { return *mNode; }
        Ogre::Entity &getEntity() const { return *mEntity; }
        
        const vec3 &getPosition() const { return mNode->getPosition(); }
        const quat &getOrientation() const { return mNode->getOrientation(); }
        const vec3 &getScale() const { return mNode->getScale(); }

        // =====================================================================
        // Setters
        void setName(const string &entityName) { mEntityName = entityName; }
        void setMeshName(const string &meshPath) { mEntityMesh = meshPath; }
        void setDrawable(bool state) { mDrawable = state; }
        
        void setMaterial(const string &matName, const string &group = "") { mEntity->setMaterialName(matName, group); }
        void setPosition(const vec3 pos = vec3()) { mNode->setPosition(pos); }
        void setRotation(const quat rot = quat()) { mNode->setOrientation(rot); }
        void setScale(const vec3 scale = vec3()) { mNode->setScale(scale); }
};


#endif	/* ENTITIES_HPP */