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
#include "Managers/Entities/Camera.hpp"

using namespace boost::serialization;
using namespace std;

#define entityManager (EntityManager::get_mutable_instance())
#define entityManagerConst (EntityManager::get_const_instance())

// Fast creating of entities
#define MakeObject(entName) entityManager.MakeEntity<Object>(entName)
#define MakeLight(entName) entityManager.MakeEntity<Light>(entName)
#define MakeCamera(entName) entityManager.MakeEntity<Camera>(entName)

// Fast accessing to the entities
#define GetObject(entName) entityManager.GetEntity<Object>(entName)
#define GetLight(entName) entityManager.GetEntity<Light>(entName)
#define GetCamera(entName) entityManager.GetEntity<Camera>(entName)

class EntityManager : public singleton<EntityManager>
{
    protected:
        typedef boost::ptr_map<const string, Entity> TEntityList;
        TEntityList mEntityList;

    public:
        // Templated interface
        bool DeleteEntity(const string &entityName);
        int DeleteAllEntities();

        // Predefined interface for all objects types
        template<typename EntityType>
        EntityType *MakeEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) != 0)
            {
                LOG_META(FORMAT("Can`t make entity with name '%1%' because it already exsists!", entityName));
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
                LOG_META(FORMAT("Can`t get entity '%1%', because it doesn`t exsist!", entityName));
                return NULL;
            }

            return dynamic_cast<EntityType*>(&mEntityList.at(entityName));
        }
};

#endif	/* ENTITYMANAGER_HPP */
