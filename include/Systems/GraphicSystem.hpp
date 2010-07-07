#ifndef _GRAPHIC_SYSTEM_H_
#define _GRAPHIC_SYSTEM_H_

#include "System.hpp"
#include "Core/Types.hpp"
#include "Core/Singleton.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/ConfigManager.hpp"
#include "Managers/ResourceManager.hpp"

#include <boost/foreach.hpp>
#include <boost/serialization/singleton.hpp>

#include <Ogre.h>

using namespace boost::serialization;
using namespace std;

//class GraphicSystem : public ISystem,  public Ogre::Singleton<GraphicSystem>
//class GraphicSystem : public ISystem, public singleton<GraphicSystem>
class GraphicSystem : public ISystem, public ISingleton<GraphicSystem>
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
        void update(float elapsed);
        std::string toString();
};

#endif
