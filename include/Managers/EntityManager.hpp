#ifndef ENTITYMANAGER_HPP
#define	ENTITYMANAGER_HPP

#include "boost/ptr_container/ptr_map.hpp"
#include "boost/foreach.hpp"
#include <boost/serialization/singleton.hpp>

#include "Core/Types.hpp"
#include "Core/Utils.hpp"
#include "Managers/LogManager.hpp"

using namespace boost::serialization;
using namespace std;

class IEntity
{
    protected:
        string mEntityName;
        vec3 mEntityPos;
        bool mDrawable;
};

class EntityManager : public singleton<EntityManager>
{
    protected:
        boost::ptr_map<string, IEntity*> mEntityList;
        IEntity &loadEntity(const string &entityName) { IEntity *temp; return *temp; /* Here will be loading from info files*/ };

    public:
        bool CreateEntity(const string &entityName, IEntity *copyEntity = NULL)
        {
            if (mEntityList.count(entityName) == 0) 
            {
                LOG(FORMAT("Can`t make entity with name '%1%' because it's already exsists!", entityName));
                return false;
            }

            if (copyEntity != NULL)
                mEntityList[entityName] = copyEntity;
            else
                IEntity newEntity = loadEntity(entityName);
            
            return true;
        }
        
        IEntity *GetEntity(const string &entityName)
        {
            if (mEntityList.count(entityName) == 0)
            {
                LOG(FORMAT("Can`t get entity '%1%', because it doesn`t exsist!", entityName));
                return NULL;
            }
            return mEntityList[entityName];
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

        bool RenameEntity(const string &entityName, const string &newEntityName)
        {
            if (mEntityList.count(entityName) == 0)
            {
                LOG(FORMAT("Can`t rename entity '%1%', because it doesn`t exsist!", entityName));
                return false;
            }

            if (newEntityName == "")
            {
                LOG(FORMAT("New name for entity '%1%' wasn`t declared!", entityName));
                return false;
            }

            mEntityList.erase(entityName);
            return true;
        }
};

#endif	/* ENTITYMANAGER_HPP */

