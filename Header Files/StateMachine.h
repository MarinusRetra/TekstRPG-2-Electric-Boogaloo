#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "Header Files/IState.h"

template<typename ContextType>
class StateMachine
{
public:
	void ChangeState(ContextType* p_context, IState<ContextType>* p_newState)
	{
		if (p_newState == mp_currentState) return;

		// Before setting a new state clean up the existing one.
		if (mp_currentState)
		{
			mp_currentState->Exit(p_context);
		}

		// Set and enter the new state.
		mp_previousState = mp_currentState;
		mp_currentState = p_newState;

		if (mp_currentState)
		{
			mp_currentState->Enter(p_context);
		}
	}

	void Update(ContextType* p_context)
	{
		if (mp_currentState)
		{
			mp_currentState->Update(p_context);
		}
	}
	// Don't use this for calling functions, just use this as read only.
	IState<ContextType>* GetPreviousState() const 
	{
		return mp_previousState;
	}

private:
	IState<ContextType>* mp_currentState = nullptr;
	IState<ContextType>* mp_previousState = nullptr;
};

#endif