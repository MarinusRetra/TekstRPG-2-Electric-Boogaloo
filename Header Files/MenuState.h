#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "Header Files/State.h"
#include "Header Files/GameContext.h"
#include <BearLibTerminal.h>

class MenuState : public State
{
public:
	void Update(GameContext* p_gameContext) override
	{
		if (terminal_read() == TK_CLOSE)
		{
			p_gameContext->GameIsRunning = false;
		}

		//Menu logic
		terminal_refresh();
	}
};

#endif 
