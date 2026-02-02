#include "Header Files/SettingsState.h"
#include "Header Files/SettingData.h"
#include <BearLibTerminal.h>
#include <string>

namespace states
{
	void SettingsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape, left, right]");
	}

	void SettingsState::Update(GameContext* p_gameContext)
	{
		gamedata::Slider& _selectedSlider = gamedata::SettingsDataInstance.GetSelectedSlider(p_gameContext->Selection);

		terminal_clear();
		p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_clear_area(1, 8, 237, 2); // Clears the selection text.
		terminal_print_ext(1, 8, 237, 10, TK_ALIGN_CENTER, _selectedSlider.name.c_str());
		terminal_print_ext(1, 9, 237, 10, TK_ALIGN_CENTER,  (_selectedSlider.value == 0) ? "" : std::to_string(_selectedSlider.value).c_str());
		PrintMenu();
		terminal_refresh();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN && p_gameContext->Selection == gamedata::BACK) 
		{
			p_gameContext->m_StateMachine.ChangeState(p_gameContext, p_gameContext->m_StateMachine.GetPreviousState());
			return;
		}

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : (p_gameContext->Key == TK_DOWN) ? 1 : 0;
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > (gamedata::NUM_MAIN_SETTINGS - 1) ? (gamedata::NUM_MAIN_SETTINGS) - 1 : p_gameContext->Selection);

		_selectedSlider.value += (p_gameContext->Key == TK_LEFT) ? -1 : (p_gameContext->Key == TK_RIGHT) ? 1 : 0;
		_selectedSlider.value = (_selectedSlider.value < _selectedSlider.min) ? _selectedSlider.min : (_selectedSlider.value > (_selectedSlider.max) ? (_selectedSlider.max) : _selectedSlider.value);
	}

	void SettingsState::Exit(GameContext* p_gameContext)
	{
		gamedata::SettingsDataInstance.SaveToFile("settings.txt");
		p_gameContext->Selection = 0;
		terminal_clear();
	}

	void SettingsState::PrintMenu()
	{
		for (int i = 0; i < gamedata::NUM_MAIN_SETTINGS-1; i++)
		{
			terminal_print_ext(1, i + 2, 237, 10, TK_ALIGN_CENTER, gamedata::SettingsDataInstance.GetSelectedSlider(i).GetAndUpdateSetting().c_str());
		}
		terminal_print_ext(1, gamedata::NUM_MAIN_SETTINGS+1, 237, 10, TK_ALIGN_CENTER, "Back");
	}
}