#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR_SCREEN_CMD "cls"
#else
    #define CLEAR_SCREEN_CMD "clear"
#endif

void clear_screen(){
    system(CLEAR_SCREEN_CMD);
}

void show_welcome(char *nickname){
    clear_screen();
    printf("========================================\n");
    printf("     Bem-vindo(a) ao Jogo Ordemoji!  \n");
    printf("========================================\n\n");
    printf("Informe seu nickname: ");

    scanf("%20s", nickname);
}

void enter_option(char *n){
    printf("Escolha uma opção: ");
    scanf("%c", n);
}

void show_panel(){
    printf("========================================\n");
    printf("                 Ordemoji               \n");
    printf("========================================\n");
}

void show_menu(char *option){
    clear_screen();
    show_panel();

    printf("1. Jogar\n");
    printf("2. Configuracoes\n");
    printf("3. Instrucoes\n");
    printf("4. Ranking\n");
    printf("5. Sair\n\n");

    enter_option(option);
    option[0] -= '0';
}
