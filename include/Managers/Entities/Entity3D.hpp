#ifndef ENTITY3D_HPP
#define	ENTITY3D_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Entity3D : public Entity
{
    public:
        Entity3D(const string entityName, const string &entityMesh = "");
        void _loadData();
};

#endif	/* ENTITY3D_HPP */

