#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Core/AppIncludes.h"
#include "Core/GameApplication.h"

int main(int argc, char **argv)
{
	GameApplication appHandle;

	try
	{
		if (!appHandle.init()) return 0;

		LOG("System initialized ******************\n");
		appHandle.start();

		LOG("Entering Main Loop ******************\n");
		appHandle.loop();
		LOG("Exiting Main Loop *******************\n");

		LOG("Shutting down ***********************\n");
		appHandle.shutdown();
	}
	catch(const std::exception &e)
	{
		Ogre::StringUtil::StrStreamType desc;

        desc << 
            "\nAn exception has been thrown!\n"
            "-----------------------------------\n"
            "Details:\n"
            "-----------------------------------\n"
            << "Description: " << e.what();

        std::cerr << desc.str();
        LOG(desc.str());
	}
	// catch(...) { } catch (python_error) { }
}
