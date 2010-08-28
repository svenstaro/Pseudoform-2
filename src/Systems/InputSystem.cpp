#include "Systems/InputSystem.hpp"

#include <iostream>

template<> InputSystem* ISingleton<InputSystem>::mInstance = 0;

bool InputSystem::keyPressed(const OIS::KeyEvent &e)
{
	SIGNAL(Events::KeyEvent, "KeyPressed", e);
	guiSystem.handle()->injectKeyPress(MyGUI::KeyCode::Enum(e.key), e.text);
    return true;
}

bool InputSystem::keyReleased(const OIS::KeyEvent &e)
{
	SIGNAL(Events::KeyEvent, "KeyReleased", e);
	guiSystem.handle()->injectKeyRelease(MyGUI::KeyCode::Enum(e.key));
    return true;
}

bool InputSystem::mouseMoved(const OIS::MouseEvent &e)
{
	SIGNAL(Events::MouseMoveEvent, "MouseMoved", e);
	guiSystem.handle()->injectMouseMove(e.state.X.abs, e.state.Y.abs, e.state.Z.abs);
    return true;
}

bool InputSystem::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	SIGNAL(Events::MouseButtonEvent, "MouseButtonPressed", e, id);
	guiSystem.handle()->injectMousePress(e.state.X.abs, e.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool InputSystem::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	SIGNAL(Events::MouseButtonEvent, "MouseButtonReleased", e, id);
	guiSystem.handle()->injectMouseRelease(e.state.X.abs, e.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool InputSystem::windowClosing (Ogre::RenderWindow *rw)
{
    bool ret = true;
    SIGNAL(Events::ClosingEvent, "WindowClosing", rw, ret);
    return ret;
}

void InputSystem::windowClosed (Ogre::RenderWindow *rw)
{
    SIGNAL(Events::WindowEvent, "WindowClosed", rw);
}

void InputSystem::windowMoved (Ogre::RenderWindow *rw)
{
    SIGNAL(Events::WindowEvent, "WindowMoved", rw);
}

void InputSystem::windowResized (Ogre::RenderWindow *rw)
{
    SIGNAL(Events::WindowEvent, "WindowResized", rw);
}

void InputSystem::windowFocusChanged (Ogre::RenderWindow *rw)
{
    SIGNAL(Events::WindowEvent, "WindowFocusChanged", rw);
}

InputSystem::InputSystem():
    mMouse(0),
    mKeyboard(0),
    mInputSystem(0) { }

InputSystem::~InputSystem()
{
    if( mInputSystem ) {
        if( mMouse ) {
            mInputSystem->destroyInputObject(mMouse);
            mMouse = 0;
        }

        if( mKeyboard ) {
            mInputSystem->destroyInputObject(mKeyboard);
            mKeyboard = 0;
        }

        mInputSystem->destroyInputSystem(mInputSystem);
        mInputSystem = 0;
    }
}

void InputSystem::init()
{
    graphicSystemConst.getWindow()->getCustomAttribute("WINDOW", &mWindowHandle);
    LOG("\t- Got window handle from Ogre");

    Ogre::WindowEventUtilities::addWindowEventListener(graphicSystemConst.getWindow(),this);

    if( !mInputSystem )
    {
        OIS::ParamList paramList;
        std::ostringstream windowHndStr;

        windowHndStr << (unsigned int)mWindowHandle;
        paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

		bool showCursor = CONFIG("window.showCursor", bool, false);
		if (!showCursor)
		{
			LOG("\t- Input system will be in foreground mode");
			#if defined OIS_WIN32_PLATFORM
				paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
				paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
				paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
				paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
			#elif defined OIS_LINUX_PLATFORM
				paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
				paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
				paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
				paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
			#endif
		}

        mInputSystem = OIS::InputManager::createInputSystem( paramList );
        LOG("\t- Input system is created");

        mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
        mKeyboard->setEventCallback( this );
        LOG("\t- Keyboard created and configured");

        mMouse = static_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
        mMouse->setEventCallback( this );
        LOG("\t- Mouse created and configured");

        // Get window size
        unsigned int width, height, depth;
        int left, top;
        graphicSystemConst.getWindow()->getMetrics(width, height, depth, left, top);

        this->setWindowExtents(width, height);
        LOG("\t- Window size have been appeared for input region");
    }
}

void InputSystem::update(float elapsed)
{
    if(mMouse)
        mMouse->capture();

    if(mKeyboard)
        mKeyboard->capture();
}

OIS::Mouse* InputSystem::getMouse() {
    return mMouse;
}

OIS::Keyboard* InputSystem::getKeyboard() {
    return mKeyboard;
}

void InputSystem::setWindowExtents( int width, int height ) {
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
}

std::string InputSystem::toString()
{
    return "InputSystem";
}
