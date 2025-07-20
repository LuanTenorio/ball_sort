#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../ui/ui.h"
#include "../config.h"

void convertMapToArray(char map[MAP_SIZE][MAP_SIZE]) {
    if(access("entrada.txt", F_OK)) {
        printf("Arquivo de entrada não encontrado.\n");
        exit(1);
        return;
    }
    
    FILE *file = fopen("entrada.txt", "r");
    char c[2];
    int lenColumn = 0;
    int curLine = 0;

    while(fgets(c, 2, file)){
        if(c[0] == '\n') continue;

        // Preenche o mapa
        if(lenColumn--){
            map[curLine][lenColumn] = c[0];
            continue;
        }

        // Verifica as linhas e colunas
        int numberOfColumns = c[0] - '0';
        int isNumber = numberOfColumns >= 0 && numberOfColumns <= 9;

        if(isNumber){
            lenColumn = numberOfColumns;
            curLine++;
        }else{
            printf("Arquivo está em um formato inválido.\n");
            exit(1);
        }
    }

    fclose(file);
}

void startGame(){
    char map[MAP_SIZE][MAP_SIZE] = {0};

    convertMapToArray(map);
    showMap(map);
    pressEnterToContinue();
}
