#ifndef SLOTOBJECT_HPP
#define	SLOTOBJECT_HPP

#include <boost/function_types/parameter_types.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/fused.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

using namespace boost;
using namespace boost::signals2;

// This structure for taking signature of the signal object
template<class SignalT>
struct SignatureOf;

template<
    typename Signature, typename Combiner, typename Group,
    typename GroupCompare, typename SlotFunction
>
struct SignatureOf<
    signals2::signal<Signature, Combiner, Group, GroupCompare, SlotFunction>
>
{
    typedef Signature type;
};

// Signal wrapper
template<class SignalT>
class SlotObject
{
    private:
        shared_ptr<SignalT> mSignal;
    public:
        SlotObject() { mSignal = shared_ptr<SignalT>(new SignalT()); }

        typedef typename SignatureOf<SignalT>::type SignatureType;
        typedef typename SignalT::slot_type SignatureSlotType;

        // Packing the arguments signature into vector
        typedef typename fusion::result_of::as_vector<
            typename function_types::parameter_types<SignatureType>::type
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

#endif	/* SLOTOBJECT_HPP */

