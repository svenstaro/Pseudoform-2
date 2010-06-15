#ifndef ENTITYMANAGER_HPP
#define	ENTITYMANAGER_HPP

#include "boost/ptr_container/ptr_map.hpp"
#include "boost/foreach.hpp"
#include "boost/noncopyable.hpp"
#include <boost/serialization/singleton.hpp>

#include "Core/Types.hpp"
#include "Core/Utils.hpp"
#include "Managers/LogManager.hpp"

using namespace boost::serialization;
using namespace std;

class IEntity : private boost::noncopyable
{
    protected:
        string mEntityName;
        vec3 mEntityPos;
        bool mDrawable;
};

class EntityManager : public singleton<EntityManager>
{
    protected:
        boost::ptr_map<const string, IEntity> mEntityList;
        void loadEntity(const string &entityName) { /*Will be soon*/ };

    public:
        bool CreateEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) == 0) 
            {
                LOG(FORMAT("Can`t make entity with name '%1%' because it's already exsists!", entityName));
                return false;
            }

            mEntityList.insert(entityName, new IEntity());
            loadEntity(entityName);
            
            return true;
        }
        
        IEntity *GetEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) == 0)
            {
                LOG(FORMAT("Can`t get entity '%1%', because it doesn`t exsist!", entityName));
                return NULL;
            }
            return &mEntityList[entityName];
        }

        bool DeleteEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) == 0)
            {
                LOG(FORMAT("Can`t delete entity '%1%', because it doesn`t exsist!", entityName));
                return false;
            }

            mEntityList.erase(entityName);
            return true;
        }
};

#endif	/* ENTITYMANAGER_HPP */

