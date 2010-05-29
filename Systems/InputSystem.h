#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "System.h"
#include "Core/Singleton.h"
#include "Core/AppIncludes.h"

class InputSystem : public ISystem, public ISingleton<InputSystem>
{
	private:
		size_t mWindowHandle;
		boost::shared_ptr<sf::Window> mInputWindow;

	public:
		InputSystem();
		~InputSystem();

		// Inherited from ISystem
		void init();
		void update();
		std::string toString();
};

#endif
