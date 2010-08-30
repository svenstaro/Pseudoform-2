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
        Light(const string &entityName);
        ~Light();

        Ogre::Light *handle();
        Light *loadFromFile(const string &filePath);

        Light *setDiffuse(const colour &diffuse);
        Light *setSpecular(const colour &specular);
        Light *setRadius(float value);
        Light *setPower(float value);

        colour getDiffuse();
        colour getSpecular();
        float getRadius();
        float getPower();

        Light *dump();
        string type();
        void update(float elapsed);
};

#endif /* LIGHT_HPP_ */
