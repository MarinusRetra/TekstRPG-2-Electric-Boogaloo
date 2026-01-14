#include <BearLibTerminal.h> // Angled brackets indicate that you use a c++ header file.

using namespace std;


int main() {

    terminal_open();
    terminal_print(1, 1, "Hello, world!");
    // terminal_print(1, 2, to_string(4).c_str()); // BearLibTerminal is a C library so I need to convert the int to a C++ string to then convert it to a C-style string.
                                                   //                    Doesn't look great but this is the best way to do it.

    terminal_refresh();
  
    // Wait until user closes the window
    while (terminal_read() != TK_CLOSE)
    {
        // Game loop
    }
    
    terminal_close();

    return 0;

}
