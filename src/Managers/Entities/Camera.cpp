#include "Managers/Entities/Camera.hpp"

Camera::Camera(const string cameraName)
{
	Ogre::SceneManager *sceneMgr = GraphicSystem::get_const_instance().getSceneMgr();

    mEntityName = cameraName;
    mCamera = sceneMgr->createCamera(cameraName);

    mMove = 250;
    mRotate = 0.13;

    mNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Node:Camera_" + cameraName);
    mPitchNode = mNode->createChildSceneNode("Node:CameraPitch_" + cameraName);
    mPitchNode->attachObject(mCamera);
}

void Camera::configure(const float nearClip, const float farClip, bool autoAR, const float FOV,
		vec3 pos, vec3 lookAt)
{
    mCamera->setNearClipDistance(nearClip);
    mCamera->setFarClipDistance(farClip);
    mCamera->setAutoAspectRatio(autoAR);
    mCamera->setFOVy(deg(FOV));
}

Ogre::Camera *Camera::cameraHandle() { return mCamera; }
Ogre::SceneNode *Camera::getPitchNode() { return mPitchNode; }

float Camera::getMoveStep() { return mMove; }
float Camera::getRotateStep() { return mRotate; }
void Camera::setMoveStep(float step) { mMove = step; }
void Camera::setRotateStep(float step) { mRotate = step; }

string Camera::type() { return "camera"; }
void Camera::_loadData() { }
void Camera::update(float elapsed) { }

#define WIDTH GraphicSystem::get_mutable_instance().getWindow()->getWidth()
#define HEIGHT GraphicSystem::get_mutable_instance().getWindow()->getHeight()

void Camera::setCameraType(CameraType type)
{
	mCameraType = type;

	if (type != Camera::DONT_USE)
	{
		CONNECT(Engine::Events::KeyEvent, "KeyPressed", &Camera::onKeyPressed)
	    CONNECT(Engine::Events::MouseMoveEvent, "MouseMoved", &Camera::onMouseMoved);
	    CONNECT0(Engine::Events::GlobalUpdateEvent, "Updated", &Camera::onUpdated);
	    CONNECT0(Engine::Events::GlobalInitEvent, "Inited", &Camera::onInited);
	}
}

void Camera::onInited()
{
	switch(mCameraType)
	{
		case Camera::FREE:

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
		case Camera::DONT_USE: break;
	}
}

void Camera::onUpdated()
{
	switch(mCameraType)
	{
		case Camera::FREE:

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
		case Camera::DONT_USE: break;
	}
}

void Camera::onKeyPressed(const OIS::KeyEvent &e)
{
	using namespace sf;
	vec3 translation = vec3::ZERO;

	switch(mCameraType)
	{
		case Camera::FREE:
			if (e.key == OIS::KC_W)
			    translation.z -= mMove;
			else if (e.key == OIS::KC_S)
			    translation.z += mMove;
			else if (e.key == OIS::KC_A)
			    translation.x -= mMove;
			else if (e.key == OIS::KC_D)
			    translation.x += mMove;
			else if (e.key == OIS::KC_Q)
				translation.y += mMove;
			else if (e.key == OIS::KC_E)
				translation -= mMove;

			mNode->translate(mNode->getOrientation() * translation * GameApplication::get_const_instance().getElapsed());

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
		case Camera::DONT_USE: break;
	}
}

void Camera::onMouseMoved(const OIS::MouseEvent &e)
{
	switch(mCameraType)
	{
		case Camera::FREE:
			mNode->yaw(deg(-mRotate * e.state.X.rel), Ogre::Node::TS_WORLD);
			mPitchNode->pitch(deg(-mRotate * e.state.Y.rel), Ogre::Node::TS_LOCAL);

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
		case Camera::DONT_USE: break;
	}
}
