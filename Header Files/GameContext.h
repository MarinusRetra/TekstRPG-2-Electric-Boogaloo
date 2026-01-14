#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Header Files/StateMachine.h"

class GameContext
{
public:
	StateMachine m_StateMachine;
	
	bool GameIsRunning = true;

	bool IsInCombat = false;
};

#endif