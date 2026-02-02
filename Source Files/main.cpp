#include <BearLibTerminal.h>
#include "Header Files/GameContext.h"
#include "Header Files/EnemyContext.h"
#include "Header Files/MenuState.h"
#include "Header Files/Themes.h"
#include "Header Files/SettingData.h"
#include <iostream>

using namespace std;

int main() {

    EnemyContext EnemyContext; // Will probably move this somewhere else later.
    GameContext GameContext;
    terminal_open();

    if (!gamedata::SettingsDataInstance.LoadFromFile("settings.txt"))
    {
        cout << "Loading settings failed creating new settings.txt\n\n";
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
