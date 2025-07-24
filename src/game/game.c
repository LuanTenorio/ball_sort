#include <stdio.h>

#include "../ui/ui.h"
#include "../config.h"

// Melhorar tratamento de erros
bool play(Map *map) {
    printf("Informe a coluna de origem (0-%d): ", map->lenCollumns - 1);
    
    char inputChar, outputChar;

    scanf(" %c", &inputChar);

    int numChar = inputChar - '0';

    if(numChar < 0 || numChar >= map->lenCollumns) {
        printf("Coluna invalida, tente novamente.\n");
        pressEnterToContinue();
        return false;
    }

    map->input = numChar;

    printf("Informe a coluna de destino (0-%d): ", map->lenCollumns - 1);
    scanf(" %c", &outputChar);

    numChar = outputChar - '0';

    if(numChar < 0 || numChar >= map->lenCollumns || outputChar == inputChar) {
        printf("Coluna invalida, tente novamente.\n");
        pressEnterToContinue();
        return false;
    }

    map->output = numChar;

    return true;
}

void removeMojisFromInputColumn(Map *map, int *lenMojis, char selectedMoji) {
    for (int i = map->maxHeight - map->collumns[map->input].len; i < map->maxHeight; i++){
        // Se o moji for diferente do selecionado, sai do for
        if(map->collumns[map->input].mojis[i] != selectedMoji) break;

        // Limpa o moji selecionado
        map->collumns[map->input].mojis[i] = '\0';
    }

    map->collumns[map->input].len -= *lenMojis;
}

int getLenMojisFromInputColumn(Map *map, char selectedMoji) {
    int lenMojis = 0;
    for (int i = map->maxHeight - map->collumns[map->input].len; i < map->maxHeight; i++){
        if(map->collumns[map->input].mojis[i] != selectedMoji) break;
        
        lenMojis++;
    }

    return lenMojis;
}

void putMojisInOutputColumn(Map *map, int lenMojis, char selectedMoji) {
    int floor = map->maxHeight - map->collumns[map->output].len - 1; // Posição do primeiro espaço em branco na coluna de saida
    map->collumns[map->output].len += lenMojis;

    while(lenMojis--)
        map->collumns[map->output].mojis[floor-lenMojis] = selectedMoji; // Coloca o moji selecionado na coluna de saida
}

bool isValidSwap(Map *map, int lenMojis) {
    //Verifica se a coluna tem espaco suficiente para receber os mojis
    if(lenMojis + map->collumns[map->output].len > map->maxHeight) {
        printf("A troca de %d moji(s) de %d para %d não é possível, pois excede o tamanho da coluna.\n", lenMojis, map->input, map->output);
        return false;
    }

    // Verifica se tem algum elemento na coluna de input
    if(lenMojis == 0) {
        printf("Nenhum moji selecionado para troca.\n");
        return false;
    }

    if(
        map->collumns[map->output].len != 0 && 
        map->collumns[map->output].mojis[map->maxHeight - map->collumns[map->output].len] != 
            map->collumns[map->input].mojis[map->maxHeight - map->collumns[map->input].len]
    ) {
        printf("A troca não é possível, pois o moji da coluna de origem é diferente do moji da coluna de destino.\n");
        return false;
    }

    return true;
}

bool checkColumnCompletion(Map *map) {
    char moji = map->collumns[map->output].mojis[0];

    if (moji == '\0' || map->collumns[map->output].len != map->maxHeight) {
        return false;
    }

    bool diffMoji = false;

    for(int i = 0; i < map->maxHeight; i++) {
        if(map->collumns[map->output].mojis[i] != moji) {
            diffMoji = true;
            break;
        }
    }

    if(!diffMoji){
        showMap(map);
        printf("PARABENS, VOCE FECHOU A COLUNA %d\n", map->output);
        map->collumns[map->output].complete = true;
        map->totalCompleteColumns++;
        pressEnterToContinue();

        return true;
    }

    return false;
}

bool swapMojis(Map *map) {
    char selectedMoji = map->collumns[map->input].mojis[map->maxHeight - map->collumns[map->input].len]; // Moji selecionado para troca
    int lenMojis = getLenMojisFromInputColumn(map, selectedMoji);
    bool swapToVoidOut = map->collumns[map->output].len == 0;
    
    // Verifica se a troca é válida
    if(!isValidSwap(map, lenMojis)) {
        pressEnterToContinue();
        return false;
    }
    
    // Coloca os mojis selecionados na coluna de output
    removeMojisFromInputColumn(map, &lenMojis, selectedMoji);
    putMojisInOutputColumn(map, lenMojis, selectedMoji);

    if(!swapToVoidOut) 
        return checkColumnCompletion(map);

    return false; // Se a coluna de output estava vazia, não precisa verificar se completou
}

bool checkToWin(Map *map){
    return map->totalCompleteColumns == map->lenCollumns - map->lenVoidCollumns;
}

bool startGame(Map *map) {

    while(1){
        showMap(map);

        if(!play(map)) continue; // Se a jogada for invalida, joga denovo

        bool closedColumn = swapMojis(map);

        if(closedColumn && checkToWin(map)) {
            printf("PARABENS!!! VOCE VENCEU!!!\n");
            printf("PARABENS!!! VOCE VENCEU!!!\n");
            printf("PARABENS!!! VOCE VENCEU!!!\n");
            printf("PARABENS!!! VOCE VENCEU!!!\n");
            pressEnterToContinue();
            break;
        }
    }

    return true;
}

void playGame(Maps *maps, int *curLevel) {
    while(1) {
        int win = startGame(&maps->maps[*curLevel-1]);
        (*curLevel)++;

        if(*curLevel > maps->len || (win && !nextLevel())) break;
    }
}