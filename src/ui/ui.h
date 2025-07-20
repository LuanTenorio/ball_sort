#ifndef UI_H
#define UI_H

    #include "../config.h"

    void clearScreen();
    void showWelcome(char *nickname);
    void enterOption(char *n);
    void showPanel();
    void showMenu(char *option);
    void showMap(char map[MAP_SIZE][MAP_SIZE]);
    void pressEnterToContinue();

#endif 