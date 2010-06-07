#ifndef _UTILS_H_
#define _UTILS_H_

#include "Core/AppIncludes.hpp"

using namespace boost;
using namespace boost::serialization;

class Utils : public singleton<Utils>
{
	protected:
                ConfigManager *configHandlePtr;
                LogManager *logHandlePtr;

	public:
		Utils()
                {
                    mRunning = false;

                    configHandlePtr = new ConfigManager();
                    string engineLog = configHandle().getValue<string>("engine.logFilename", "Engine.log");

                    logHandlePtr = new LogManager(engineLog);
                }
		~Utils()
                {
                    delete configHandlePtr;
                    delete logHandlePtr;
                }

                ConfigManager &configHandle() const { return *configHandlePtr; }
                LogManager &logHandle() const { return *logHandlePtr; }

		enum renderType {
			OPENGL,
			DIRECT3D
		} mRenderer;
		renderType *renderer() { return &mRenderer; }

		bool mRunning;
};

#endif
