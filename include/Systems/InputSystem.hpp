#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "System.hpp"
#include "Core/GameApplication.hpp"
#include "Core/Singleton.hpp"
#include "Managers/Events/Events.hpp"

#include "Managers/LogManager.hpp"
#include "Managers/EventManager.hpp"

#include <boost/serialization/singleton.hpp>
#include <boost/shared_ptr.hpp>

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>

using namespace boost::serialization;
using namespace Engine;

class InputSystem : public ISystem, public ISingleton<InputSystem>, public OIS::KeyListener, public OIS::MouseListener
{
    private:
        size_t mWindowHandle;

        OIS::Mouse *mMouse;
        OIS::Keyboard *mKeyboard;

        OIS::InputManager *mInputSystem;

	    bool keyPressed(const OIS::KeyEvent &e);
	    bool keyReleased(const OIS::KeyEvent &e);

	    bool mouseMoved(const OIS::MouseEvent &e);
	    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

    public:
        InputSystem();
        ~InputSystem();

        OIS::Mouse* getMouse( );
	    OIS::Keyboard* getKeyboard();

        void setWindowExtents(int width, int height);

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
