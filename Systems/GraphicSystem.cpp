#include "GraphicSystem.h"

template<> GraphicSystem* ISingleton<GraphicSystem>::mInstance = 0;

void GraphicSystem::init()
{
	mRoot = new Ogre::Root("", "", "Pseudoform.log");

	string renderLib = CONFIG("lib", string, "OPENGL");

	#ifdef _WINDOWS
		string plugins = ".\\";
	#else
		string plugins = CONFIG("plugins", string, "");
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

	Ogre::LogManager::getSingletonPtr()->setLogDetail(Ogre::LL_NORMAL);

	// Setup renderer
	const Ogre::RenderSystemList renderers = mRoot->getAvailableRenderers();
	if (renderers.empty()) throw std::runtime_error("No avail renderers!");
	Ogre::RenderSystem *renderer = *(renderers.begin());
	mRoot->setRenderSystem(renderer);
	mRenderSys = renderer;

	mRoot->initialise(false);

	Ogre::NameValuePairList windowParams;
	windowParams["FSAA"] = CONFIG("fsaa", string, "0");
	windowParams["vsync"] = CONFIG("vsync", string, "false");

	string temp = CONFIG("width", string, "1024")
	string temp2 = CONFIG("height", string, "1024")

	size_t windowWidth = CONFIG("width", size_t, 1024);
	size_t windowHeight = CONFIG("height", size_t, 760);

	bool windowFullscreen = CONFIG("fullscreen", bool, false);

	mWindow = mRoot->createRenderWindow("Pseudoform2", windowWidth, windowHeight, windowFullscreen, &windowParams);

	mWindow->setActive(true);
	mWindow->setAutoUpdated(true);

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mSceneMgr->setAmbientLight(colour(0.1, 0.1, 0.1));

	mCamera = mSceneMgr->createCamera("root::_camera");
	mCamera->setNearClipDistance(0.01);
	mCamera->setFarClipDistance(1000);
	mCamera->setAutoAspectRatio(true);
	mCamera->setFOVy(deg(90));

	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(colour(0.5, 0.5, 0.5));

	Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.addResourceLocation("", "FileSystem", "General", true);
	rgm.initialiseResourceGroup("General");
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
