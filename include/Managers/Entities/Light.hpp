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

        Ogre::Light *handle();
        void loadFromFile(const string &filePath);

        void setDiffuse(const colour &diffuse);
        void setSpecular(const colour &specular);
        void setRadius(float value);
        void setPower(float value);

        colour getDiffuse();
        colour getSpecular();
        float getRadius();
        float getPower();

        void dump();
        string type();
        void update(float elapsed);
};

#endif /* LIGHT_HPP_ */
