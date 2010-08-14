#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "Managers/EventManager.hpp"
#include "Managers/ResourceManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Light : public Entity
{
	protected:
		Ogre::Light *mLight;

    public:
        Light(const string entityName);

        void configure(Ogre::Light::LightTypes lt = Ogre::Light::LT_POINT,
        		colour diffuse = colour(1, 1, 1), colour specular = colour(1, 1, 1),
        		float attenuation = 10, float power = 1);
        Ogre::Light *lightHandle();

        void setDiffuse(const colour &diffuse);
        void setSpecular(const colour &specular);
        void setRadius(float value);
        void setPower(float value);

        colour getDiffuse();
        colour getSpecular();
        float getRadius();
        float getPower();

        string type();
        void _loadData();
        void update(float elapsed);
};

#endif /* LIGHT_HPP_ */
