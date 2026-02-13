#include "Header Files/ExplorationState.h"
#include <BearLibTerminal.h>
#include <string>

using namespace context;

namespace states
{
    ExplorationState ExplorationStateInstance;

    void ExplorationState::Enter(GameContext* p_gameContext)
    {
        PrintMap(p_gameContext);


        terminal_refresh();
    }
    
    void ExplorationState::Update(GameContext* p_gameContext)
    {
        terminal_clear();

        p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
        p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH) - 10;

        terminal_refresh();
    }
    
    void ExplorationState::Exit(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_refresh();
    }

    void ExplorationState::PrintMap(GameContext* p_gameContext)
    {
        terminal_clear();
        terminal_layer(1);


        p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), p_gameContext->CurrentPrintHeight);

    }
}
