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
        virtual void update(float elapsed) = 0;

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

        const string getName() const;
        const string getMeshName() const;
        bool isDrawable() const;

        Ogre::SceneNode &getNode() const;
        Ogre::Entity &getEntity() const;
        
        const vec3 &getPosition() const;
        const quat &getOrientation() const;
        const vec3 &getScale() const;

        void setName(const string &entityName);
        void setMeshName(const string &meshPath);
        void setDrawable(bool state);
        
        void setMaterial(const string &matName, const string &group = "");
        void setPosition(const vec3 pos = vec3());
        void setRotation(const quat rot = quat());
        void setScale(const vec3 scale = vec3());
};


#endif	/* ENTITIES_HPP */
