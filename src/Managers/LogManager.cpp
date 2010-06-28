#include "Managers/LogManager.hpp"

LogManager::LogManager()
{
    mDefaultPath = "Engine.log";
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

    mLogHandle.open(workPath.c_str(), fstream::app | fstream::ate);
    mLogHandle << getCurrentTime() + "\t: " + message + "\n";
    mLogHandle.close();
}