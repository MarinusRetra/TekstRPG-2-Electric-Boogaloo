#include "Header Files/SettingsState.h"
#include "Header Files/MenuState.h"
#include <BearLibTerminal.h>
#include <string>

namespace states
{
	enum SettingsMode {MAINSETTINGS, THEMES, INGAME, NUM_MODES};
	enum SettingsMenuChoices {GAME_SOUND_EFFECTS, MUSIC, MENU_SOUNDS, BACK, NUM_SETTINGS};
	int settingsMode = MAINSETTINGS;

	void SettingsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]");

		switch (settingsMode)
		{
		case MAINSETTINGS:
			PrintMainSettingsMenu();
			break;
		case THEMES:
			PrintThemesMenu();
			break;
			PrintIngameMenu();
		case INGAME:
			break;
		default:
			terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "If you are reading this I messed up :)\n A settings page that does not exist just tried to open");
			//TODO: Make this appear on another layer and swap it with the current visible layer then swap it back a couple seconds later.
			break;
		}
	}

	void SettingsState::Update(GameContext* p_gameContext)
	{
		p_gameContext->key = terminal_read();
		p_gameContext->CheckGameClose();
	}

	void SettingsState::Exit(GameContext* p_gameContext)
	{

	}

	void SettingsState::SetSettingsMode(int modeIn)
	{
		settingsMode = modeIn;
	}

	void SettingsState::PrintMainSettingsMenu()
	{
		terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "MainSettingsMenu");
		terminal_refresh();

	}
	void SettingsState::PrintThemesMenu()
	{
		terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "ThemesMenu");
		terminal_refresh();
	}
	void SettingsState::PrintIngameMenu()
	{
		terminal_print_ext(1, 30, 237, 10, TK_ALIGN_CENTER, "IngameMenu");
		terminal_refresh();
		// TODO: Make ingame menu.
	}
}