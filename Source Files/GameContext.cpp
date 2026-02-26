#include "Header Files/GameContext.h"
#include "BearLibTerminal.h"

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

	void GameContext::SwapFontAndLayer(int layerIn)
	{
		terminal_layer(layerIn);

		switch (layerIn)
		{
		case (UI):
			terminal_set("font: Fonts/cp437_16x16.png, size=16x16, codepage=437");
			break;
		case (MAP_VISUAL):
			terminal_set("font: Fonts/Monochrome_ReReRePacked.png, size=16x16, layout=16x352, codepage=Fonts/Monochrome_ReReRePacked_codepage.txt");
			break;
		case (MAP_COLLISION):
			terminal_set("font: Fonts/Monochrome_ReReRePacked.png, size=16x16, layout=16x352, codepage=Fonts/Monochrome_ReReRePacked_codepage.txt");
			break;
		case (MAP_INTERACTABLES): //MAP_INTERACTABLES Might become something different later, not sure how to implement it yet.
			terminal_set("font: Fonts/Monochrome_ReReRePacked.png, size=16x16, layout=16x352, codepage=Fonts/Monochrome_ReReRePacked_codepage.txt");
			break;
		default:
			break;
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

	GameContext::GameContext() : currentMap("Maps/OverWorld1.xp")
	{}
}