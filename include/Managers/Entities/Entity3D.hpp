#ifndef ENTITY3D_HPP
#define	ENTITY3D_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

using namespace std;

class Entity3D : public Entity
{
    public:
        ~Entity3D() { }
        Entity3D(const string entityName, const string &entityMesh = "")
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

        void _loadData() { }
};

#endif	/* ENTITY3D_HPP */

