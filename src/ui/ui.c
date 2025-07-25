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

bool nextLevel() {
    clearScreen();
    printf("Deseja passar para o próximo nível? (s/n): ");

    char n;
    scanf(" %c", &n);

    return n == 's' || n == 'S';
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
    for(int i = 0; i < map->lenCollumns; i++){
        printf("Coluna %d: ", i);
        for(int j = 0; j < map->maxHeight; j++){
            int character = map->collumns[i].mojis[j];
            printf(" %c", character == '\0' ? ' ' : character);
        }
        printf("\n");
    }
}

void showColumn(int column, Map *map) {
    printf("Coluna %d: ", column);

    for(int i = 0; i < map->maxHeight; i++) {
        char character = map->collumns[column].mojis[i];
        printf(" %c", character == '\0' ? ' ' : character);
    }
    
    printf("\n");
}

void showMap(Map *map) {
    clearScreen();
    printf("\n\n");

    for (int line = 0; line < map->maxHeight; line++) {
        for (int col = 0; col < map->lenCollumns; col++) {
            char character = map->collumns[col].mojis[line];
            printf(" %c |", character == '\0' ? ' ' : character);
        }
        
        printf("\n");
    }

    for(int i = 0; i < map->lenCollumns; i++) 
        printf(" -  ");
    
    printf("\n");

    for(int i = 0; i < map->lenCollumns; i++) 
        printf(" %d |", i);

    printf("\n\n");
}

void showRanking(Player *players, int numJogadores){
    printf("\n----------------RANKING------------------\n");

    for (int i = 0; i < numJogadores; i++) 
        printf("%d - Nome: %-20s | Score: %d\n", i + 1, players[i].nickname, players[i].score);
    
    printf("-----------------------------------------\n\n");
}

void showConfig(){
    printf("=======================================\n");
    printf("             Configurações             \n");
    printf("=======================================\n\n");
    printf("1 - Zerar Ranking\n");
    printf("2 - Modo Blind (não implementado)\n");
    printf("3 - Editor de Fases (não implementado)\n");
    printf("4 - Voltar ao Menu Principal\n\n");
}