#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../ui/ui.h"
#include "../config.h"

void convertMapToArray(Map *map) {
    if(access("entrada.txt", F_OK)) {
        printf("Arquivo de entrada não encontrado.\n");
        exit(1);
        return;
    }
    
    FILE *file = fopen("entrada.txt", "r");
    char c[2];
    int lenColumn = 0;
    int curLine = 0;
    int floor = 0;
    
    while(fgets(c, 2, file)){
        if(c[0] == '\n') continue;

        // Preenche o mapa
        if(lenColumn--){
            map->collumns[curLine].mojis[lenColumn + floor] = c[0];
            continue;
        }

        // Verifica as linhas e colunas
        int numberOfLines = c[0] - '0';
        int isNumber = numberOfLines >= 0 && numberOfLines < MAP_SIZE;
        floor = MAP_SIZE - numberOfLines;
        map->collumns[curLine].len = numberOfLines;
        map->collumns[curLine].complete = 0;

        if(isNumber){
            lenColumn = numberOfLines;
            curLine++;
        }else{
            printf("Arquivo está em um formato inválido.\n");
            exit(1);
        }
    }

    fclose(file);
}

// Melhorar tratamento de erros
bool play(int *input, int *output) {
    printf("Informe a coluna de origem (0-%d): ", MAP_SIZE - 1);

    char inputChar, outputChar;

    scanf(" %c", &inputChar);

    int numChar = inputChar - '0';

    if(numChar < 0 || numChar >= MAP_SIZE) {
        printf("Coluna invalida, tente novamente.\n");
        pressEnterToContinue();
        return 0;
    }

    *input = numChar;

    printf("Informe a coluna de destino (0-%d): ", MAP_SIZE - 1);
    scanf(" %c", &outputChar);

    numChar = outputChar - '0';

    if(numChar < 0 || numChar >= MAP_SIZE || numChar == inputChar - '0') {
        printf("Coluna invalida, tente novamente.\n");
        pressEnterToContinue();
        return 0;
    }

    *output = numChar;

    return 1;
}

void startGame(){
    Map map = {0};
    int input, output;

    convertMapToArray(&map);

    while(1){
        showMap(&map);

        if(!play(&input, &output)) continue; // Se a jogada for invalida, joga denovo
    }

}
