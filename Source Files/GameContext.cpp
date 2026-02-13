#include "Header Files/GameContext.h"
#include "Header Files/Themes.h"
#include <BearLibTerminal.h>
#include <REXSpeeder.h>

namespace context
{
	void GameContext::SetTheme(color_t textColor, color_t backgroundColor, int BorderSymbol1, int BorderSymbol2)
	{
		terminal_color(textColor);
		terminal_bkcolor(backgroundColor);
		terminal_clear();
		PrintBorder(BorderSymbol1, BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
		terminal_refresh();
	}
	
	void GameContext::PrintBorder(int Symbol1, int Symbol2, int w, int h)
	{
		for (int x = 0; x < w; x++)
		{
			terminal_put(x, 0, x % 2 ? Symbol1 : Symbol2);
			terminal_put(x, h - 1, x % 2 ? Symbol1 : Symbol2);
		}
	
		for (int y = 0; y < h; y++)
		{
			terminal_put(0, y, y % 2 ? Symbol1 : Symbol2);
			terminal_put(w - 1, y, y % 2 ? Symbol1 : Symbol2);
		}
	}

	themes::Theme& GameContext::GetCurrentTheme()
	{
		return themes::CurrentTheme;
	}
	
	void GameContext::CheckGameClose()
	{
		if (Key == TK_CLOSE || Key == TK_ESCAPE) // Toggles the game loop when the window gets closed or when escape is pressed.
		{
			GameIsRunning = false;
		}
	}


	void func()
	{
		try
		{
			xp::RexImage currentMap("ResourceFiles/Maps/OverWorld1.xp");
			currentMap.flatten();
		}
		catch (xp::Rexception& e) {
			std::cerr << "Exception! " << e.what() << " [" << e.code << "]" << std::endl;
		}
	}

}