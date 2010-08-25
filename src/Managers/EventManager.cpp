#include "Managers/EventManager.hpp"

EventManager::EventManager()
{
    fillEventMap();
}

void EventManager::fillEventMap()
{
    using namespace Engine::Events;

    mSignalAssociation["KeyPressed"] = KeyEvent();
    mSignalAssociation["KeyReleased"] = KeyEvent();

    //mSignalAssociation["Resized"] = SizeEvent();
    //mSignalAssociation["TextEntered"] = TextEvent();

    mSignalAssociation["MouseButtonPressed"] = MouseButtonEvent();
    mSignalAssociation["MouseButtonReleased"] = MouseButtonEvent();

    mSignalAssociation["MouseMoved"] = MouseMoveEvent();
    //mSignalAssociation["MouseWheelMoved"] = MouseWheelEvent();

    /*
    mSignalAssociation["JoyButtonPressed"] = JoyButtonEvent();
    mSignalAssociation["JoyButtonReleased"] = JoyButtonEvent();
    mSignalAssociation["JoyMoved"] = JoyMoveEvent();

    mSignalAssociation["WindowClosed"] = CloseEvent();
    mSignalAssociation["WindowLostFocus"] = LostFocusEvent();
    mSignalAssociation["WindowGainedFocus"] = GainFocusEvent();
    mSignalAssociation["WindowMouseEntered"] = MouseEnteredEvent();
     */

    mSignalAssociation["Updated"] = GlobalUpdateEvent();
    mSignalAssociation["Inited"] = GlobalInitEvent();
}
