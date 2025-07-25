#include <stdio.h>

#include "./src/ui/ui.h"
#include "./src/config.h"
#include "./src/game/game.h"
#include "./src/game/map.h"
#include "./src/ranking/ranking.h"

int loopGame() {
    char option;
    Maps *maps = loadAllMaps("entrada.txt");
    int curLevel = 1;

    while(option != MENU_SAIR) {
        showMenu(&option);
        switch (option){
            case MENU_JOGAR:
                playGame(maps, &curLevel);
                break;
            case MENU_CONFIGURACOES:
                openConfig();
                break;
            case MENU_INSTRUCOES:
                showInstructions();
                break;
            case MENU_RANKING:
                readRanking();
                pressEnterToContinue();
                break;
        }
    }

    freeMaps(maps);
    return curLevel * (curLevel + 1) / 2;
}

int main(){
    Player player = {0};
    
    showWelcome(player.nickname);
    
    player.score = loopGame();
    pushPlayer(&player);

    return 0;
}