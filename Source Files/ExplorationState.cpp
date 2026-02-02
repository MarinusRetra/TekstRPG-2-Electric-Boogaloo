#include "Header Files/ExplorationState.h"
#include <REXSpeeder.h>
#include <BearLibTerminal.h>
#include <string>

namespace states
{
    void ExplorationState::Enter(GameContext* p_gameContext)
    {
        terminal_clear();
        p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));

        xp::Rexception;

        terminal_refresh();
    }
    
    void ExplorationState::Update(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_refresh();
    }
    
    void ExplorationState::Exit(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_refresh();
    }
}
