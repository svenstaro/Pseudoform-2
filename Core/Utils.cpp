#include "Utils.h"

//template<> Utils* ISingleton<Utils>::mInstance = 0;

Utils::Utils()
{
	mRunning = false;

	mConfig = configPtr(new ConfigManager());
	string engineLog = configHandle().getValue<string>("logFilename", "Engine.log");
	//string engineLog = CONFIG("logFilename", string, "Engine.log");

	mLog =  logPtr(new LogManager(engineLog));
}

Utils::~Utils()
{
	mConfig.reset();
	mLog.reset();
}

ConfigManager &Utils::configHandle() const
{
	return *mConfig.get();
}

LogManager &Utils::logHandle() const
{
	return *mLog.get();
}

Utils::renderType *Utils::renderer()
{
	return &mRenderer;
}
