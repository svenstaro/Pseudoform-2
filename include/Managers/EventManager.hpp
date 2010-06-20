#ifndef EVENTMANAGER_HPP
#define	EVENTMANAGER_HPP

#include <boost/serialization/singleton.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/fused.hpp>
#include <boost/shared_ptr.hpp>

#include "Managers/LogManager.hpp"
#include "Core/Utils.hpp"
#include "Core/Events.hpp"

#include <typeinfo>
#include <iostream>
#include <map>

using namespace boost;
using namespace std;
using namespace boost::signals2;
using namespace boost::serialization;

// This structure for taking signature of the signal object
template<class SignalT>
struct SignatureOf;

template<
    typename Signature, typename Combiner, typename Group,
    typename GroupCompare, typename SlotFunction
>
struct SignatureOf<
    boost::signals2::signal<Signature, Combiner, Group, GroupCompare, SlotFunction>
>
{
    typedef Signature type;
};

// Signal wrapper
template<class SignalT>
class SlotObject
{
    private:
        boost::shared_ptr<SignalT> mSignal;
    public:
        SlotObject() { mSignal = boost::shared_ptr<SignalT>(new SignalT()); }

        typedef typename SignatureOf<SignalT>::type SignatureType;
        typedef typename SignalT::slot_type SignatureSlotType;

        // Packing the arguments signature into vector
        typedef typename boost::fusion::result_of::as_vector<
            typename boost::function_types::parameter_types<SignatureType>::type
        >::type ArgsType;

        // Public interface ----------------------------------------------------

        // This is for easy calling of current signal
        void Call(ArgsType P)
        {
            boost::fusion::fused<SignalT&> f(*mSignal);
            f(P);
        }

        // This is for connecting slots
        signals2::connection Connect(const typename SignalT::slot_type &slotHandle)
        {
            return mSignal.get()->connect(slotHandle);
        }
};

// Define section
#define CONNECT(EventType, EventName, FunctionPointer) EventManager::get_mutable_instance().connect<EventType>(EventName, bind(FunctionPointer, this, _1));
#define SIGNAL(EventType, EventName, Arguments) EventManager::get_mutable_instance().get<EventType>(EventName).Call(EventType::ArgsType(Arguments));

// TODO: Allow lambda-slots

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
        }

        template<typename EventType>
        signals2::connection connect(const string signalName, const typename EventType::SignatureSlotType  &eventSlot)
        {
            return get<EventType>(signalName).Connect(eventSlot);
            LOG(FORMAT("[Event System → connect] Connected new slot for '%1%' signal", signalName));
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
                NEW_EVENT(typename SignatureOf<EventType>::type, signalName);
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

