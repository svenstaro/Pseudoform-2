#ifndef _GAME_LISTENER_H_
#define _GAME_LISTENER_H_

#include "Core/OgreIncludes.h"

class GameListener: public Ogre::FrameListener
	// SFML Key and Mouse listeners!
{
	protected:
		// Current Key
	
	public:
		bool frameStarted(const Ogre::FrameEvent &evt)
		{
			// Gui update
			// Physics update
			// Sound update
			// Graphic update

			return true;
		}

		// Inject gui here	

		// switch(Current Key) { ... }
};

#endif
