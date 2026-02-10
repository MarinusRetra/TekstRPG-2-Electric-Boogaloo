#include "Header Files/MenuState.h"
#include "Header Files/SettingsState.h"
#include "Header Files/SetThemeState.h"
#include <Header Files/ExplorationState.h>
#include <BearLibTerminal.h>
#include <string>

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
		p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
		p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH)-10;

		terminal_clear();
		p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), p_gameContext->CurrentPrintHeight);
		terminal_clear_area(1, p_gameContext->CurrentPrintHeight/4, p_gameContext->CurrentPrintWidth, 1);
		terminal_print_ext(1, p_gameContext->CurrentPrintHeight/4, p_gameContext->CurrentPrintWidth, 1, TK_ALIGN_CENTER, (mainMenuChoiceArray[p_gameContext->Selection]).c_str());
		PrintMainMenu();
		terminal_refresh();

	    p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN)
		{
			switch (p_gameContext->Selection)
			{
			case PLAY:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &ExplorationStateInstance);
				break;

			case SETTINGS:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &SettingsStateInstance);
				break;

			case THEMES:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &SetThemeStateInstance);
				break;

			case QUIT:
				p_gameContext->GameIsRunning = false;
				break;

			default:
				terminal_print_ext(1, p_gameContext->CurrentPrintHeight/3, p_gameContext->CurrentPrintWidth, 5, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
				break;
			}
			return;
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : (p_gameContext->Key == TK_DOWN) ? 1 : 0;
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_CHOICHES-1) ? NUM_CHOICHES-1 : p_gameContext->Selection;
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
			terminal_print_ext(1, i+2, terminal_state(TK_WIDTH)-10, 5, TK_ALIGN_CENTER, mainMenuChoiceArray[i].c_str());
		}
		terminal_print_ext(1, terminal_state(TK_HEIGHT)/2, terminal_state(TK_WIDTH)-10, 5, TK_ALIGN_CENTER, "Press 'escape' to instantly quit the game at anytime :D\nPress Alt+Enter to toggle fullscreen. (It does not always scale properly so manually maximise the window and then press Alt+Enter.)");
	}
}

