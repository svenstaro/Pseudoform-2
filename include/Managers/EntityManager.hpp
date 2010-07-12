#ifndef ENTITYMANAGER_HPP
#define	ENTITYMANAGER_HPP

#include "boost/ptr_container/ptr_map.hpp"
#include "boost/foreach.hpp"
#include "boost/noncopyable.hpp"
#include <boost/serialization/singleton.hpp>

#include "Core/Types.hpp"
#include "Core/Utils.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/Entities/Entity.hpp"
#include "Managers/Entities/Object.hpp"
#include "Managers/Entities/Light.hpp"

using namespace boost::serialization;
using namespace std;

class EntityManager : public singleton<EntityManager>
{
    protected:
        boost::ptr_map<const string, Entity> mEntityList;

    public:
        // Object entity
        Object *MakeObject(const string &entityName);
        Object *GetObject(const string &entityName);

        // Light entity
        Light *MakeLight(const string &entityName);
        Light *GetLight(const string &entityName);

        // Templated interface
        bool DeleteEntity(const string &entityName);

        // Predefined interface for all objects types
        template<typename EntityType>
        EntityType *MakeEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) != 0)
            {
                LOG(FORMAT("Can`t make entity with name '%1%' because it's already exsists!", entityName));
                return NULL;
            }

            mEntityList.insert(entityName, new EntityType(entityName));
            return dynamic_cast<EntityType*>(&mEntityList.at(entityName));
        }
        
        template<typename EntityType>
        EntityType *GetEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) == 0)
            {
                LOG(FORMAT("Can`t get entity '%1%', because it doesn`t exsist!", entityName));
                return NULL;
            }

            return dynamic_cast<EntityType*>(&mEntityList.at(entityName));
        }
};

#endif	/* ENTITYMANAGER_HPP */
