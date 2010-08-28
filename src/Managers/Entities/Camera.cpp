#include "Managers/Entities/Camera.hpp"

Camera::Camera(const string entityName)
{
	Ogre::SceneManager *sceneMgr = GraphicSystem::get_const_instance().getSceneMgr();

    mEntityName = entityName;

    mCamera = sceneMgr->createCamera(entityName);

    mMove = 250;
    mRotate = 0.13;

    mNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Node:Camera_" + entityName);
    mPitchNode = mNode->createChildSceneNode("Node:CameraPitch_" + entityName);
    mPitchNode->attachObject(mCamera);

}

void Camera::loadFromFile(const string &filename, const string &res)
{
    _declareEntityResources();

    if (Ogre::ResourceGroupManager::getSingletonPtr()->resourceExists(res, filename))
    {
        //Ogre::ResourceGroupManager::getSingleton().declareResource(entMesh, "Mesh", res);

        ptree tree_handle;
        read_info(Utils::get_const_instance().getMediaPath() + "Entities/" +  filename + "/init.info", tree_handle);

        float fov = tree_handle.get<float>("type_settings.fov", 90);
        float nearClip = tree_handle.get<float>("type_settings.nearClip", 1);
        float farClip = tree_handle.get<float>("type_settings.farClip", 1000);
        bool autoAR = tree_handle.get<bool>("type_settings.autoAR", true);
        configure(nearClip, farClip, autoAR, fov);
        bool attachVP = tree_handle.get<bool>("type_settings.attachVP", true);
        if(attachVP)
            GraphicSystem::get_mutable_instance().getViewport()->setCamera(mCamera);
        string type = tree_handle.get<string>("type_settings.cam_type", "DONT_USE");
        if(type == "DONT_USE")
            setCameraType(Camera::DONT_USE);
        else if(type == "FREE")
            setCameraType(Camera::FREE);
        else if(type == "FIRST_PERSON")
            setCameraType(Camera::FIRST_PERSON);
        else if(type == "ATTACHED")
            setCameraType(Camera::ATTACHED);
        LOG("Loaded Camera from " + filename);
    }


    _defaultLoader(filename);

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
		//CONNECT(Engine::Events::KeyEvent, "KeyPressed", &Camera::onKeyPressed) //we don't need this anymore
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
    using namespace sf;
	vec3 translation = vec3::ZERO;
    OIS::Keyboard *keyboard = InputSystem::get_mutable_instance().getKeyboard();
	switch(mCameraType)
	{
		case Camera::FREE:
            if (keyboard->isKeyDown(OIS::KC_W)) //smoother movement instead of using the keyPressed-Callback method
			    translation.z -= mMove;
			else if (keyboard->isKeyDown(OIS::KC_S))
			    translation.z += mMove;
			if (keyboard->isKeyDown(OIS::KC_A))
			    translation.x -= mMove;
			else if (keyboard->isKeyDown(OIS::KC_D))
			    translation.x += mMove;
			if (keyboard->isKeyDown(OIS::KC_Q))
				translation.y += mMove;
			else if (keyboard->isKeyDown(OIS::KC_E))
				translation.y -= mMove;

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
