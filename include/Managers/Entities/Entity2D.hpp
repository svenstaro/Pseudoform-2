#ifndef ENTITY2D_HPP
#define	ENTITY2D_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include <OgreMeshManager.h>
#include <OgreMaterial.h>

using namespace std;

class Entity2D : public Entity
{
    protected:
        Ogre::Plane *mPlane;
        Ogre::MaterialPtr mTextureMat;
        string mResGroup;

    public:
        ~Entity2D() { }
        Entity2D(const string entityName, const string &entityMesh = "",
                const string &resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                real width = 0, real height = 0)
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

        void setImage(const string &imgPath)
        {
            mTextureMat = Ogre::MaterialManager::getSingleton().create("Material:" + mEntityName, mResGroup);
            mTextureMat->getTechnique(0)->getPass(0)->createTextureUnitState(imgPath);

            GraphicSystem::get_mutable_instance().getSceneMgr()->getEntity(mEntityName)->setMaterial(mTextureMat);
        }

        Ogre::MaterialPtr &getMaterial() { return mTextureMat; }

        void _loadData() { }
};

#endif	/* ENTITY2D_HPP */

