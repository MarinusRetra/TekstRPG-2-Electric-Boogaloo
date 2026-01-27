#include <BearLibTerminal.h>
#include "Header Files/GameContext.h"
#include "Header Files/EnemyContext.h"
#include "Header Files/MenuState.h"
#include "Header Files/Themes.h"
#include "Header Files/SettingData.h"

using namespace std;

int main() {

    EnemyContext EnemyContext; // Will probably move this somewhere else later.
    GameContext GameContext;
    
    terminal_open();
    if (!terminal_set("window: title='Game', size=240x66, fullscreen=true, cellsize='auto';")) // TEMP: I'm just closing the terminal when configuring fails so I can debug properly.
    {
        terminal_close(); //TODO: Change this to inform the user the configurations have failed.
    }

    if (!gamedata::SettingsDataInstance.LoadFromFile("settings.txt"))
    {
        gamedata::SettingsDataInstance.SaveToFile("settings.txt");
    }
    
    GameContext.SetTheme(GameContext.GetCurrentTheme().TextColor, GameContext.GetCurrentTheme().BackgroundColor, GameContext.GetCurrentTheme().BorderSymbol1, GameContext.GetCurrentTheme().BorderSymbol2);
    terminal_print_ext(1, 15, 237, 10, TK_ALIGN_CENTER, GameContext.GetCurrentTheme().name.c_str());

    GameContext.m_StateMachine.ChangeState(&GameContext, &states::MenuStateInstance);

    // Loops until the game toggles off.
    while (GameContext.GameIsRunning)
    {
        GameContext.m_StateMachine.Update(&GameContext);
    }
    terminal_close();

    return 0;
}
