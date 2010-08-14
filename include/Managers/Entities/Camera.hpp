#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include "Managers/EventManager.hpp"
#include "Core/Systems.hpp"
#include "Core/Types.hpp"

#include "Managers/Entities/Entity.hpp"

using namespace std;

class Camera : public Entity
{
	protected:
		Ogre::Camera *mCamera;
		Ogre::SceneNode *mPitchNode;

		float mMove;
		float mRotate;

    public:
        enum CameraType
        {
        	FREE,
        	ATTACHED,
        	FIRST_PERSON,
        	DONT_USE	// If we don't want predefined stuff
        } mCameraType;

        Camera(const string cameraName);
        void configure(const float nearClip = 1, const float farClip = 1000, bool autoAR = true, const float FOV = 90,
        		vec3 pos = vec3(0, 1000, 1000), vec3 lookAt = vec3(0, 0, 0));
        Ogre::Camera *cameraHandle();
        Ogre::SceneNode *getPitchNode();
        void setCameraType(CameraType type);

        void setMoveStep(float step);
        void setRotateStep(float step);
        float getMoveStep();
        float getRotateStep();

		void onInited();
		void onUpdated();
		void onKeyPressed(sf::Event::KeyEvent &eventData);
		void onMouseMoved(sf::Event::MouseMoveEvent &eventData);

        void _loadData();
        string type();
        void update(float elapsed);
};

#endif	/* CAMERA_HPP */

