#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include <vector>
#include <Ogre.h>
#include <boost/serialization/singleton.hpp>

using namespace boost::serialization;
using namespace std;

#define LOG(message) LogManager::get_const_instance().write(message)
class LogManager : public singleton<LogManager>
{
    protected:
        string mDefaultPath;
        std::vector<std::string> mCreatedLogs;

    public:
        LogManager() { mDefaultPath = "Engine.log"; }
        
        void setDefaultLog(const string &logPath) { mDefaultPath = logPath; }

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
