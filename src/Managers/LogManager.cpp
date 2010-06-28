#include "Managers/LogManager.hpp"

LogManager::LogManager()
{
    mDefaultPath = "Engine.log";
}

void LogManager::_forceLog(const string& logPath)
{
    if (std::find(mUsedFiles.begin(), mUsedFiles.end(), logPath) == mUsedFiles.end())
    {
        if (boost::filesystem::exists(logPath))
            boost::filesystem::remove(logPath);
        mUsedFiles.push_back(logPath);
    }
}

string LogManager::getCurrentTime(){
    ptime time = microsec_clock::local_time();
    return to_simple_string(time);
}

void LogManager::setDefaultLog(const string& logPath)
{
    mDefaultPath = logPath;
}

void LogManager::write(const string& message, const string logFile)
{
    string workPath = mDefaultPath;
    if (logFile != "") workPath = logFile;

    this->_forceLog(workPath);

    mLogHandle.open(workPath.c_str(), fstream::app | fstream::ate);
    mLogHandle << getCurrentTime() + "\t: " + message + "\n";
    mLogHandle.close();
}