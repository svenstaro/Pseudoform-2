#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include <boost/serialization/singleton.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Managers/LogManager.hpp"

using namespace boost;
using namespace std;

class State
{
	public:
		virtual ~State() { }
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void shutdown() = 0;
};

class StateManager : public singleton<ConfigManager>
{
	private:
		ptr_vector<State> mStates;
		shared_ptr<State> mActiveState;

		~StateManager();

	public:
		void push(const State &state);
		State *getActiveState();

		State *pop();
};

#endif /* _STATE_MANAGER_HPP_ */
