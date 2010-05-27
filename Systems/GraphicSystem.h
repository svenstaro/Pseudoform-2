#ifndef _GRAPHIC_SYSTEM_H_
#define _GRAPHIC_SYSTEM_H_

#include "System.h"
#include "Core/Singleton.h"
#include "Core/AppIncludes.h"

class GraphicSystem : public ISystem, public ISingleton<GraphicSystem>
{
	private:
		Ogre::Root *mRoot;
		Ogre::RenderWindow *mWindow;
		Ogre::RenderSystem *mRenderSys;
		Ogre::SceneManager *mSceneMgr;
		Ogre::Viewport *mViewport;
		Ogre::Camera *mCamera;
	
	public:
		Ogre::Root *getRoot() const { return mRoot; }
		Ogre::RenderWindow *getWindow() const { return mWindow; }
		Ogre::RenderSystem *getRenderSys() const { return mRenderSys; }
		Ogre::SceneManager *getSceneMgr() const { return mSceneMgr; }
		Ogre:: Viewport *getViewport() const { return mViewport; }
		Ogre::Camera *getCamera() const { return mCamera; }

		GraphicSystem();
		~GraphicSystem();

		// Inherited from ISystem
		void init();
		void update();
		std::string toString();
};

#endif
