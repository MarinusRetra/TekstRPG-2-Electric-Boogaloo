#ifndef VIEWCONTROLSSTATE_H
#define VIEWCONTROLSSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

using namespace context;

namespace states
{
	class ViewControlsState : public IState<GameContext>
	{
	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;
	private:
		void PrintPlayers();
	};

	extern ViewControlsState SetThemeStateInstance;
}

#endif 
