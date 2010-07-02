#ifndef OBJECT_HPP
#define	OBJECT_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include <Ogre.h>

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Object : public Entity
{
    public:
        Object(const string entityName, const string &entityMesh = "", const string &res = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        void setImage(const string& imgPath);
        void _loadData();
        void update(float elapsed);
};

#endif	/* OBJECT_HPP */

