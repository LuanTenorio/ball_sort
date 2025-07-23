#ifndef CONFIG_H
    #define CONFIG_H

    typedef enum { false, true } bool;

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

    typedef struct Collumn{
        char *mojis;
        int len;
        bool complete;
    } Collumn;

    typedef struct Map{
        Collumn *collumns;
        int input;
        int output;
        int maxHeight;
        int lenCollumns;
        int totalCompleteColumns;
        int lenVoidCollumns;
    } Map;

    typedef struct Maps{
        Map *maps;
        int count;
    } Maps;

#endif
