#ifndef EVENTS_HPP
#define	EVENTS_HPP

#include "Core/Utils.hpp"

// Event dependencies below
#include <SFML/Window/Event.hpp>

template<class SignalT>
class SlotObject;

namespace Engine
{
    namespace Events
    {
        NEW_EVENT(void (sf::Event::KeyEvent &eventData), KeyEvent);
        NEW_EVENT(void (sf::Event::SizeEvent &eventData), SizeEvent);
        NEW_EVENT(void (sf::Event::TextEvent &eventData), TextEvent);

        NEW_EVENT(void (sf::Event::MouseButtonEvent &eventData), MouseButtonEvent);
        NEW_EVENT(void (sf::Event::MouseMoveEvent &eventData), MouseMoveEvent);
        NEW_EVENT(void (sf::Event::MouseWheelEvent &eventData), MouseWheelEvent);

        NEW_EVENT(void (sf::Event::JoyButtonEvent &eventData), JoyButtonEvent);
        NEW_EVENT(void (sf::Event::JoyMoveEvent &eventData), JoyMoveEvent);
    }
}

#endif	/* EVENTS_HPP */

