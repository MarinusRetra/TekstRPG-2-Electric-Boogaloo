#include "Header Files/SetThemeState.h"
#include <string>
#include "Header Files/Themes.h"
#include <BearLibTerminal.h>

namespace states
{
	enum ThemesMenuChoiches { BRIGHT, DARK, DEFAULT, ROCK, GRASS, BACK_TO_MAIN, NUM_THEMES };

	std::string themesArray[NUM_THEMES] = { "Bright", "Dark", "Default", "Rock", "Grass", "Back" };

	void SetThemeState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]");
	}

	void SetThemeState::Update(GameContext* p_gameContext)
	{
		p_gameContext->PrintBorder(p_gameContext->CurrentTheme.BorderSymbol1, p_gameContext->CurrentTheme.BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_clear_area(1, NUM_THEMES+3, 237, 1);
		terminal_print_ext(1, NUM_THEMES+3, 237, 10, TK_ALIGN_CENTER, themesArray[p_gameContext->Selection].c_str());
		PrintMenu();
		terminal_refresh();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN)
		{
			switch (p_gameContext->Selection) {
			case BRIGHT:
				p_gameContext->CurrentTheme = themes::EveryTheme.BrightTheme;
				break;

			case DARK:
				p_gameContext->CurrentTheme = themes::EveryTheme.DarkTheme;
				break;

			case DEFAULT:
				p_gameContext->CurrentTheme = themes::EveryTheme.DefaultTheme;
				break;

			case ROCK:
				p_gameContext->CurrentTheme = themes::EveryTheme.RockTheme;
				break;

			case GRASS:
				p_gameContext->CurrentTheme = themes::EveryTheme.GrassTheme;
				break;

			case BACK_TO_MAIN:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
				return;
				break;

			default:
				terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
				break;
			}
			p_gameContext->SetTheme(p_gameContext->CurrentTheme.TextColor, p_gameContext->CurrentTheme.BackgroundColor, p_gameContext->CurrentTheme.BorderSymbol1, p_gameContext->CurrentTheme.BorderSymbol2);
			terminal_clear();
			return;
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : 1;
		// Keeps the selection in range.
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_THEMES - 1) ? (NUM_THEMES) - 1 : p_gameContext->Selection;
	}

	void SetThemeState::Exit(GameContext* p_gameContext)
	{
		p_gameContext->Selection = 0;
		terminal_clear();
	}

	void SetThemeState::PrintMenu()
	{
		for (int i = 0; i < NUM_THEMES; i++)
		{
			terminal_print_ext(1, i + 2, 237, 10, TK_ALIGN_CENTER, themesArray[i].c_str());
		}
		terminal_refresh();
	}
}