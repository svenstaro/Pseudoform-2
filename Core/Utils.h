#ifndef _UTILS_H_
#define _UTILS_H_

#include "Core/Singleton.h"
#include "Core/AppIncludes.h"

using namespace boost;

class Utils : public ISingleton<Utils>
{
	protected:
		typedef shared_ptr<ConfigManager> configPtr;
		typedef shared_ptr<LogManager> logPtr;

		configPtr mConfig;
		logPtr mLog;

	public:
		Utils();
		~Utils();

		ConfigManager &configHandle() const;
		LogManager &logHandle() const;

		enum renderType {
			OPENGL,
			DIRECT3D
		} mRenderer;
		renderType *renderer();

		bool mRunning;
};

#endif
