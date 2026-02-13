#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Header Files/StateMachine.h"
#include "BearLibTerminal.h"
#include "Themes.h"

namespace context
{
	class GameContext 
	{
	public:
		StateMachine<GameContext> m_StateMachine;

		int CurrentPrintWidth = terminal_state(TK_WIDTH);
		int CurrentPrintHeight = terminal_state(TK_HEIGHT);

		bool GameIsRunning = true;
		int Selection = 0;
		int Key = 0;
	
		// This is so i don't have to include gamecontext when i want to get current theme and so I don't need themes when I already have gamecontext.
		themes::Theme& GetCurrentTheme();
	
		//Sets the theme, reprints the border and refreshes the terminal.
		void SetTheme(color_t textColor, color_t backgroundColor, int BorderSymbol1, int BorderSymbol2);
	
		/// <summary>
		/// Sets the border text of the console based on the current theme.
		/// </summary>
		void PrintBorder(int Symbol1, int Symbol2, int w, int h);
	
		void CheckGameClose();
	};

	//extern xp::RexImage currentMap;
}

#endif