#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "StateMachine.h"
#include "Themes.h"
#include "Entities.h"
#include <REXSpeeder.h>

namespace context
{
	const int NUM_PLAYER_CHOICES = 4;

	class GameContext 
	{
	public:
		xp::RexImage CurrentMap;

		StateMachine<GameContext> m_StateMachine;

		int CurrentPrintWidth = 0;
		int CurrentPrintHeight = 0;

		bool GameIsRunning = true;
		int Selection = 0;
		int Key = 0;
		
		entities::Entity playerChoices[NUM_PLAYER_CHOICES];
		entities::Entity Player = playerChoices[0];
			
		// This is so i don't have to include gamecontext when i want to get current theme and so I don't need themes when I already have gamecontext.
		themes::Theme& GetCurrentTheme();
		
		GameContext();

		void SwapFontAndLayer(int layerIn);

		//Sets the theme, reprints the border and refreshes the terminal.
		void SetTheme(color_t textColor, color_t backgroundColor, int BorderSymbol1, int BorderSymbol2);
	
		/// <summary>
		/// Sets the border text of the console based on the current theme.
		/// </summary>
		void PrintBorder(int Symbol1, int Symbol2, int w, int h);
	
		void CheckGameClose();

	};

	enum MapLayers { UI, MAP_VISUAL, MAP_INTERACTABLES, NUM_LAYERS };
}

#endif