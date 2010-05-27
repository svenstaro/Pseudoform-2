#include "Utils.h"

template<> Utils* ISingleton<Utils>::mInstance = 0;

Utils::Utils()
{
	mConfig = configPtr(new ConfigManager());
	mLog =  logPtr(new LogManager());
}

Utils::~Utils() { }

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
