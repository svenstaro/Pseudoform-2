#include "Managers/StateManager.hpp"
#include "Managers/LogManager.hpp"

void StateManager::push(const StatePtr &state)
{
	mStates.push_back(state);
}

StateManager::~StateManager()
{
	while (!mStates.empty())
	{
		mStates.pop_back();
	}
}

State *StateManager::pop()
{
	if (mStates.empty()) return StatePtr().get();

	mActiveState = mStates.back();	// Store pointer for next state to use
	mStates.pop_back();				// And remove it from list
}

State *StateManager::getActiveState()
{
	if (mActiveState.get() == NULL) LOG("[State Manager → getActiveState] There aren't any active state. Maybe, you didn't push one.");
	return mActiveState.get();
}
