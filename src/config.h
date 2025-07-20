#ifndef CONFIG_H
    #define CONFIG_H

// UI

    // Menu
    #define MENU_JOGAR 1
    #define MENU_CONFIGURACOES 2
    #define MENU_INSTRUCOES 3
    #define MENU_RANKING 4
    #define MENU_SAIR 5

    // Limpar tela
    #ifdef _WIN32
        #define CLEAR_SCREEN_CMD "cls"
    #else
        #define CLEAR_SCREEN_CMD "clear"
    #endif


// GAME

    // tamanho do mapa
    #define MAP_SIZE 10

#endif
