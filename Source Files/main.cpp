#include <BearLibTerminal.h> // Angled brackets indicate that you use a c++ header file.
#include "Header Files/GameContext.h" // "" Are for when a header file is in your project directly.
#include "Header Files/MenuState.h"
using namespace std;


int main() {

    GameContext GameContext;

    GameContext.m_StateMachine.changeState(&GameContext, new MenuState());

    terminal_open();
    // terminal_print(1, 2, to_string(4).c_str()); // BearLibTerminal is a C library so I need to convert the int to a C++ string to then convert it to a C-style string.
  
    // Loops until the game toggles off.
    while (GameContext.GameIsRunning)
    {
        GameContext.m_StateMachine.Update(&GameContext);
    }

    terminal_close();

    return 0;
}
