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
			InputSystem::get_mutable_instance().Window().SetCursorPosition(WIDTH/2, HEIGHT/2);
			cout << "On inited, cursor position set: " << WIDTH/2 << "; " << HEIGHT/2 << "\n";
			InputSystem::get_mutable_instance().Window().ShowMouseCursor(false);

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
	}
}

void Camera::onUpdated()
{
	switch(mCameraType)
	{
		case Camera::FREE:
			InputSystem::get_mutable_instance().Window().SetCursorPosition(WIDTH/2, HEIGHT/2);

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
	}
}

void Camera::onKeyPressed(sf::Event::KeyEvent &eventData)
{
	using namespace sf;
	vec3 translation = vec3::ZERO;

	switch(mCameraType)
	{
		case Camera::FREE:
			if (eventData.Code == Key::W)
			    translation.z -= mMove;
			else if (eventData.Code == Key::S)
			    translation.z += mMove;
			else if (eventData.Code == Key::A)
			    translation.x -= mMove;
			else if (eventData.Code == Key::D)
			    translation.x += mMove;
			else if (eventData.Code == Key::Q)
				translation.y += mMove;
			else if (eventData.Code == Key::E)
				translation -= mMove;

			mNode->translate(mNode->getOrientation() * translation * GameApplication::get_const_instance().getElapsed());

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
	}
}

void Camera::onMouseMoved(sf::Event::MouseMoveEvent &eventData)
{
	int offsetX = 0;
	int offsetY = 0;

	int centerX = WIDTH/2;
	int centerY = HEIGHT/2;

	switch(mCameraType)
	{
		case Camera::FREE:
			offsetX = eventData.X - centerX;
			offsetY = eventData.Y - centerY;

		    mNode->yaw(deg(mRotate * -offsetX));
		    mPitchNode->pitch(deg(mRotate * -offsetY));

		break;
		case Camera::ATTACHED:
			// ...

		break;
		case Camera::FIRST_PERSON:
			// ...

		break;
	}
}
