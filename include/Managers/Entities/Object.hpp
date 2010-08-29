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
        Object(const string &entityName, const string &resGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        void setImage(const string& imgPath);

        // Inherited from Entity class
        void loadFromFile(const string &filePath);
        string type();
        void update(float elapsed);
};

#endif	/* OBJECT_HPP */

