
#include "Header Files/CharacterSelectionState.h"
#include "Header Files/Entities.h"
#include "Header Files/ExplorationState.h"
#include "Header Files/EntitySprites.h"
#include <string>
#include <BearLibTerminal.h>


using namespace context;

namespace states
{
    void CharacterSelectionState::Enter(GameContext* p_gameContext)
    {
        terminal_set("input.filter = [up, down, return, backspace, escape]");
    }

    void CharacterSelectionState::Update(GameContext* p_gameContext)
    {
        p_gameContext->PrintBorder(p_gameContext->GetCurrentTheme().BorderSymbol1, p_gameContext->GetCurrentTheme().BorderSymbol2, terminal_state(TK_WIDTH), p_gameContext->CurrentPrintHeight);
        PrintPlayers(p_gameContext);
        terminal_clear_area(1, p_gameContext->CurrentPrintHeight / 4, p_gameContext->CurrentPrintWidth, 1);
        terminal_print_ext(1, p_gameContext->CurrentPrintHeight / 4, p_gameContext->CurrentPrintWidth, 1, TK_ALIGN_CENTER, p_gameContext->playerChoices[p_gameContext->Selection].Name.c_str());
        terminal_refresh();

        p_gameContext->Key = terminal_read();
        p_gameContext->CheckGameClose();

        if (p_gameContext->Key == TK_RETURN)
        {
            do
            {
                terminal_clear();
                terminal_print_ext(1, (p_gameContext->CurrentPrintHeight / 4) - 1, p_gameContext->CurrentPrintWidth, 1, TK_ALIGN_CENTER, ("Are you sure you want to play as " + p_gameContext->playerChoices[p_gameContext->Selection].Name + "?").c_str());
                terminal_print_ext(1, p_gameContext->CurrentPrintHeight / 4, p_gameContext->CurrentPrintWidth, 4, TK_ALIGN_CENTER, "\nYes(Return)\nNo(Backspace)");
                terminal_refresh();
                p_gameContext->Key = terminal_read();
            } while (p_gameContext->Key != TK_BACKSPACE && p_gameContext->Key != TK_RETURN && p_gameContext->Key != TK_ESCAPE && p_gameContext->Key != TK_CLOSE);
            
            p_gameContext->CheckGameClose();
            
            if (p_gameContext->Key == TK_RETURN)
            {
                p_gameContext->Player = p_gameContext->playerChoices[p_gameContext->Selection];
                p_gameContext->m_StateMachine.ChangeState(p_gameContext, &ExplorationStateInstance);
            }
            else
            {
                terminal_clear();
                return;
            }
        }
        p_gameContext->Selection += (p_gameContext->Key == TK_UP) ? -1 : (p_gameContext->Key == TK_DOWN) ? 1 : 0;
        p_gameContext->Selection = (p_gameContext->Selection < 0) ? 0 : (p_gameContext->Selection > NUM_PLAYER_CHOICES - 1) ? NUM_PLAYER_CHOICES - 1 : p_gameContext->Selection;
    }

    void CharacterSelectionState::Exit(GameContext* p_gameContext)
    {
        terminal_clear();
    }

    void CharacterSelectionState::PrintPlayers(GameContext* p_gameContext) const
    {
        for (int i = 0; i < NUM_PLAYER_CHOICES; i++)
        {
            terminal_print_ext(1, i + 2, terminal_state(TK_WIDTH) - 10, 5, TK_ALIGN_CENTER, p_gameContext->playerChoices[i].Name.c_str());
        }
    }

    CharacterSelectionState CharacterSelectionStateInstance;

}
