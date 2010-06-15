#ifndef _LOG_MANAGER_H_
#define _LOG_MANAGER_H_

#include <vector>
#include <Ogre.h>
#include <boost/serialization/singleton.hpp>

using namespace boost::serialization;
using namespace std;

#define LOG(message) LogManager::get_mutable_instance().write(message)
class LogManager : public singleton<LogManager>
{
    protected:
        string mDefaultPath;
        std::vector<std::string> mCreatedLogs;

    public:
        LogManager();
        
        void setDefaultLog(const string &logPath);
        void write(const string &message, const string logFile = "");
};

#endif
