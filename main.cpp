#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Core/OgreIncludes.h"
#include "Core/GameApplication.h"

int main(int argc, char **argv)
{
	GameApplication appHandle;
	try
	{
		if (!appHandle.init()) return 0;

		Ogre::LogManager::getSingleton().logMessage("******** System Initialized *******\n");
		appHandle.start();

		Ogre::LogManager::getSingleton().logMessage("******** Entering main loop *******\n");
		appHandle.loop();
		Ogre::LogManager::getSingleton().logMessage("********* Main loop exited ********\n");

		Ogre::LogManager::getSingleton().logMessage("********** Shutting down **********\n");
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
        Ogre::LogManager::getSingleton().logMessage(desc.str());
	}
	// catch(...) { } catch (python_error) { }
}
