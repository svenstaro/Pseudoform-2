#include "GraphicSystem.h"

template<> GraphicSystem* ISingleton<GraphicSystem>::mInstance = 0;

void GraphicSystem::init()
{
	mRoot = new Ogre::Root("", "", "Pseudoform.log");

	// TODO: Add switcher opengl/directx
	mRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL");

	Ogre::LogManager::getSingletonPtr()->setLogDetail(Ogre::LL_NORMAL);

	// Setup renderer
	const Ogre::RenderSystemList renderers = mRoot->getAvailableRenderers();
	if (renderers.empty()) throw std::runtime_error("No avail renderers!");
	Ogre::RenderSystem *renderer = *(renderers.begin());
	mRoot->setRenderSystem(renderer);
	mRenderSys = renderer;

	mRoot->initialise(false);

	Ogre::NameValuePairList windowParams;
	windowParams["FSAA"] = "0";
	windowParams["vsync"] = "false";

	mWindow = mRoot->createRenderWindow("Pseudoform2", 640, 480, false, &windowParams);

	mWindow->setActive(true);
	mWindow->setAutoUpdated(true);

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	// TODO: Move ColourValue to the list of utils
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	mCamera = mSceneMgr->createCamera("root::_camera");
	mCamera->setNearClipDistance(0.01);
	mCamera->setFarClipDistance(1000);
	mCamera->setAutoAspectRatio(true);
	mCamera->setFOVy(Ogre::Degree(90)); // TODO: Utils

	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5)); // TODO: Utils

	Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.addResourceLocation("", "FileSystem", "General", true);
	rgm.initialiseResourceGroup("General");
}

GraphicSystem::GraphicSystem()
{

}

GraphicSystem::~GraphicSystem()
{
	delete mRoot;
}

void GraphicSystem::update()
{
	// ...
}
