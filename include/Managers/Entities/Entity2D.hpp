#ifndef ENTITY2D_HPP
#define	ENTITY2D_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include <OgreMeshManager.h>
#include <OgreMaterial.h>

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Entity2D : public Entity
{
    protected:
        Ogre::Plane *mPlane;
        Ogre::MaterialPtr mTextureMat;
        string mResGroup;

    public:
        Entity2D(const string entityName, const string &entityMesh = "",
                const string &resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                real width = 0, real height = 0);

        void setImage(const string &imgPath);
        Ogre::MaterialPtr &getMaterial();

        void _loadData();
};

#endif	/* ENTITY2D_HPP */

