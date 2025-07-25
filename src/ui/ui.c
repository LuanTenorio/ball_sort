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

void showInstructions(){
    printf("*** INSTRUCOES SOBRE O ORDERMOJI  ***\n\n");

    printf("Bem-vindo ao OrderMoji! O seu desafio é organizar os simbolos em colunas.\n\n");

    printf(">> OBJETIVO DO JOGO:\n");
    printf("O objetivo principal é ordenar todos os itens (representados por caracteres como '#', '@', '*', etc.) de forma que cada coluna contenha apenas simbolos iguais.\n");
    printf("Uma coluna é considerada 'fechada' ou completa quando está totalmente preenchida com itens idênticos.\n");
    printf("O jogo é vencido quando todas as colunas possíveis estiverem completas.\n\n");

    printf(">> COMO JOGAR:\n");
    printf("1. Na sua vez, você será solicitado a informar a 'coluna de origem' e a 'coluna de destino'.\n");
    printf("2. As colunas são numeradas, e você deve digitar o número correspondente para fazer sua jogada.\n\n");

    printf(">> REGRAS PARA MOVIMENTOS:\n");
    printf("Para que um movimento seja válido, as seguintes condições devem ser respeitadas:\n");
    printf("- So é possivel mover o item que está no topo de uma coluna.\n");
    printf("- Um item so pode ser movido para uma coluna de destino que esteja vazia ou cujo item no topo seja idêntico ao item que está sendo movido.\n");
    printf("- Uma coluna de destino não pode receber mais itens do que sua capacidade máxima.\n");
    printf("- Ao mover um item, todos os outros itens iguais e adjacentes no topo da coluna de origem serão movidos juntos, desde que haja espaço na coluna de destino.\n");
    printf("- Se uma jogada for inválida, uma mensagem será exibida.\n\n");

    printf(">> FASES E EVOLUCAO:\n");
    printf("O jogo é dividido em fases, carregadas de um arquivo. \n");
    printf("O jogo termina quando todas as fases do arquivo forem concluídas.\n\n");

    printf(">> PONTUACAO:\n");
    printf("Sua pontuação é a soma de todos os níveis que você alcançou.\n");
    printf("A cada fase concluída com sucesso, seu nível aumenta.\n");
    printf("Ao final da partida (seja por concluir todas as fases ou por sair antes), sua pontuação e seu nickname serão salvos no ranking.\n\n");

    pressEnterToContinue();
}
