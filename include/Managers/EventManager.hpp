#ifndef EVENTMANAGER_HPP
#define	EVENTMANAGER_HPP

#include <boost/serialization/singleton.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>

#include "Managers/LogManager.hpp"
#include "Core/Utils.hpp"
#include "Managers/Events/Events.hpp"

#include <typeinfo>
#include <iostream>
#include <map>

using namespace boost;
using namespace std;
using namespace boost::serialization;

// Define section
#define CONNECT(EventType, EventName, FunctionPointer) EventManager::get_mutable_instance().connect<EventType>(EventName, bind(FunctionPointer, this, _1));
#define SIGNAL(EventType, EventName, ...) EventManager::get_mutable_instance().get<EventType>(EventName).Call(EventType::ArgsType(__VA_ARGS__));

// TODO: Add function for removing listener from signal

class EventManager : public singleton<EventManager>
{
    private:
        map<string, any> mSignalAssociation;

    public:
        EventManager() { fillEventMap(); }
        
        void fillEventMap()
        {
            using namespace Engine::Events;

            mSignalAssociation["KeyPressed"] = KeyEvent();
            mSignalAssociation["KeyReleased"] = KeyEvent();

            mSignalAssociation["Resized"] = SizeEvent();
            mSignalAssociation["TextEntered"] = TextEvent();

            mSignalAssociation["MouseButtonPressed"] = MouseButtonEvent();
            mSignalAssociation["MouseButtonReleased"] = MouseButtonEvent();

            mSignalAssociation["MouseMoved"] = MouseMoveEvent();
            mSignalAssociation["MouseWheelMoved"] = MouseWheelEvent();

            mSignalAssociation["JoyButtonPressed"] = JoyButtonEvent();
            mSignalAssociation["JoyButtonReleased"] = JoyButtonEvent();
            mSignalAssociation["JoyMoved"] = JoyMoveEvent();
            
            mSignalAssociation["WindowClosed"] = CloseEvent();
            mSignalAssociation["WindowLostFocus"] = LostFocusEvent();
            mSignalAssociation["WindowGainedFocus"] = GainFocusEvent();
            mSignalAssociation["WindowMouseEntered"] = MouseEnteredEvent();
        }

        template<typename EventType>
        signals2::connection connect(const string signalName, const typename EventType::SignatureSlotType  &eventSlot)
        {
            LOG(FORMAT("[Event System → connect] Connecting new slot for '%1%' signal", signalName));
            return get<EventType>(signalName).Connect(eventSlot);
        }

        template<typename EventType>
        EventType &get(const string &signalName)
        {
            if (mSignalAssociation.count(signalName) == 0)
            {
                LOG(FORMAT("[Event System → get] Wrong assign for the signal '%1%' because it doesn`t exist!",
                    signalName));
            }
            
            try
            {
                return any_cast<EventType&>(mSignalAssociation[signalName]);
            } catch(bad_any_cast &e)
            {
                LOG(FORMAT("[Event System → get] Can`t make casting of type '%1%' into signal '%2%' signature with type '%3%'!",
                        typeid(EventType).name() % signalName % mSignalAssociation[signalName].type().name()));
            } catch(...)
            {
                LOG(FORMAT("[Event System → get] Something wrong happend with getting signal %1%", signalName));
            }
        }
        
        template<typename EventType>
        void create(const string &signalName)
        {
            if (mSignalAssociation.count(signalName) != 0)
            {
                LOG(FORMAT("[Event System → create] Can`t make new signal with name '%1%' because it's already exist!",
                    signalName));
            }

            try
            {
                mSignalAssociation[signalName] = EventType();
                // Event is created in the map. Now we need in typedefinition of it in the signals
                // TODO: This should be created in namespace Events. Fix this.

                // This will not work. The user have to do this manually
                // When he wants to make new event type
                //NEW_EVENT(typename SignatureOf<EventType>::type, signalName);
            } catch(bad_any_cast &e)
            {
                LOG(FORMAT("[Event System → create] Can`t make casting from type '%1%' into signal '%2%' signature!",
                        typeid(EventType).name() % signalName));
            } catch(...)
            {
                LOG(FORMAT("[Event System → create] Something wrong happend with making new signal %1%", signalName));
            }
        }
};

#endif	/* EVENTMANAGER_HPP */

