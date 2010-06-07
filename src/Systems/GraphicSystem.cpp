#include "Systems/GraphicSystem.hpp"

template<> GraphicSystem* Ogre::Singleton<GraphicSystem>::ms_Singleton = 0;

void GraphicSystem::init()
{
	mRoot = new Ogre::Root("", "", "Pseudoform.log");

	Ogre::LogManager::getSingletonPtr()->setLogDetail(Ogre::LL_NORMAL);
	string engineLog = CONFIG("engine.logFilename", string, "Engine.log");
        Ogre::LogManager::getSingleton().createLog(engineLog, false, true);

	string renderLib = CONFIG("ogre.renderLib", string, "OPENGL");

	#ifdef _WINDOWS
		string pluginsDir = ".\\";
	#else
		string pluginsDir = CONFIG("ogre.pluginsDir", string, "/usr/lib/OGRE/");
	#endif

	if (renderLib == "OPENGL")
	{
		mRoot->loadPlugin(pluginsDir + "RenderSystem_GL");
		// TODO: Setup enum var
	}
	else
	{
		mRoot->loadPlugin(pluginsDir + "RenderSystem_Direct3D9");
	}

        std::vector<std::string> pluginsList = Utils::get_const_instance().configHandle().getListValue("ogre.plugins");
        bforeach(std::string &plugin, pluginsList)
        {
            mRoot->loadPlugin(pluginsDir + plugin);
        }

	// Setup renderer
	const Ogre::RenderSystemList renderers = mRoot->getAvailableRenderers();
	if (renderers.empty()) throw std::runtime_error("No available renderers!");
	Ogre::RenderSystem *renderer = *(renderers.begin());
	mRoot->setRenderSystem(renderer);
	mRenderSys = renderer;

	mRoot->initialise(false);

	Ogre::NameValuePairList windowParams;
	windowParams["FSAA"] = CONFIG("window.paramFSAA", string, "0");
	windowParams["vsync"] = CONFIG("window.paramVSYNC", string, "false");

	size_t windowWidth = CONFIG("window.width", size_t, 1024);
	size_t windowHeight = CONFIG("window.height", size_t, 768);

	bool windowFullscreen = CONFIG("window.fullscreen", bool, false);

	mWindow = mRoot->createRenderWindow("Pseudoform2", windowWidth, windowHeight, windowFullscreen, &windowParams);
	LOG("\t- Window has been created with given params");

	mWindow->setActive(true);
	mWindow->setAutoUpdated(true);

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mSceneMgr->setAmbientLight(colour(0.1, 0.1, 0.1));

	mCamera = mSceneMgr->createCamera("root::_camera");
	mCamera->setNearClipDistance(0.01);
	mCamera->setFarClipDistance(1000);
	mCamera->setAutoAspectRatio(true);
	mCamera->setFOVy(deg(90));
	LOG("\t- Camera is set up");

	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(colour(0.5, 0.5, 0.5));

	// TODO: Add resources worker
	Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.addResourceLocation("", "FileSystem", "General", true);
	rgm.initialiseResourceGroup("General");
	LOG("\t- All resources are loaded");
}

GraphicSystem::GraphicSystem()
{
}

std::string GraphicSystem::toString()
{
	return "GraphicSystem";
}

GraphicSystem::~GraphicSystem()
{
	delete mRoot;
}

void GraphicSystem::update()
{
	// ...
}
