#include <BearLibTerminal.h>

int main() {
    int key = 0;
    const char* msg = "Hello BLT";

    terminal_open();
    // Coordinaten in BearLibTerminal 0,0 is rechtsboven x is van links naar rechts
    // Y is van boven naarbeneden. (Helemaal boven is dus 0) 
    terminal_print(0,0, msg);
    terminal_refresh();
    //terminal_close();
    return 0;

    // Gameplay loop = meerdere while loops die op basis van een enum gameState
    // Bepalen welke logica gebeurt en de gameState wordt gezet vanuit een SetState functie
    // er zijn functies voor alle gameplay loops die bij elke functie call 1 iteratie van gameplay uitvoeren
    
}
