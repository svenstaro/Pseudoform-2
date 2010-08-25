#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include <boost/serialization/singleton.hpp>
#include <boost/filesystem.hpp>
#include "Core/Utils.hpp"

#include <vector>
#include <fstream>
#include <iostream>

using namespace boost::serialization;
using namespace std;

#define LOG(message) LogManager::get_mutable_instance().write(message, "", "")
#define LOG_META(message) LogManager::get_mutable_instance().write(message, "", __PRETTY_FUNCTION__)
#define LOG_FILE(message, fileName) LogManager::get_mutable_instance().write(message, fileName)
#define LOG_NOFORMAT(message) LogManager::get_mutable_instance().write(message, "", "", false);

class LogManager : public singleton<LogManager>
{
    protected:
        ofstream mLogHandle;
        string mDefaultPath;
        vector<string> mUsedFiles;

        void _forceLog(const string &logPath);
        string _cleanSignature(const string &signature);

    public:
        LogManager();
        
        void setDefaultLog(const string &logPath);
        void write(const string &message, const string logFile = "", const string metaSignature = "", bool formatString = true);
};

#endif
