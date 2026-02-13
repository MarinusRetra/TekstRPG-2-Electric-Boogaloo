#include "Header Files/CombatState.h"
#include <BearLibTerminal.h>
#include <string>

using namespace context;

namespace states
{
    void CombatState::Enter(GameContext* p_gameContext)
    {
        terminal_print(1, 2, "Combat!");
        terminal_refresh();
    }
    
    void CombatState::Update(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_refresh();
    }
    
    void CombatState::Exit(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_refresh();
    }
}
