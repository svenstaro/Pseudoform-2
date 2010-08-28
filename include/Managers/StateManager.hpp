#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include <boost/serialization/singleton.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Core/Utils.hpp"
#include "Managers/LogManager.hpp"
#include <deque>

using namespace boost;
using namespace std;

class State
{
    public:
        virtual ~State() { }
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void shutdown() = 0;
        virtual string type() = 0;
};

typedef shared_ptr<State> StatePtr;
typedef deque<StatePtr> StateDeque;

// Call this when need to run to the next state
#define READY_TO_ADVANCE() StateManager::get_mutable_instance().setAdvanceState(true);

#define stateManager (StateManager::get_mutable_instance())
#define stateManagerConst (StateManager::get_const_instance())

class StateManager : public singleton<StateManager>
{
    private:
        StateDeque mStates;
        StatePtr mActiveState;

        bool mAdvanceState;

    public:
        StateManager();
        ~StateManager();

        void push(State *state);
        void update();
        void setAdvanceState(bool advance);

        State *getActiveState();
        State *pop();
};

#endif /* _STATE_MANAGER_HPP_ */
