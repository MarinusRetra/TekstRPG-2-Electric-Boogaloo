#ifndef COMBATSTATE_H
#define COMBATSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"

using namespace context;

namespace states
{
    class CombatState : public IState<GameContext>
    {
    public:
        void Enter(GameContext* p_gameContext) override;
    
        void Update(GameContext* p_gameContext) override;
    
        void Exit(GameContext* p_gameContext) override;
    };

    static CombatState CombatStateInstance;
}
#endif