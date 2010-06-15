#include "Managers/LogManager.hpp"

LogManager::LogManager()
{
    mDefaultPath = "Engine.log";
}

void LogManager::setDefaultLog(const string& logPath)
{
    mDefaultPath = logPath;
}

void LogManager::write(const string& message, const string logFile)
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