#include "Header Files/ViewControlsState.h"
#include "BearLibTerminal.h"

namespace states
{
	//TODO: Define these variables in the header files as members instead.
	const int NUM_CONTROLS = 7;

	struct ControlText
	{
		std::string Button;
		std::string Description;
	};

	ControlText controlsArray[NUM_CONTROLS] = {
		{"Escape: ", "Will instantly quit the game at any moment."},
		{"W, UpArrow: ", "Move/Look/Navigate up."},
		{"A, LeftArrow: ", "Move/Look/Navigate left."},
		{"S, DownArrow: ", "Move/Look/Navigate down."},
		{"D, RightArrow: ", "Move/Look/Navigate right."},
		{"Right-Click, Q: ", "Will open and close your inventory when ingame."},
		{"Left-click, Enter/Return, Z: ", "Interact when ingame. Confirm/Submit choices when in a menu." },
	};

	void ViewControlsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, escape]");
	}
	void ViewControlsState::Update(GameContext* p_gameContext)
	{
		p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
		p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH) - 10;

		p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), p_gameContext->CurrentPrintHeight);
		PrintPlayers();
		terminal_clear_area(1, p_gameContext->CurrentPrintHeight / 4, p_gameContext->CurrentPrintWidth, 1);
		terminal_print_ext(1, p_gameContext->CurrentPrintHeight / 4, p_gameContext->CurrentPrintWidth, 1, TK_ALIGN_CENTER, controlsArray[p_gameContext->Selection].Description.c_str());
		terminal_refresh();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();
		terminal_refresh();

		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : (p_gameContext->Key == TK_DOWN) ? 1 : 0;
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_CONTROLS - 1) ? NUM_CONTROLS - 1 : p_gameContext->Selection;
	}
	
	void ViewControlsState::Exit(GameContext* p_gameContext)
	{
		terminal_clear();
	}
	
	void ViewControlsState::PrintPlayers()
	{
		for (int i = 0; i < NUM_CONTROLS; i++)
		{
			terminal_print_ext(1, 2+i, terminal_state(TK_WIDTH) - 10, 5, TK_ALIGN_CENTER, controlsArray[i].Button.c_str());
		}
	}
}