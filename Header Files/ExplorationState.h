#ifndef EXPLORATIONSTATE_H
#define EXPLORATIONSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

using namespace context;

namespace states
{
	class ExplorationState : public IState<GameContext>
	{
	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;

	private:
		void PrintMap(GameContext* p_gameContext);
	};

	extern ExplorationState ExplorationStateInstance;
}



#endif