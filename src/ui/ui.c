#include <stdio.h>
#include <stdlib.h>

#include "../config.h"

// Sempre chamar ao printar ao novo na tela e nunca depois de finalizar uma operação
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
    scanf(" %c", n);
    clearScreen();
}

void pressEnterToContinue(){
    printf("Pressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
}

void showPanel(){
    printf("========================================\n");
    printf("                 Ordemoji               \n");
    printf("========================================\n");
}

void showMenu(char *option){
    clearScreen();
    showPanel();

    printf("1. Jogar\n");
    printf("2. Configuracoes\n");
    printf("3. Instrucoes\n");
    printf("4. Ranking\n");
    printf("5. Sair\n\n");

    enterOption(option);
    option[0] -= '0';
}

void debuggerShowMap(Map *map){
    for(int i = 0; i < MAP_SIZE; i++){
        printf("Coluna %d: ", i);
        for(int j = 0; j < MAP_SIZE; j++){
            int character = map->collumns[i].mojis[j];
            printf(" %c", character == '\0' ? ' ' : character);
        }
        printf("\n");
    }
}

void showColumn(int column, Map *map) {
    printf("Coluna %d: ", column);

    for(int i = 0; i < MAP_SIZE; i++) {
        char character = map->collumns[column].mojis[i];
        printf(" %c", character == '\0' ? ' ' : character);
    }
    
    printf("\n");
}

void showMap(Map *map) {
    clearScreen();
    printf("\n\n");

    for (int line = 0; line < MAP_SIZE; line++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            char character = map->collumns[col].mojis[line];
            printf(" %c |", character == '\0' ? ' ' : character);
        }
        
        printf("\n");
    }

    printf(" -   -   -   -   -   -   -   -   -   -\n");

    for(int i = 0; i < MAP_SIZE; i++) {
        printf(" %d |", i);
    }

    printf("\n\n");
}