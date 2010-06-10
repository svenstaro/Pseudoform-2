#ifndef _UTILS_H_
#define _UTILS_H_

#define bforeach BOOST_FOREACH
#define LOG(message) Utils::get_const_instance().logHandle().write(message)
#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define CONFIG(key, type, def) Utils::get_const_instance().configHandle().getValue<type>(key, def)

#include "PseudoformManagers.hpp"

using namespace boost;
using namespace boost::serialization;

class Utils : public singleton<Utils>
{
    protected:
        ConfigManager *configHandlePtr;
        LogManager *logHandlePtr;
        ResourcesManager *resourceHandlePtr;

    public:
        Utils()
        {
            configHandlePtr = new ConfigManager();

            string engineLog = configHandle().getValue<string>("engine.logFilename", "Engine.log");
            logHandlePtr = new LogManager(engineLog);
            
            resourceHandlePtr = new ResourcesManager();
        }
        ~Utils()
        {
            delete configHandlePtr;
            delete logHandlePtr;
            delete resourceHandlePtr;
        }

        ConfigManager &configHandle() const { return *configHandlePtr; }
        LogManager &logHandle() const { return *logHandlePtr; }
        ResourcesManager &resourceHandle() const { return *resourceHandlePtr; }

        enum renderType {
            OPENGL,
            DIRECT3D
        } mRenderer;
        renderType *renderer() { return &mRenderer; }
};

#endif
