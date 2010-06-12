#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include <vector>
#include <Ogre.h>

using namespace std;

class LogManager
{
    protected:
        string mDefaultPath;
        std::vector<std::string> mCreatedLogs;

    public:
        LogManager(const string &logPath = "Engine.log") :
                mDefaultPath(logPath) { }

        void write(const string &message, const string logFile = "")
        {
            string workPath = mDefaultPath;
            if (logFile != "")
            {
                // If the log isn't used
                if (std::find(mCreatedLogs.begin(), mCreatedLogs.end(), logFile) == mCreatedLogs.end())
                {
                    Ogre::LogManager::getSingleton().createLog(logFile, false, true);
                    mCreatedLogs.push_back(logFile);
                }
                        
                workPath = logFile;
            }

            Ogre::LogManager::getSingletonPtr()->getLog(workPath)->logMessage(message, Ogre::LML_CRITICAL);
        }
};

#endif
