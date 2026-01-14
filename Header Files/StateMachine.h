#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "Header Files/State.h"

class StateMachine
{
public:
	StateMachine()
	{
		mp_currentState = nullptr;
	}

	void changeState(GameContext* p_gameContext, State* p_newState)
	{
		// Before setting a new state clean up the existing one.
		if (mp_currentState)
		{
			mp_currentState->Exit(p_gameContext);
			delete mp_currentState;
		}

		// Set new state.
		mp_currentState = p_newState;

		if (mp_currentState)
		{
			mp_currentState->Enter(p_gameContext);
		}
	}

	void Update(GameContext* p_gameContext)
	{
		if (mp_currentState) // Only update if there actually is a state.
		{
			mp_currentState->Update(p_gameContext);
		}
	}
private:
	State* mp_currentState;
};

#endif