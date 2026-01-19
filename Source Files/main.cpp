#include <BearLibTerminal.h>
#include "Header Files/GameContext.h"
#include "Header Files/EnemyContext.h"
#include "Header Files/MenuState.h"

using namespace std;

int main() {
    EnemyContext EnemyContext; // Will probably move this somewhere else later.
    GameContext GameContext;

    terminal_open();

    GameContext.m_StateMachine.ChangeState(&GameContext, &states::MenuStateInstance);
  
    // Loops until the game toggles off.
    while (GameContext.GameIsRunning)
    {
        GameContext.m_StateMachine.Update(&GameContext);
    }
    // TODO: Add restart or go back to main menu prompt.
    terminal_close();

    return 0;
}
