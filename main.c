#include "./src/ui/ui.h"
#include "./src/config.c"
#include <stdio.h>

void loop_game() {
    char option;
    while(option != MENU_SAIR) {
        show_menu(&option);
        switch (option){
            case MENU_JOGAR:
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
    show_welcome(nickname);
    loop_game();
    return 0;
}