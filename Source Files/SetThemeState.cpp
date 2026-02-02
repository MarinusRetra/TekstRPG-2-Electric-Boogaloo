#include "Header Files/SetThemeState.h"
#include <string>
#include "Header Files/Themes.h"
#include "Header Files/SettingData.h"
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
		terminal_clear();
		p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_clear_area(1, NUM_THEMES+3, 237, 1);
		terminal_print_ext(1, NUM_THEMES+3, 237, 10, TK_ALIGN_CENTER, themesArray[p_gameContext->Selection].c_str());
		PrintMenu();
		terminal_refresh();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN)
		{
			switch (p_gameContext->Selection) 
			{
			case BACK_TO_MAIN:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
				return;
				break;

			default:
				p_gameContext->GetCurrentTheme() = themes::ThemesInstance.ThemesArray[p_gameContext->Selection];
				p_gameContext->SetTheme(p_gameContext->GetCurrentTheme().TextColor, p_gameContext->GetCurrentTheme().BackgroundColor, p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2);
				terminal_clear();
				break;
			}
			return;
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : 1;
		// Keeps the selection in range.
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_THEMES - 1) ? (NUM_THEMES) - 1 : p_gameContext->Selection;
	}

	void SetThemeState::Exit(GameContext* p_gameContext)
	{
		gamedata::SettingsDataInstance.SaveToFile("settings.txt");
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