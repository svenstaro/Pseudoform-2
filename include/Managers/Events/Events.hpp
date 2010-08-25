#ifndef EVENTS_HPP
#define	EVENTS_HPP

#include "Core/Utils.hpp"
#include "Managers/Events/SlotObject.hpp"

#include <OISMouse.h>
#include <OISKeyboard.h>

namespace Engine
{
    namespace Events
    {
    /*
        NEW_EVENT(void (sf::Event::KeyEvent &eventData), KeyEvent);
        NEW_EVENT(void (sf::Event::SizeEvent &eventData), SizeEvent);
        NEW_EVENT(void (sf::Event::TextEvent &eventData), TextEvent);

        NEW_EVENT(void (sf::Event::MouseButtonEvent &eventData), MouseButtonEvent);
        NEW_EVENT(void (sf::Event::MouseMoveEvent &eventData), MouseMoveEvent);
        NEW_EVENT(void (sf::Event::MouseWheelEvent &eventData), MouseWheelEvent);

        NEW_EVENT(void (sf::Event::JoyButtonEvent &eventData), JoyButtonEvent);
        NEW_EVENT(void (sf::Event::JoyMoveEvent &eventData), JoyMoveEvent);

        NEW_EVENT(void (void), CloseEvent);
        NEW_EVENT(void (void), LostFocusEvent);
        NEW_EVENT(void (void), GainFocusEvent);
        NEW_EVENT(void (void), MouseEnteredEvent);
     */
    	NEW_EVENT(void (const OIS::KeyEvent &e), KeyEvent);
    	NEW_EVENT(void (const OIS::MouseEvent &e, const OIS::MouseButtonID &id), MouseButtonEvent);
    	NEW_EVENT(void (const OIS::MouseEvent &ed), MouseMoveEvent);

        NEW_EVENT(void (void), GlobalUpdateEvent);
        NEW_EVENT(void (void), GlobalInitEvent);
    }
}

#endif	/* EVENTS_HPP */
