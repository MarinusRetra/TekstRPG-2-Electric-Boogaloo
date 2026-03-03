#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

using namespace context;

namespace states
{
	class CharacterSelectionState : public IState<GameContext>
	{

	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;
	private:
		void PrintPlayers(GameContext* p_gameContext) const;
	};

	extern CharacterSelectionState CharacterSelectionStateInstance;
}

#endif 
