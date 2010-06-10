#ifndef _GRAPHIC_SYSTEM_H_
#define _GRAPHIC_SYSTEM_H_

#include "System.hpp"
#include "PseudoformAdditional.hpp"
#include "PseudoformCore.hpp"

using namespace boost::serialization;
using namespace std;

class GraphicSystem : public ISystem,  public Ogre::Singleton<GraphicSystem>
{
    protected:
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
