#ifndef UI_H
#define UI_H

    #include "../config.h"

    void clearScreen();
    void showWelcome(char *nickname);
    void enterOption(char *n);
    void showPanel();
    void showMenu(char *option);
    void showMap(Map *map);
    void pressEnterToContinue();
    void debuggerShowMap(Map *map);

#endif 