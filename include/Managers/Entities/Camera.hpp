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
		string mCamTypeStr;

		float mMove;
		float mRotate;

		boost::signals2::connection mEMouseMoved;
		boost::signals2::connection mEUpdated;

    public:
        enum CameraType
        {
        	FREE,
        	ATTACHED,
        	FIRST_PERSON,
        	DONT_USE	// If we don't want predefined stuff
        } mCameraType;

        Camera(const string &entityName);
        ~Camera();

        Ogre::Camera *handle();
        Ogre::SceneNode *getPitchNode();

        Camera *loadFromFile(const string &filePath);

        Camera *setCameraType(CameraType type);
        Camera *setActive(bool state);

        Camera *setMoveStep(float step);
        Camera *setRotateStep(float step);
        float getMoveStep();
        float getRotateStep();

		void onInited();
		void onUpdated();
		void onKeyPressed(const OIS::KeyEvent &e);
		void onMouseMoved(const OIS::MouseEvent &e);

        Camera *dump();
        string type();
        void update(float elapsed);
};

#endif	/* CAMERA_HPP */

