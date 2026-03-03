#ifndef EXPLORATIONSTATE_H
#define EXPLORATIONSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"
#include "Header Files/Entities.h"
#include "Header Files/GameUtility.h"

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
		void PrintMap(GameContext* p_gameContext, xp::RexImage&);
		void MovePlayer(GameContext* p_gameContext, game_utility::Vector2<int> directionIn);
		void SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn);
		void SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn, int spawnPosXIn, int spawnPosYIn);
	};

	extern ExplorationState ExplorationStateInstance;
}

#endif