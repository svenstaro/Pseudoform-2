#ifndef _UTILS_H_
#define _UTILS_H_

#include "Core/Managers.hpp"

#include <boost/serialization/singleton.hpp>

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
