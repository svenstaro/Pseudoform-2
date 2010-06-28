#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include <boost/serialization/singleton.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/filesystem.hpp>

#include <vector>
#include <fstream>
#include <iostream>

using namespace boost::serialization;
using namespace std;
using namespace boost::posix_time;

#define LOG(message) LogManager::get_mutable_instance().write(message)
class LogManager : public singleton<LogManager>
{
    protected:
        ofstream mLogHandle;
        string mDefaultPath;
        vector<string> mUsedFiles;

        string getCurrentTime();
        void _forceLog(const string &logPath);

    public:
        LogManager();
        
        void setDefaultLog(const string &logPath);
        void write(const string &message, const string logFile = "");
};

#endif
