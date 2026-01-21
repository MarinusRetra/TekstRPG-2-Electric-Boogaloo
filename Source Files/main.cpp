#include <BearLibTerminal.h>
#include "Header Files/GameContext.h"
#include "Header Files/EnemyContext.h"
#include "Header Files/MenuState.h"

using namespace std;

int main() {

    EnemyContext EnemyContext; // Will probably move this somewhere else later.
    GameContext GameContext;

    terminal_open();

    terminal_color(0xffcccccc);
    terminal_bkcolor(0xff222222);

    if (!terminal_set("window: title='Game', size=240x66, fullscreen=true, cellsize='auto';")) // TEMP: I'm just closing the terminal when configuring fails so I can debug properly.
    {
        terminal_close(); //TODO: Change this to inform the user the configurations have failed.
    }

    terminal_clear();
    GameContext.m_StateMachine.ChangeState(&GameContext, &states::MenuStateInstance);

    // Loops until the game toggles off.
    while (GameContext.GameIsRunning)
    {
        GameContext.m_StateMachine.Update(&GameContext);
    }
    terminal_close();

    return 0;
}
