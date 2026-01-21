#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Header Files/StateMachine.h"
#include <BearLibTerminal.h>
struct GameContext
{
	StateMachine<GameContext> m_StateMachine;

	bool GameIsRunning = true;
	int selection = -1;
	int key;


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
		if (key == TK_CLOSE || key == TK_ESCAPE) // Toggles the game loop when the window gets closed or when escape is pressed.
		{
			GameIsRunning = false;
		}
	}
};

#endif