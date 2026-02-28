#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

using namespace context;

namespace states
{
	// This is declared outside the class so I can use this inside a switch statement for player selection.
	const int NUM_PLAYER_CHOICES = 4; 

	class CharacterSelectionState : public IState<GameContext>
	{

	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;
	private:
		void PrintPlayers() const;
	};

	extern CharacterSelectionState CharacterSelectionStateInstance;
}

#endif 
