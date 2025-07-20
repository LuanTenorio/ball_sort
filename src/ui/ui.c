#include <stdio.h>
#include <stdlib.h>

#include "../config.h"

void clearScreen(){
    system(CLEAR_SCREEN_CMD);
}

void showWelcome(char *nickname){
    clearScreen();
    printf("========================================\n");
    printf("     Bem-vindo(a) ao Jogo Ordemoji!  \n");
    printf("========================================\n\n");
    printf("Informe seu nickname: ");

    scanf("%20s", nickname);
}

void enterOption(char *n){
    printf("Escolha uma opção: ");
    scanf("%c", n);
    clearScreen();
}

void pressEnterToContinue(){
    printf("Pressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
    clearScreen();
}

void showPanel(){
    printf("========================================\n");
    printf("                 Ordemoji               \n");
    printf("========================================\n");
}

void showMenu(char *option){
    showPanel();

    printf("1. Jogar\n");
    printf("2. Configuracoes\n");
    printf("3. Instrucoes\n");
    printf("4. Ranking\n");
    printf("5. Sair\n\n");

    enterOption(option);
    option[0] -= '0';
}

void showMap(char map[MAP_SIZE][MAP_SIZE]) {
    clearScreen();
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        
        printf("\n");
    }
}