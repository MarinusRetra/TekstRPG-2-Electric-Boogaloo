#include "Header Files/MenuState.h"
#include "Header Files/CombatState.h"
#include <BearLibTerminal.h>
#include <string>

namespace states
{
	void MenuState::Enter(GameContext* p_gameContext)
	{
		terminal_clear();
		terminal_print(1, 1, std::to_string(4).c_str()); // BearLibTerminal is a C library so I need to convert the int to a C++ string to then convert it to a C-style string.
		terminal_refresh();
		p_gameContext->m_StateMachine.ChangeState(p_gameContext, &states::CombatStateInstance);
	}

	void MenuState::Update(GameContext* p_gameContext)
	{
		if (terminal_read() == TK_CLOSE) // Toggles the game loop when the window gets closed.
		{
			p_gameContext->GameIsRunning = false;
		}
	}

	void MenuState::Exit(GameContext* p_gameContext)
	{
		//terminal_clear();
		terminal_refresh();
	}
}

