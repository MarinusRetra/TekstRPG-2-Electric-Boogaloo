#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Header Files/StateMachine.h"
#include <BearLibTerminal.h>
#include "Themes.h"

class GameContext 
{
public:
	StateMachine<GameContext> m_StateMachine;

	bool GameIsRunning = true;
	int Selection = 0;
	int Key = 0;

	// This is so i don't have to include gamecontext when i want to get current theme and so I don't need themes when I already have gamecontext.
	themes::Theme& GetCurrentTheme()
	{
		return themes::CurrentTheme;
	}

	//Sets the theme, reprints the border and refreshes the terminal.
	void SetTheme(color_t textColor, color_t backgroundColor, int BorderSymbol1, int BorderSymbol2)
	{
		terminal_color(textColor);
		terminal_bkcolor(backgroundColor);
		terminal_clear();
		PrintBorder(BorderSymbol1, BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_refresh();
	}

	/// <summary>
	/// Sets the border text of the console based on the current theme.
	/// </summary>
	void PrintBorder(int Symbol1, int Symbol2, int w, int h)
	{
		// If the remainder of x divided by 2 is 0 make a full block at the top/bottom.
		for (int x = 0; x < w; x++)
		{
			terminal_put(x, 0, x % 2 ? Symbol1 : Symbol2);
			terminal_put(x, h - 1, x % 2 ? Symbol1 : Symbol2);
		}

		// If the remainder of x divided by 2 is 0 make a full block at the left/right side.
		for (int y = 0; y < h; y++)
		{
			terminal_put(0, y, y % 2 ? Symbol1 : Symbol2);
			terminal_put(w - 1, y, y % 2 ? Symbol1 : Symbol2);
		}
	}

	void CheckGameClose()
	{
		if (Key == TK_CLOSE || Key == TK_ESCAPE) // Toggles the game loop when the window gets closed or when escape is pressed.
		{
			GameIsRunning = false;
		}
	}
};

#endif