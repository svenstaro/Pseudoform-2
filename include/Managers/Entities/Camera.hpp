#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Camera : public Entity
{
	protected:
		Ogre::Camera *mCamera;
		Ogre::SceneNode *mPitchNode;

    public:
        Camera(const string cameraName);
        void configure(const float nearClip = 1, const float farClip = 1000, bool autoAR = true, const float FOV = 90,
        		vec3 pos = vec3(0, 1000, 1000), vec3 lookAt = vec3(0, 0, 0));
        Ogre::Camera *cameraHandle();
        Ogre::SceneNode *getPitchNode();

        void _loadData();
        void update(float elapsed);
};

#endif	/* CAMERA_HPP */

