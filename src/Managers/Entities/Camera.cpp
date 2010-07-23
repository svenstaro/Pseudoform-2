#include "Managers/Entities/Camera.hpp"

Camera::Camera(const string cameraName)
{
	Ogre::SceneManager *sceneMgr = GraphicSystem::get_const_instance().getSceneMgr();

    mEntityName = cameraName;
    mCamera = sceneMgr->createCamera(cameraName);

    mNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Node:Camera" + cameraName);
    mNode->createChildSceneNode("Node:CameraPitch" + cameraName)->attachObject(mCamera);
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
void Camera::_loadData() { }
void Camera::update(float elapsed) { }
