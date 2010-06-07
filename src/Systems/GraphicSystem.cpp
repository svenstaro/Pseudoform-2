#include "Systems/GraphicSystem.hpp"

template<> GraphicSystem* Ogre::Singleton<GraphicSystem>::ms_Singleton = 0;

void GraphicSystem::init()
{
	mRoot = new Ogre::Root("", "", "Pseudoform.log");

	Ogre::LogManager::getSingletonPtr()->setLogDetail(Ogre::LL_NORMAL);
	string engineLog = CONFIG("logFilename", string, "Engine.log");
        Ogre::LogManager::getSingleton().createLog(engineLog, false, true);

	string renderLib = CONFIG("renderLib", string, "OPENGL");

	#ifdef _WINDOWS
		string plugins = ".\\";
	#else
		string plugins = CONFIG("pluginsDir", string, "");
	#endif

	if (renderLib == "OPENGL")
	{
		mRoot->loadPlugin(plugins + "RenderSystem_GL");
		// TODO: Setup enum var
	}
	else
	{
		mRoot->loadPlugin(plugins + "RenderSystem_Direct3D9");
	}

	// TODO: Add loading of OGRE plugins from list

	// Setup renderer
	const Ogre::RenderSystemList renderers = mRoot->getAvailableRenderers();
	if (renderers.empty()) throw std::runtime_error("No avail renderers!");
	Ogre::RenderSystem *renderer = *(renderers.begin());
	mRoot->setRenderSystem(renderer);
	mRenderSys = renderer;

	mRoot->initialise(false);

	Ogre::NameValuePairList windowParams;
	windowParams["FSAA"] = CONFIG("paramFSAA", string, "0");
	windowParams["vsync"] = CONFIG("paramVSYNC", string, "false");

	size_t windowWidth = CONFIG("windowWidth", size_t, 1024);
	size_t windowHeight = CONFIG("windowHeight", size_t, 760);

	bool windowFullscreen = CONFIG("windowFullscreen", bool, false);

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
