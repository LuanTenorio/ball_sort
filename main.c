#include <stdio.h>

#include "./src/ui/ui.h"
#include "./src/config.h"
#include "./src/game/game.h"

void loopGame() {
    char option;
    int numMaps;
    Map *maps = loadAllMaps("entrada.txt", &numMaps);

    while(option != MENU_SAIR) {
        showMenu(&option);
        switch (option){
            case MENU_JOGAR:
                startGame(&maps[0]);
                break;
            case MENU_CONFIGURACOES:
                break;
            case MENU_INSTRUCOES:
                break;
            case MENU_RANKING:
                break;
        }
    }
}

int main(){
    char nickname[21]; // Não faz nada ainda
    showWelcome(nickname);
    loopGame();
    return 0;
}