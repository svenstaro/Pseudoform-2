#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include "Core/AppIncludes.h"

using namespace std;

class LogManager
{
	protected:
		string mLogPath;

	public:
		LogManager(const string &logPath = "Engine.log") :
			mLogPath(logPath) { }

		void write(const string &message)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(message, Ogre::LML_CRITICAL);
		}
};

#endif
