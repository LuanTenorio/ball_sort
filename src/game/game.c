#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../ui/ui.h"
#include "../config.h"

int countMapsInFile(FILE *file) {
    int mapCount = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF)
        if (ch == '-') 
            mapCount++;

    // Conta o ultimo mapa
    if(!isspace(ch)) 
        mapCount++;

    return mapCount;
}

void setMapDimensions(Map *map, FILE *file) {
    char ch;
    int totMojis = 0;

    while ((ch = fgetc(file)) != EOF && ch != '-') {
        if (isspace(ch)) continue;

        if (!isdigit(ch)) {
            totMojis++;
            continue;
        }

        int height = ch - '0';
        map->lenCollumns++;

        if (height > map->maxHeight) {
            map->maxHeight = height;
        }
    }

    map->lenVoidCollumns = (map->lenCollumns * map->maxHeight - totMojis) / map->maxHeight;
}

void setMap(Map *map, FILE *file) {
    int lenColumn = 0;
    int curColumn = -1;
    int floor;
    char ch;

    // Coloca os mojis no mapa
    while ((ch = fgetc(file)) != EOF && ch != '-' && ch != '}') {
        if (isspace(ch)) continue;

        if(lenColumn--){
            map->collumns[curColumn].mojis[lenColumn + floor] = ch;
            continue;
        }

        // Presume-se que sempre vai ser um digito caso o mapa esteja correto
        curColumn++;
        lenColumn = ch - '0';
        floor = map->maxHeight - lenColumn;

        map->collumns[curColumn].mojis = malloc(sizeof(char) * map->maxHeight);
        map->collumns[curColumn].len = lenColumn;
        map->collumns[curColumn].complete = false;
    }

    map->lenCollumns = curColumn + 1;
}

void readMap(Map *map, FILE *file) {
    *map = (Map){0};
    int mapStartPosition = ftell(file);
    int totMojis = 0;

    setMapDimensions(map, file);

    // Vai pro começo do mapa
    fseek(file, mapStartPosition, SEEK_SET);

    map->collumns = malloc(sizeof(Collumn) * map->lenCollumns);

    setMap(map, file);
}

void readMaps(Map *maps, int mapCount, FILE *file){
    for (int i = 0; i < mapCount; i++) 
        readMap(&maps[i], file);
}

Map* loadAllMaps(const char* filename, int* mapCount) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Arquivo de entrada '%s' não encontrado.\n", filename);
        exit(1);
    }

    *mapCount = countMapsInFile(file);
    
    if (*mapCount == 0) {
        fclose(file);
        return NULL;
    }

    Map* maps = malloc(sizeof(Map) * (*mapCount));

    // Volta para o começo do mapa
    fseek(file, 0, SEEK_SET);

    // Lê os mapas do arquivo
    readMaps(maps, *mapCount, file);
    fclose(file);

    return maps;
}


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

    if(numChar < 0 || numChar >= map->lenCollumns || numChar == inputChar - '0') {
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
