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

class EntityManager : public singleton<EntityManager>
{
    protected:
        boost::ptr_map<const string, Entity> mEntityList;

    public:
        // Templated interface
        bool DeleteEntity(const string &entityName);

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
