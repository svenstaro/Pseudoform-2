#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include <boost/serialization/singleton.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Managers/LogManager.hpp"
#include <deque>

using namespace boost;
using namespace std;

class State
{
	public:
		virtual ~State() { }
		virtual void update() = 0;
		virtual void shutdown() = 0;
};

typedef shared_ptr<State> StatePtr;
typedef deque<StatePtr> StateDeque;

class StateManager : public singleton<StateManager>
{
	private:
		StateDeque mStates;
		StatePtr mActiveState;

	public:
		~StateManager();

		void push(State *state);
		void update();

		State *getActiveState();
		State *pop();
};

#endif /* _STATE_MANAGER_HPP_ */
