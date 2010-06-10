#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include "PseudoformAdditional.hpp"
#include <vector>

using namespace std;

class LogManager
{
    protected:
        string mDefaultPath;

    public:
        LogManager(const string &logPath = "Engine.log") :
                mDefaultPath(logPath) { }

        void write(const string &message, const string logFile = "")
        {
            string workPath = mDefaultPath;
            if (logFile != "")
            {
                if (Ogre::LogManager::getSingletonPtr()->getLog(logFile) == NULL)
                        Ogre::LogManager::getSingleton().createLog(logFile, false, true);

                workPath = logFile;
            }


            Ogre::LogManager::getSingletonPtr()->getLog(workPath)->logMessage(message, Ogre::LML_CRITICAL);
        }
};

#endif
