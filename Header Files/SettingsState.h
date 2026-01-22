#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

namespace states
{
	class SettingsState : public IState<GameContext>
	{
	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;

		/// <summary>
		/// Decides what settings will be opened
		/// 0 = MAINSETTINGS, 1 = THEMES
		/// </summary>
		/// <param name="mode"> </param>
		void SetSettingsMode(int mode);
	private:
		void PrintMainSettingsMenu();
		void PrintThemesMenu();
		void LoadSettings();
	};

	static SettingsState SettingsStateInstance;
}

#endif 
