#include "Header Files/SettingsState.h"
#include "Header Files/MenuState.h"
#include <BearLibTerminal.h>
#include <string>

namespace states
{
	enum SettingsMode {MAINSETTINGS, THEMES, NUM_MODES};
	enum SettingsMenuChoices {GAME_SOUND_EFFECTS, MUSIC, MENU_SOUNDS, BACK, NUM_MAIN_SETTINGS};
	enum ThemesMenuChoiches {BRIGHT, DARK, DEFAULT, ROCK, GRASS ,BACK_TO_MAIN, NUM_THEMES};
	int settingsMode = MAINSETTINGS;

	std::string mainSettings[NUM_MAIN_SETTINGS] = { "General sound effects","Music","Menu Sound effects","Back" };
	std::string themesArray[NUM_THEMES] = { "Bright", "Dark", "Default", "Rock", "Grass", "Back"};


	void SettingsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]");
	}

	void SettingsState::Update(GameContext* p_gameContext)
	{
		p_gameContext->PrintBorder(0x2588, '#', terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		
		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER,  (settingsMode == MAINSETTINGS) ? mainSettings[p_gameContext->selection].c_str() : themesArray[p_gameContext->selection].c_str());

		LoadSettings();

		p_gameContext->key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->key == TK_RETURN) 
		{
			if (settingsMode == MAINSETTINGS) 
			{
				switch (p_gameContext->selection) {
				case GAME_SOUND_EFFECTS:

					break;

				case MUSIC:

					break;

				case MENU_SOUNDS:

					break;

				case BACK:
					p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
					return;
					break;

				default:
					terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
					break;
				}
			}
			else {
				switch (p_gameContext->selection) {
				case BRIGHT:

					break;
				case DARK:

					break;
				case DEFAULT:

					break;
				case ROCK:

					break;
				case GRASS:

					break;
				case BACK_TO_MAIN:
					p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
					return;
					break;
				default:
					terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\nYou are selecting a choice that does not exist.");
					break;
				}
			}
		}

		p_gameContext->selection += (p_gameContext->key == TK_UP) ? -1 : 1;
		
		// Don't worry about it.
		p_gameContext->selection = (p_gameContext->selection < 0) ? 0 : (p_gameContext->selection > ((settingsMode == MAINSETTINGS) ? NUM_MAIN_SETTINGS : NUM_THEMES) - 1) ? ((settingsMode == MAINSETTINGS) ? NUM_MAIN_SETTINGS : NUM_THEMES) - 1 : p_gameContext->selection;

		terminal_clear_area(1, 8, 237, 1);
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER, (settingsMode == MAINSETTINGS) ? mainSettings[p_gameContext->selection].c_str() : themesArray[p_gameContext->selection].c_str());
	}

	void SettingsState::Exit(GameContext* p_gameContext)
	{
		p_gameContext->selection = 0;
		terminal_clear();
	}

	void SettingsState::SetSettingsMode(int modeIn)
	{
		settingsMode = modeIn;
		LoadSettings();
	}

	void SettingsState::PrintMainSettingsMenu()
	{
		for (int i = 0; i < NUM_MAIN_SETTINGS; i++)
		{
			terminal_print_ext(1, i + 2, 237, 10, TK_ALIGN_CENTER, mainSettings[i].c_str());
		}
		terminal_refresh();
	}

	void SettingsState::PrintThemesMenu()
	{
		for (int i = 0; i < NUM_THEMES; i++)
		{
			terminal_print_ext(1, i + 2, 237, 10, TK_ALIGN_CENTER, themesArray[i].c_str());
		}
		terminal_refresh();
	}

	void SettingsState::LoadSettings()
	{
		switch (settingsMode) {
			case MAINSETTINGS:
				PrintMainSettingsMenu();
			break;

			case THEMES:
				PrintThemesMenu();
			break;

			default:
				terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\n A settings page that does not exist just tried to open");
				//TODO: Make this appear on another layer and swap it with the current visible layer then swap it back a couple seconds later.
			break;
		}
		terminal_refresh();
	}
}