#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Header Files/StateMachine.h"
#include <BearLibTerminal.h>
struct GameContext
{
	StateMachine<GameContext> m_StateMachine;

	bool GameIsRunning = true;
};

#endif