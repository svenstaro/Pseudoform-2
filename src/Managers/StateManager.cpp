#include "Managers/StateManager.hpp"

void StateManager::push(State *state)
{
    mStates.push_back(StatePtr(state));
}

void StateManager::update()
{
    if (mActiveState.get() == NULL) this->pop();

    if (mAdvanceState)
    {
        mActiveState.get()->shutdown();
        LOG_META(FORMAT(" Exiting from '%1%'", mActiveState.get()->type()));
        setAdvanceState(false);
        this->pop();
    }
    else
    {
        mActiveState.get()->update();
    }
}

StateManager::StateManager(): mAdvanceState(false) { }

StateManager::~StateManager()
{
    while (!mStates.empty())
    {
        mStates.pop_back();
    }
}

void StateManager::setAdvanceState(bool advance)
{
    mAdvanceState = advance;
}

State *StateManager::pop()
{
    if (mStates.empty()) LOG_META("There aren't any states now. Maybe, you didn't push one.");

    mActiveState = mStates.front();	// Store pointer for next state to use
    mStates.pop_front();     		// And remove it from list

    LOG_META(FORMAT(" Activating '%1%'", mActiveState.get()->type()));
    mActiveState.get()->init();

    return mActiveState.get();
}

State *StateManager::getActiveState()
{
    if (mActiveState.get() == NULL) LOG_META("There is no active state. Maybe, you didn't push one.");
    return mActiveState.get();
}
