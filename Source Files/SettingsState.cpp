#include "Header Files/SettingsState.h"
#include <BearLibTerminal.h>
#include <string>

namespace states
{
	enum SettingsMenuChoices {GAME_SOUND_EFFECTS, MUSIC, MENU_SOUNDS, BACK, NUM_MAIN_SETTINGS};

	std::string mainSettings[NUM_MAIN_SETTINGS] = { "General sound effects", "Music", "Menu Sound effects", "Back" };

	void SettingsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]");
	}

	void SettingsState::Update(GameContext* p_gameContext)
	{
		p_gameContext->PrintBorder(p_gameContext->CurrentTheme.BorderSymbol1, p_gameContext->CurrentTheme.BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		
		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER,  mainSettings[p_gameContext->Selection].c_str());

		PrintMenu();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN) 
		{
			switch (p_gameContext->Selection) {
			case GAME_SOUND_EFFECTS:
				break;

			case MUSIC:
				break;

			case MENU_SOUNDS:
				break;

			case BACK:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
				break;

			default:
				terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
				break;
			}
			return;
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : 1;
		
		// Keeps the selection in range.
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > (NUM_MAIN_SETTINGS - 1) ? (NUM_MAIN_SETTINGS) - 1 : p_gameContext->Selection);

		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER, mainSettings[p_gameContext->Selection].c_str());
	}

	void SettingsState::Exit(GameContext* p_gameContext)
	{
		p_gameContext->Selection = 0;
		terminal_clear();
	}

	void SettingsState::PrintMenu()
	{
		for (int i = 0; i < NUM_MAIN_SETTINGS; i++)
		{
			terminal_print_ext(1, i + 2, 237, 10, TK_ALIGN_CENTER, mainSettings[i].c_str());
		}
		terminal_refresh();
	}
}