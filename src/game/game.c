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
    int curColumn = -1;
    int floor = 0;
    
    while(fgets(c, 2, file)){
        if(c[0] == '\n') continue;

        // Preenche o mapa
        if(lenColumn--){
            map->collumns[curColumn].mojis[lenColumn + floor] = c[0];
            continue;
        }

        // Verifica as linhas e colunas
        int numberOfLines = c[0] - '0';
        int isNumber = numberOfLines >= 0 && numberOfLines < MAP_SIZE;
        floor = MAP_SIZE - numberOfLines;
        
        // Seleciona a quantidade de colunas
        if(isNumber){
            lenColumn = numberOfLines;
            curColumn++;
        }else{
            printf("Arquivo está em um formato inválido.\n");
            exit(1);
        }
        
        // Coloca o valor inicial da coluna
        map->collumns[curColumn].len = numberOfLines;
        map->collumns[curColumn].complete = 0;
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

void removeMojisFromInputColumn(Map *map, int *lenMojis, char selectedMoji) {
    for (int i = MAP_SIZE - map->collumns[map->input].len; i < MAP_SIZE; i++){
        // Se o moji for diferente do selecionado, sai do for
        if(map->collumns[map->input].mojis[i] != selectedMoji) break;

        // Limpa o moji selecionado
        map->collumns[map->input].mojis[i] = '\0';
    }

    map->collumns[map->input].len -= *lenMojis;
}

int getLenMojisFromInputColumn(Map *map, char selectedMoji) {
    int lenMojis = 0;
    for (int i = MAP_SIZE - map->collumns[map->input].len; i < MAP_SIZE; i++){
        if(map->collumns[map->input].mojis[i] != selectedMoji) break;
        
        lenMojis++;
    }

    return lenMojis;
}

void putMojisInOutputColumn(Map *map, int lenMojis, char selectedMoji) {
    int floor = MAP_SIZE - map->collumns[map->output].len - 1; // Posição do primeiro espaço em branco na coluna de saida
    map->collumns[map->output].len += lenMojis;

    while(lenMojis--)
        map->collumns[map->output].mojis[floor-lenMojis] = selectedMoji; // Coloca o moji selecionado na coluna de saida
}

bool isValidSwap(Map *map, int lenMojis) {
    //Verifica se a coluna tem espaco suficiente para receber os mojis
    if(lenMojis + map->collumns[map->output].len > MAP_SIZE) {
        printf("A troca de %d moji(s) de %d para %d não é possível, pois excede o tamanho da coluna.\n", lenMojis, map->input, map->output);
        return 0;
    }

    // Verifica se tem algum elemento na coluna de input
    if(lenMojis == 0) {
        printf("Nenhum moji selecionado para troca.\n");
        return 0;
    }

    return 1;
}

void swapMojis(Map *map) {
    char selectedMoji = map->collumns[map->input].mojis[MAP_SIZE - map->collumns[map->input].len]; // Moji selecionado para troca
    int lenMojis = getLenMojisFromInputColumn(map, selectedMoji);
    
    // Verifica se a troca é válida
    if(!isValidSwap(map, lenMojis)) {
        pressEnterToContinue();
        return;
    }
    
    // Coloca os mojis selecionados na coluna de output
    removeMojisFromInputColumn(map, &lenMojis, selectedMoji);
    putMojisInOutputColumn(map, lenMojis, selectedMoji);
}

void startGame(){
    Map map = {0};

    convertMapToArray(&map);
    
    while(1){
        showMap(&map);

        if(!play(&map.input, &map.output)) continue; // Se a jogada for invalida, joga denovo

        swapMojis(&map);
    }

}
