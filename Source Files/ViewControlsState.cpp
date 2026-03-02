#include "Header Files/ViewControlsState.h"
#include "BearLibTerminal.h"
#include "Header Files/MenuState.h"

namespace states
{
	const int NUM_CONTROLS = 8;

	ViewControlsState ViewControlsStateInstance;

	ControlText controlsArray[NUM_CONTROLS] = {
		{"Escape", "<Will instantly quit the game at any moment>"},
		{"W, UpArrow", "<Move/Look/Navigate up>"},
		{"A, LeftArrow", "<Move/Look/Navigate left>"},
		{"S, DownArrow", "<Move/Look/Navigate down>"},
		{"D, RightArrow", "<Move/Look/Navigate right>"},
		{"Right-Click, Q", "<Will open and close your inventory when ingame>"},
		{"Left-click, Enter/Return, Z", "<Is for interacting when ingame and is for confirm/submit choices when in menus>" },
		{"Back", " <Press enter now to go back to main>"}
	};

	void ViewControlsState::Enter(GameContext* p_gameContext)
	{
		terminal_set("input.filter = [up, down, return, escape]");
	}

	void ViewControlsState::Update(GameContext* p_gameContext)
	{
		p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
		p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH) - 10;
		terminal_clear();

		p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), p_gameContext->CurrentPrintHeight);
		PrintControls();
		terminal_clear_area(1, 2+p_gameContext->Selection, p_gameContext->CurrentPrintWidth, 1);
		terminal_print_ext(1, 2+p_gameContext->Selection, p_gameContext->CurrentPrintWidth, 2, TK_ALIGN_CENTER, (controlsArray[p_gameContext->Selection].Button + ": " + controlsArray[p_gameContext->Selection].Description).c_str());
		terminal_refresh();

		p_gameContext->Key = terminal_read();
		p_gameContext->CheckGameClose();

		if (p_gameContext->Key == TK_RETURN)
		{
			switch (p_gameContext->Selection)
			{
			case NUM_CONTROLS-1:
				p_gameContext->m_StateMachine.ChangeState(p_gameContext, &MenuStateInstance);
				break;
			default:
				break;
			}
		}

		//TODO: Make this a function with an int as parameter so I don't have to rewrite this in every menu state.
		p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : (p_gameContext->Key == TK_DOWN) ? 1 : 0;
		p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_CONTROLS - 1) ? NUM_CONTROLS - 1 : p_gameContext->Selection;
	}
	
	void ViewControlsState::Exit(GameContext* p_gameContext)
	{
		p_gameContext->Selection = 0;
		terminal_clear();
	}
	
	void ViewControlsState::PrintControls() const
	{
		for (int i = 0; i < NUM_CONTROLS; i++)
		{
			terminal_print_ext(1, 2+i, terminal_state(TK_WIDTH) - 10, 5, TK_ALIGN_CENTER, (controlsArray[i].Button).c_str());
		}
			terminal_print_ext(1, 20, terminal_state(TK_WIDTH) - 10, 5, TK_ALIGN_CENTER, "Currently both Inventory and interaction are not yet implemented.");
	}
}