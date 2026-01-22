#include "Header Files/MenuState.h"
#include "Header Files/SettingsState.h"
#include <BearLibTerminal.h>
#include <string>
#include "Header Files/BigString.h"

namespace states
{
	enum MainMenuChoices{ PLAY, SETTINGS, THEMES, QUIT, NUM_CHOICHES };

	std::string mainMenuChoiceArray[NUM_CHOICHES] = { "Play","Settings","Themes","Quit" };
	
	void MenuState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]"); 
	}
	
	void MenuState::Update(GameContext* p_gameContext)
	{
		terminal_refresh();

		p_gameContext->PrintBorder(p_gameContext->CurrentTheme.BorderSymbol1, p_gameContext->CurrentTheme.BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER, (mainMenuChoiceArray[p_gameContext->Selection]).c_str());
		PrintMainMenu();

	    p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN)
		{
			switch (p_gameContext->Selection)
			{
			case PLAY:
				
				break;

			case SETTINGS:
				SettingsStateInstance.SetSettingsMode(0);
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &SettingsStateInstance);
				return;
				break;

			case THEMES:
				SettingsStateInstance.SetSettingsMode(1);
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &SettingsStateInstance);
				return;
				break;

			case QUIT:
				p_gameContext->GameIsRunning = false;
				return;
				break;

			default:
				terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
				break;
			}
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : 1;
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_CHOICHES-1) ? NUM_CHOICHES-1 : p_gameContext->Selection;

		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER, (mainMenuChoiceArray[p_gameContext->Selection]).c_str());
	}
	
	void MenuState::Exit(GameContext* p_gameContext)
	{
		p_gameContext->Selection = 0;
		terminal_clear();
	}

	void MenuState::PrintMainMenu()
	{	
		for (int i = 0; i < NUM_CHOICHES; i++)
		{
			terminal_print_ext(1, i+2, 237,10,TK_ALIGN_CENTER, mainMenuChoiceArray[i].c_str());
		}
		terminal_print_ext(1, 45, 237, 10, TK_ALIGN_CENTER, "Press 'escape' to instantly quit the game at anytime :D");
		terminal_refresh();
	}
}

